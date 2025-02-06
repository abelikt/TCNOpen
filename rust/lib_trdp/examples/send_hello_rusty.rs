#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

//! Crude implementation of example sendHello that uses lib_trdp from Rust that should provide
//! a nicer, more idiomatic, rusty experience.
//!
//! Should still be compatible to the C example sendHello and Rust send_hello.
//!
//! Run Example:
//!
//!     cargo run --example send_hello_rusty -- --destination 192.168.53.103 --source 192.168.53.104 --comid 1001
//!
//! Add second address
//!     sudo ip address add 192.168.53.103/24 dev enp8s0
//!     sudo ip address add 192.168.53.104/24 dev enp8s0
//!

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use libc;
use std::mem;
use std::net;
use std::os::raw;
use std::ptr;

use clap::Parser;

use lib_trdp;

#[derive(Parser)]
#[command(version, about, long_about = None)]
struct Cli {
    /// Destination IP
    #[arg(short, long)]
    destination: String,

    #[arg(short, long)]
    /// Source IP
    source: String,

    /// Communication IO
    #[arg(short, long)]
    comid: Option<u32>,
}

/// The code of this example is mostly aligned with the sendHello.c
/// This is very unfinished demo application
fn main() {
    let cli = Cli::parse();

    let dest_ip = cli
        .destination
        .parse::<net::Ipv4Addr>()
        .expect("Cannot parse destination address");
    println!("Destination will be  {dest_ip:?}");

    let src_ip = cli
        .source
        .parse::<net::Ipv4Addr>()
        .expect("Cannot parse source address");
    println!("Source will be  {src_ip:?}");

    let comid: u32 = cli.comid.unwrap_or_else(
        || {
            println!("No comid specified default will be zero");
            0
        }
    );

    // The user context
    let pRefCon: *mut raw::c_void = ptr::null_mut();

    // Enable debug callback
    // Todo direct assignment fails, so we pipe through callback
    // = note: expected enum `Option<unsafe extern "C" fn(_, _, _, _, _, _)>`
    // found enum `Option<unsafe extern "C" fn(_, _, _, _, _, _) {debug_callback}>`
    // let debug = Some( debug_callback );
    let callback: unsafe extern "C" fn(_, _, _, _, _, _) = lib_trdp::debug_callback;
    let debug = Some(callback);

    let memConfig = TRDP_MEM_CONFIG_T {
        p: ptr::null_mut() as *mut UINT8,
        size: 160000,
        prealloc: [0; 15],
    };

    let pMemConfig = &memConfig as *const TRDP_MEM_CONFIG_T;

    let err = unsafe { tlc_init(debug, pRefCon, pMemConfig) };

    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_init failed");

    let mut session: TRDP_SESSION = unsafe { mem::zeroed() };
    let mut psession: *mut TRDP_SESSION = &mut session;
    let pAppHandle: *mut TRDP_APP_SESSION_T = &mut psession as *mut TRDP_APP_SESSION_T;

    let ownIpAddr: TRDP_IP_ADDR_T = src_ip.to_bits();
    let destIpAddr: TRDP_IP_ADDR_T = dest_ip.to_bits();

    let leaderIpAddr: TRDP_IP_ADDR_T = 0x0;
    let pMarshall: *const TRDP_MARSHALL_CONFIG_T = ptr::null();

    let pd_zero: TRDP_PD_CONFIG_T = unsafe { mem::zeroed() };
    let pdDefault = TRDP_PD_CONFIG_T {
        sendParam: TRDP_COM_PARAM_T {
            qos: TRDP_PD_DEFAULT_QOS as u8,
            ttl: TRDP_PD_DEFAULT_TTL as u8,
            retries: 0,
        },
        flags: TRDP_FLAGS_NONE as u8,
        timeout: 1000000,
        toBehavior: 1,
        ..pd_zero
    };

    let pPdDefault: *const TRDP_PD_CONFIG_T = &pdDefault as *const TRDP_PD_CONFIG_T;

    let pMdDefault: *const TRDP_MD_CONFIG_T = ptr::null();

    let processConfig: TRDP_PROCESS_CONFIG_T = unsafe { mem::zeroed() };
    let pProcessConfig: *const TRDP_PROCESS_CONFIG_T = &processConfig;

    let err = unsafe {
        tlc_openSession(
            pAppHandle,
            ownIpAddr,
            leaderIpAddr,
            pMarshall,
            pPdDefault,
            pMdDefault,
            pProcessConfig,
        )
    };
    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_openSession failed");

    let mut ele: PD_ELE = unsafe { mem::zeroed() };
    let mut pubHandle: TRDP_PUB_T = &mut ele;
    let pPubHandle: *mut TRDP_PUB_T = &mut pubHandle;

    let interval = 100_000;

    const buffer_size: usize = 24;
    let mut data: [u8; buffer_size] = [0x00; buffer_size];
    let pData = &data as *const u8;

    // Mimic C example
    let initial_message = format!("Hello World");
    let message_bytes = initial_message.as_bytes();
    let size = message_bytes.len();
    data[..size].copy_from_slice(message_bytes);

    let err = unsafe {
        tlp_publish(
            psession, // appHandle: TRDP_APP_SESSION_T,
            pPubHandle,
            ptr::null(),           //pUserRef: *const ::std::os::raw::c_void,
            None,                  //pfCbFunction: TRDP_PD_CALLBACK_T,
            0,                     //serviceId: UINT32,
            comid,                 //comId: UINT32,
            0,                     //etbTopoCnt: UINT32,
            0,                     //opTrnTopoCnt: UINT32,
            ownIpAddr,             //srcIpAddr: TRDP_IP_ADDR_T,
            destIpAddr,            // destIpAddr: TRDP_IP_ADDR_T,
            interval,              //interval: UINT32,
            0,                     //redId: UINT32,
            TRDP_FLAGS_NONE as u8, // pktFlags: TRDP_FLAGS_T,
            pData,                 //pData: *const UINT8,
            buffer_size as u32,    //dataSize: UINT32,
        )
    };
    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlp_publish failed");

    let err = unsafe { tlc_updateSession(psession) };
    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_updateSession failed");

    for i in 0..=100 {

        println!("Procesing interval: {}", i);

        // Create a file descriptor set for later use with the select call
        // (bindings.rs provides a binding but its unclear how to use it with FD_ZERO)
        let mut rfds: libc::fd_set = unsafe { mem::zeroed() };

        let mut noDesc: i32 = 0;

        let mut tv: timeval = unsafe { mem::zeroed() };
        let max_tv: TRDP_TIME_T = TRDP_TIME_T {
            tv_sec: 0,
            tv_usec: 100_000,
        };
        let min_tv: TRDP_TIME_T = TRDP_TIME_T {
            tv_sec: 0,
            tv_usec: 10_000 as i64,
        };

        // Prepare rfds file descriptor set for later use with the select call
        // Simplify this madness later, if possible
        let p_rfds: *mut libc::fd_set = &mut rfds as *mut libc::fd_set;
        let p_rfds_2: *mut fd_set = unsafe { &mut *(p_rfds as *mut libc::fd_set as *mut fd_set) };
        // Same trick with transmute:
        // let p_rfds_2: *mut fd_set =  unsafe{ std::mem::transmute::< *mut libc::fd_set , *mut fd_set>(p_rfds) };

        unsafe { libc::FD_ZERO(p_rfds) };

        unsafe {
            tlc_getInterval(psession, &mut tv, p_rfds_2, &mut noDesc as *mut i32);
        }
        println!("    tv interval {} {} {}", tv.tv_sec, tv.tv_usec, noDesc);

        if (unsafe { vos_cmpTime(&tv, &max_tv) } > 0) {
            tv = max_tv;
        } else if (unsafe { vos_cmpTime(&tv, &min_tv) } < 0) {
            tv = min_tv;
        }
        println!("    tv minmax {} {} {}", tv.tv_sec, tv.tv_usec, noDesc);

        let pWriteableFD: *mut fd_set = ptr::null_mut();

        // TODO Replace and simplify this with a clock_nanosleep / thread::sleep()
        let mut rv = unsafe {
            vos_select(
                noDesc,
                p_rfds_2,
                pWriteableFD,
                ptr::null_mut() as *mut fd_set,
                &mut tv,
            )
        };
        println!("    Ready descriptors : {:?}", rv);

        // let delay = time::Duration::from_millis(100);
        // thread::sleep(delay);

        let err = unsafe { tlc_process(psession, p_rfds_2, &mut rv as *mut i32) };
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_process failed");

        let temp_string = format!("Just a Counter: {i:08}"); // Keep temporary value
        let message_bytes = temp_string.as_bytes();
        let size = message_bytes.len();
        data[..size].copy_from_slice(message_bytes);

        let err = unsafe { tlp_put(psession, pubHandle, pData, size as u32) };
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlp_put failed");
    }
    unsafe { tlp_unpublish(psession, pubHandle) };
    unsafe { tlc_closeSession(psession) };
    unsafe { tlc_terminate() };
}
