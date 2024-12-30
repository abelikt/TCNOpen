#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

/*
cargo run --example receive_hello


*/
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::ffi::CStr;
use std::os::raw;

use std::mem;
use std::ptr;
// use std::thread;
// use std::time;
use libc;

use lib_trdp;

/// # Safety
/// Gets called from C and therefore unsafe
#[no_mangle]
pub unsafe extern "C" fn debug_callback(
    _pRefCon: *mut raw::c_void,
    _categrory: u32,
    _pTime: *const i8,
    _pFile: *const i8,
    _LineNumber: u16,
    pMsgStr: *const i8,
) {
    let msg_str: &str = CStr::from_ptr(pMsgStr).to_str().unwrap();
    let msg: &str = msg_str.strip_suffix("\n").unwrap();
    println!("Log: {}", msg);
}

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
    let mut pAppHandle: *mut TRDP_APP_SESSION_T = &mut psession as *mut TRDP_APP_SESSION_T;
    // 192.168.53.104
    // 0xc0a83568

    let ownIpAddr: TRDP_IP_ADDR_T = 0xc0a83567;
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
    let mut ppdInfo: *mut TRDP_PD_INFO_T = &mut pdInfo as *mut TRDP_PD_INFO_T;

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
    let mut pSubHandle: *mut TRDP_SUB_T = &mut subHandle;

    let comid = 1001;

    /*
    memset(gBuffer, 0, sizeof(gBuffer));

    err = tlp_subscribe( appHandle,                 /*    our application identifier            */
                         &subHandle,                /*    our subscription identifier           */
                         NULL,                      /*    user reference                        */
                         NULL,                      /*    callback functiom                     */
                         0u,
                         comId,                     /*    ComID                                 */
                         0,                         /*    etbTopoCnt: local consist only        */
                         0,                         /*    opTopoCnt                             */
                         VOS_INADDR_ANY, VOS_INADDR_ANY,    /*    Source IP filter              */
                         dstIP,                     /*    Default destination    (or MC Group)  */
                         TRDP_FLAGS_DEFAULT,        /*    TRDP flags                            */
                         PD_COMID_CYCLE * 3,        /*    Time out in us                        */
                         TRDP_TO_SET_TO_ZERO        /*    delete invalid data on timeout        */
    );
    */
    // 192.168.53.104
    let ownIpAddr: TRDP_IP_ADDR_T = 0xc0a83568;

    // 192.168.53.103
    let ownIpAddr_b: TRDP_IP_ADDR_T = 0xc0a83567;

    let err = unsafe {
        tlp_subscribe(
            psession,    // appHandle,                 /*    our application identifier            */
            pSubHandle, // &subHandle,                /*    our subscription identifier           */
            ptr::null(), // NULL,                      /*    user reference                        */
            None, // TRDP_PD_CALLBACK_T // NULL,                      /*    callback functiom                     */
            0,    // 0u,  //serviceId
            comid, // comId,                     /*    ComID                                 */
            0,    // 0,                         /*    etbTopoCnt: local consist only        */
            0,    // 0,                         /*    opTopoCnt                             */
            libc::INADDR_ANY,
            libc::INADDR_ANY, // VOS_INADDR_ANY, VOS_INADDR_ANY,    /*    Source IP filter              */
            ownIpAddr_b, // dstIP,                     /*    Default destination    (or MC Group)  */
            TRDP_FLAGS_NONE as TRDP_FLAGS_T, // TRDP_FLAGS_DEFAULT,        /*    TRDP flags                            */
            2_000_000, // PD_COMID_CYCLE * 3,        /*    Time out in us                        */
            TRDP_TO_BEHAVIOR_T_TRDP_TO_SET_TO_ZERO, // TRDP_TO_SET_TO_ZERO        /*    delete invalid data on timeout        */
        )
    };

    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlp_subscibefailed");
    // drop:        tlc_terminate();

    let err = unsafe { tlc_updateSession(psession) };
    assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_updateSession failed");

    let mut data: [u8; 1024] = [0xAA; 1024];
    data[0] = 0x55;
    data[31] = 0x55;
    let mut pData: *mut u8 = &mut data as *mut u8;

    for i in 0..=100 {
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
        // Same thing with transmutate
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

        let mut pWriteableFD: *mut fd_set = ptr::null_mut();
        let mut rv = unsafe {
            vos_select(
                noDesc,
                p_rfds_2,
                pWriteableFD,
                ptr::null_mut() as *mut fd_set,
                &mut tv,
            )
        };
        println!("Ready descriptors {:?}", rv);

        // let delay = time::Duration::from_millis(100);
        // thread::sleep(delay);

        let err = unsafe { tlc_process(psession, p_rfds_2, &mut rv as *mut i32) };

        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlc_process failed");

        //receivedSize = sizeof(gBuffer);
        let mut receivedSize: u32 = 1024;
        let preceivedSize: *mut u32 = &mut receivedSize as *mut u32;

        let err = unsafe { tlp_get(psession, subHandle, ppdInfo, pData, preceivedSize) };

        //assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR, "tlp_get failed");
        println!("Error {:?}", err);
    }
}
