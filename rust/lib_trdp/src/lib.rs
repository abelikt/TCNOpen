#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::os::raw;
use std::ptr;
use std::ffi::CStr;

#[no_mangle]
pub unsafe extern "C" fn debug_callback(
        pRefCon: *mut raw::c_void,
        categrory: u32,
        pTime: *const i8,
        pFile: *const i8,
        LineNumber: u16,
        pMsgStr: *const i8,
    ) {
        let msg_str : &str = CStr::from_ptr(pMsgStr).to_str().unwrap();
        let msg: &str  = msg_str.strip_suffix("\n").unwrap();
        println!("Log: {}", msg);
    }

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        assert_eq!(4, 4);
    }

    //     pub fn tlc_init(
    //         pPrintDebugString: TRDP_PRINT_DBG_T,
    //         pRefCon: *mut ::std::os::raw::c_void,
    //         pMemConfig: *const TRDP_MEM_CONFIG_T,
    //     ) -> TRDP_ERR_T;
    //
    //     pub static mut gPDebugFunction: VOS_PRINT_DBG_T;
    //
    // pub struct TRDP_MEM_CONFIG_T {
    //     pub p: *mut UINT8,
    //     pub size: UINT32,
    //     pub prealloc: [UINT32; 15usize],
    // }
    //
    //
    #[test]
    fn test_tlc_init() {
        let err: TRDP_ERR_T;
        //let pPrintDebugString= ptr::null() as std::os::raw::c_void;
        let pRefCon: *mut raw::c_void = ptr::null_mut();


        // Todo direct assignment fails, so we pipe through callback
        // = note: expected enum `Option<unsafe extern "C" fn(_, _, _, _, _, _)>`
        // found enum `Option<unsafe extern "C" fn(_, _, _, _, _, _) {debug_callback}>`
        // let debug = Some( debug_callback );
        let callback : unsafe extern "C" fn(_, _, _, _, _, _)  = debug_callback;
        let debug = Some( callback );

        //     TRDP_MEM_CONFIG_T       dynamicConfig   = {NULL, RESERVED_MEMORY, {0}};
        let memConfig = TRDP_MEM_CONFIG_T {
            p: ptr::null_mut() as *mut UINT8,
            size: 160000,
            prealloc: [0; 15],
        };
        let pMemConfig = &memConfig as *const TRDP_MEM_CONFIG_T;

        let err = unsafe { tlc_init(debug, pRefCon, pMemConfig) };

        println!("The error {:?}", err);
    }
}
