#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::ffi::CStr;
use std::os::raw;

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

#[cfg(test)]
mod tests {

    // cargo test -- --nocapture

    use super::*;
    use std::mem;
    use std::ptr;
    use std::thread;
    use std::time;

    use libc;

    /// The code of this example is mostly aligned with the sendHello.c
    /// This is very unfinised demo application
    #[test]
    fn test_sendHello() {
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

        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        let mut session: TRDP_SESSION = unsafe { mem::zeroed() };
        let mut psession: *mut TRDP_SESSION = &mut session;
        let mut pAppHandle: *mut TRDP_APP_SESSION_T = &mut psession as *mut TRDP_APP_SESSION_T;
        // 192.168.53.104
        let ownIpAddr: TRDP_IP_ADDR_T = 0xc0a83568;
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
        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        let mut ele: PD_ELE = unsafe { mem::zeroed() };
        let mut pubHandle: TRDP_PUB_T = &mut ele;
        let mut pPubHandle: *mut TRDP_PUB_T = &mut pubHandle;
        let comid = 1001;
        let interval = 1000000;
        let mut data: [u8; 32] = [0xAA; 32];
        data[0] = 0x55;
        data[31] = 0x55;
        let pData = &data as *const u8;
        let data_size = 32;
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
                0,                     //destIpAddr: TRDP_IP_ADDR_T,
                interval,              //interval: UINT32,
                0,                     //redId: UINT32,
                TRDP_FLAGS_NONE as u8, // pktFlags: TRDP_FLAGS_T,
                pData,                 //pData: *const UINT8,
                data_size,             //dataSize: UINT32,
            )
        };

        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        let err = unsafe { tlc_updateSession(psession) };
        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        for i in (0..=20) {
            let mut rfds: libc::fd_set = unsafe { mem::zeroed() }; // bindings.rs have their own fd_set
            let mut noDesc: i32 = 0;

            let mut tv: timeval = unsafe { mem::zeroed() };
            let max_tv : TRDP_TIME_T  = TRDP_TIME_T{tv_sec:0, tv_usec:200_000};
            let min_tv : TRDP_TIME_T  = TRDP_TIME_T{tv_sec:0, tv_usec:100_00 as i64};

            // Fix this later, if necessary
            // let p_rfds : *mut libc::fd_set = &mut rfds as *mut libc::fd_set;
            let p_rfds: *mut libc::fd_set = &mut rfds as *mut libc::fd_set;


            let p_rfds_2: *mut fd_set = unsafe{ &mut *(p_rfds as *mut libc::fd_set as *mut fd_set) };
            // Same thing with transmutate
            // let p_rfds_2: *mut fd_set =  unsafe{ std::mem::transmute::< *mut libc::fd_set , *mut fd_set>(p_rfds) };

            unsafe { libc::FD_ZERO(p_rfds) };

            unsafe {
                tlc_getInterval(
                    psession,
                    &mut tv,
                    p_rfds_2,
                    &mut noDesc as *mut i32,
                );
            }

            if (unsafe{vos_cmpTime(&tv, &max_tv)} > 0)
            {
                tv = max_tv;
            }
            else if (unsafe{vos_cmpTime(&tv, &min_tv)} < 0)
            {
                tv = min_tv;
            }

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

            // let delay = time::Duration::from_millis(100);
            // thread::sleep(delay);

            unsafe {
                tlc_process(psession, p_rfds_2, &mut rv as *mut i32);
            }
            println!("Procesing ... {}", i);
            data[0] = i;
            let err = unsafe{ tlp_put(psession, pubHandle, pData, 32)};
            println!("The error {:?}", err);
            assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        }
        unsafe { tlp_unpublish(psession, pubHandle)};
        unsafe { tlc_closeSession(psession)};
        unsafe { tlc_terminate()};
    }
}
