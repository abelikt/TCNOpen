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
    use std::time;
    use std::thread;

    use libc;

    /// The code of this example is mostly aligned with the sendHello.c
    /// demo application
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

        /*
        tlc_openSession(&appHandle,
                        ownIP, 0,               /* use default IP address           */
                        NULL,                   /* no Marshalling                   */
                        &pdConfiguration, NULL, /* system defaults for PD and MD    */
                        &processConfig) != TRDP_NO_ERR)
         */
        /*
        unsafe extern "C" {
            pub fn tlc_openSession(
                pAppHandle: *mut TRDP_APP_SESSION_T,
                ownIpAddr: TRDP_IP_ADDR_T,
                leaderIpAddr: TRDP_IP_ADDR_T,
                pMarshall: *const TRDP_MARSHALL_CONFIG_T,
                pPdDefault: *const TRDP_PD_CONFIG_T,
                pMdDefault: *const TRDP_MD_CONFIG_T,
                pProcessConfig: *const TRDP_PROCESS_CONFIG_T,
            ) -> TRDP_ERR_T;
         */
        // madness
        let mut session: TRDP_SESSION = unsafe { mem::zeroed() };
        let mut psession: *mut TRDP_SESSION = &mut session;
        let mut pAppHandle: *mut TRDP_APP_SESSION_T = &mut psession as *mut TRDP_APP_SESSION_T;
        // 192.168.53.104
        let ownIpAddr: TRDP_IP_ADDR_T = 0xc0a83568;
        let leaderIpAddr: TRDP_IP_ADDR_T = 0x0;
        let pMarshall: *const TRDP_MARSHALL_CONFIG_T = ptr::null();

        //     TRDP_PD_CONFIG_T        pdConfiguration =
        //                         {NULL, NULL, TRDP_PD_DEFAULT_SEND_PARAM, TRDP_FLAGS_NONE, 1000000u, TRDP_TO_SET_TO_ZERO, 0u};

        // Bindgen cant provide this yet
        // #define TRDP_PD_DEFAULT_SEND_PARAM          {TRDP_PD_DEFAULT_QOS, TRDP_PD_DEFAULT_TTL, 0u}

        // src/api/trdp_types.h:    TRDP_TO_SET_TO_ZERO     = 1u,    /**< If set, data will be reset to zero on time out             */
        // pub type TRDP_TO_BEHAVIOR_T = ::std::os::raw::c_uint;
        // TRDP_TO_BEHAVIOR_T -> 1

        // Type missmatch in TRDP_PD_DEFAULT_QOS (u32) / TRDP_COM_PARAM_T (UINT8)
        //pub const TRDP_PD_DEFAULT_QOS: u32 = 5;

        // Type missmatch TRDP_PD_DEFAULT_TTL  / ttl

        // Type missmatch TRDP_FLAGS_NONE expected `u8`, found `u32`
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
        let processConfig : TRDP_PROCESS_CONFIG_T = unsafe{mem::zeroed()};
        let pProcessConfig: *const TRDP_PROCESS_CONFIG_T= &processConfig;


        let err = unsafe {
            tlc_openSession(
                pAppHandle,
                ownIpAddr,
                leaderIpAddr,
                pMarshall,
                pPdDefault,
                pMdDefault,
                pProcessConfig
            )
        };
        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);


        /*
            /*    Copy the packet into the internal send queue, prepare for sending.    */
    /*    If we change the data, just re-publish it    */
    err = tlp_publish(  appHandle,                  /*    our application identifier    */
                        &pubHandle,                 /*    our pulication identifier     */
                        NULL, NULL,
                        0u,
                        comId,                      /*    ComID to send                 */
                        0,                          /*    local consist only            */
                        0,
                        ownIP,                      /*    default source IP             */
                        destIP,                     /*    where to send to              */
                        interval,                   /*    Cycle time in us              */
                        0,                          /*    not redundant                 */
                        TRDP_FLAGS_NONE,            /*    Use callback for errors       */
                        gData,                      /*    initial data                  */
                        dataSize                    /*    data size                     */
                        );

         */
        let mut ele : PD_ELE =  unsafe{mem::zeroed()};
        // pub type TRDP_PUB_T = *mut PD_ELE;
        let mut pubHandle : TRDP_PUB_T = &mut ele;
        let mut pPubHandle: *mut TRDP_PUB_T  = &mut pubHandle;
        let comid = 1001;
        let interval = 1000000;
        let data:  [u8; 32]= [0;32];
        let pData = &data as *const u8;
        let data_size= 32;
        let err = unsafe {tlp_publish
            (
                psession, // appHandle: TRDP_APP_SESSION_T,
                pPubHandle,
                ptr::null(), //pUserRef: *const ::std::os::raw::c_void,
                None, //pfCbFunction: TRDP_PD_CALLBACK_T,
                0, //serviceId: UINT32,
                comid, //comId: UINT32,
                0, //etbTopoCnt: UINT32,
                0, //opTrnTopoCnt: UINT32,
                ownIpAddr, //srcIpAddr: TRDP_IP_ADDR_T,
                0, //destIpAddr: TRDP_IP_ADDR_T,
                interval, //interval: UINT32,
                0, //redId: UINT32,
                TRDP_FLAGS_NONE as u8, // pktFlags: TRDP_FLAGS_T,
                pData, //pData: *const UINT8,
                data_size, //dataSize: UINT32,
        )};

        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        let err = unsafe {tlc_updateSession(psession) };
        println!("The error {:?}", err);
        assert_eq!(err, TRDP_ERR_T_TRDP_NO_ERR);

        for _ in (0..=10) {
            //let mut rfds : TRDP_FDS_T;
            let mut rfds : fd_set = unsafe{mem::zeroed()}; // bindings.rs have their own fd_set
            //let mut rfds = libc::fd_set{};
            let mut noDesc:i32 =0;

            let mut tv : timeval = unsafe{mem::zeroed()};

            // Fix this later, if necessary
            // unsafe { libc::FD_ZERO(&mut rfds as *mut libc::fd_set) ; }

            unsafe {tlc_getInterval(psession, &mut tv, &mut rfds as *mut fd_set, &mut noDesc as *mut i32);}

            // Fix this later
            // if (vos_cmpTime(&tv, &max_tv) > 0)
            // {
            //     tv = max_tv;
            // }
            // else if (vos_cmpTime(&tv, &min_tv) < 0)
            // {
            //     tv = min_tv;
            // }

            let mut pWriteableFD : *mut fd_set = ptr::null_mut();
            let mut rv = unsafe{ vos_select(noDesc, &mut rfds, pWriteableFD, ptr::null_mut() as *mut fd_set, &mut tv) };

            let delay = time::Duration::from_millis(1000);
            thread::sleep(delay);

            unsafe {tlc_process(psession, &mut rfds, &mut rv as *mut i32);}


        }

    }
}
