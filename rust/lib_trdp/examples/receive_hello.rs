#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

//! Very crude implementation of an example that uses lib_trdp from Rust.
//! Work in progress!!!
//!
//! Run Example:
//!
//!     cargo run --example receive_hello
//!
//! Needs a sendHello instance:
//!
//! Build examples
//!     cd ../../trdp
//!     make example
//!
//! Run Example
//!     export LD_LIBRARY_PATH=$HOME/Repos/tcnopen-trdp/trdp/bld/output/linux-rel/
//!     ../../trdp/bld/output/linux-rel/sendHello -o 192.168.53.104 -t 192.168.53.103
//!     ./sendHello -o 192.168.53.104 -t 192.168.53.103

// TODO: open issue Ignored PD
// Log: Ignore PD received for IP 192.168.53.104 which is not this sessions realIP (0xc0a83567)
// Error: Timeout

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use libc;
use std::ffi::CStr;
use std::mem;
use std::os::raw;
use std::ptr;

use lib_trdp;
use lib_trdp::debug_callback;

/// The code of this example is mostly aligned with the sendHello.c
/// This is very unfinished demo application
///
fn main() {
    let pRefCon: *mut raw::c_void = ptr::null_mut();

    // Todo direct assignment fails, so we pipe through callback
    // = note: expected enum `Option<unsafe extern "C" fn(_, _, _, _, _, _)>`
    // found enum `Option<unsafe extern "C" fn(_, _, _, _, _, _) {debug_callback}>`
    // let debug = Some( debug_callback );
    let callback: unsafe extern "C" fn(_, _, _, _, _, _) = debug_callback;
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

    let ownIpAddr: TRDP_IP_ADDR_T = 0xc0a83567; // 192.168.53.103

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

    let mut pdInfo: TRDP_PD_INFO_T = unsafe { mem::zeroed() };
    let ppdInfo: *mut TRDP_PD_INFO_T = &mut pdInfo as *mut TRDP_PD_INFO_T;

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
    let mut subHandle: TRDP_SUB_T = &mut ele;
    let pSubHandle: *mut TRDP_SUB_T = &mut subHandle;

    let comid = 0; // sendHello.c sends with comid 0
                   // send_hello : 1001;

    let err = unsafe {
        tlp_subscribe(
            psession,    /*    our application identifier            */
            pSubHandle,  /*    our subscription identifier           */
            ptr::null(), /*    user reference                        */
            None,        /*    callback functiom                     */
            0,           //serviceId
            comid,       /*    ComID                                 */
            0,           /*    etbTopoCnt: local consist only        */
            0,           /*    opTopoCnt                             */
            libc::INADDR_ANY,
            libc::INADDR_ANY,                /*    Source IP filter              */
            ownIpAddr,                     /*    Default destination    (or MC Group)  */
            TRDP_FLAGS_NONE as TRDP_FLAGS_T, /*    TRDP flags                            */
            2_000_000,                       /*    Time out in us                        */
            TRDP_TO_BEHAVIOR_T_TRDP_TO_SET_TO_ZERO, /*    delete invalid data on timeout        */
        )
    };

    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlp_subscibefailed");
    // todo: drop:        tlc_terminate();

    let err = unsafe { tlc_updateSession(psession) };
    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_updateSession failed");

    let mut data: [u8; 1024] = [0xAA; 1024];
    data[0] = 0x55;
    data[31] = 0x55;
    let pData: *mut u8 = &mut data as *mut u8;

    for _ in 0..=100 {
        let mut rfds: libc::fd_set = unsafe { mem::zeroed() }; // bindings.rs have their own fd_set
        let mut noDesc: i32 = 0;

        let mut tv: timeval = unsafe { mem::zeroed() };
        let max_tv: TRDP_TIME_T = TRDP_TIME_T {
            tv_sec: 0,
            tv_usec: 1_000_000,
        };
        let min_tv: TRDP_TIME_T = TRDP_TIME_T {
            tv_sec: 0,
            tv_usec: 100_000 as i64,
        };

        // Fix this later, if necessary
        // let p_rfds : *mut libc::fd_set = &mut rfds as *mut libc::fd_set;
        let p_rfds: *mut libc::fd_set = &mut rfds as *mut libc::fd_set;

        let p_rfds_2: *mut fd_set = unsafe { &mut *(p_rfds as *mut libc::fd_set as *mut fd_set) };
        // Same thing with transmute
        // let p_rfds_2: *mut fd_set =  unsafe{ std::mem::transmute::< *mut libc::fd_set , *mut fd_set>(p_rfds) };

        unsafe { libc::FD_ZERO(p_rfds) };

        unsafe {
            tlc_getInterval(psession, &mut tv, p_rfds_2, &mut noDesc as *mut i32);
        }

        // println!("tv interval {} {} {}", tv.tv_sec, tv.tv_usec, noDesc);

        if (unsafe { vos_cmpTime(&tv, &max_tv) } > 0) {
            tv = max_tv;
        } else if (unsafe { vos_cmpTime(&tv, &min_tv) } < 0) {
            tv = min_tv;
        }

        // println!("tv minmax {} {} {}", tv.tv_sec, tv.tv_usec, noDesc);

        let pWriteableFD: *mut fd_set = ptr::null_mut();
        let mut rv = unsafe {
            vos_select(
                noDesc,
                p_rfds_2,
                pWriteableFD,
                ptr::null_mut() as *mut fd_set,
                &mut tv,
            )
        };
        // println!("Ready descriptors {:?}", rv);

        // let delay = time::Duration::from_millis(100);
        // thread::sleep(delay);

        let err = unsafe { tlc_process(psession, p_rfds_2, &mut rv as *mut i32) };

        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_process failed");

        if rv > 0 {
            println!("other descriptors were ready\n");
        }

        let mut receivedSize: u32 = 1024;
        let preceivedSize: *mut u32 = &mut receivedSize as *mut u32;

        let err = unsafe { tlp_get(psession, subHandle, ppdInfo, pData, preceivedSize) };

        match err {
            TRDP_ERR_T_TRDP_NO_ERR => println!("Success, received {}", receivedSize),
            TRDP_ERR_T_TRDP_TIMEOUT_ERR => println!("Error: Timeout"),
            TRDP_ERR_T_TRDP_NODATA_ERR => println!("Error: No Data "),
            _ => println!("Error {:?}", err),
        }
        if err == TRDP_ERR_T_TRDP_NO_ERR {
            //println!("State rv {:?} size {:?}", rv, receivedSize);
            println!("Pdinfo {:?}", pdInfo);
            println!("Pdinfo.comid {:?}", pdInfo.comId);
            println!("Pdinfo ssc {:?}", pdInfo.seqCount);
            print!("As hex: ");
            for r in 0..receivedSize {
                let d = data[r as usize];
                //print!("{:x} {:?} {} ", d, d.is_ascii(), char::from(d));
                print!("0x{:x} ", d);
            }
            println!("");
            let s: String = (0..receivedSize)
                .map(|x| char::from(data[x as usize]))
                .collect();
            println!("As String: {}", s)
        }
    }
}
