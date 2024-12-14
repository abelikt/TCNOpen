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

    #[test]
    fn test_tlc_init() {
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
        let ownIpAddr: TRDP_IP_ADDR_T = 0x11223344;
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

    }
}
