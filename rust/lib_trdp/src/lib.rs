#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::os::raw;
use std::ptr;
pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    // pub type VOS_PRINT_DBG_T = ::std::option::Option<
    //     unsafe extern "C" fn(
    //         pRefCon: *mut ::std::os::raw::c_void,
    //         category: VOS_LOG_T,
    //         pTime: *const CHAR8,
    //         pFile: *const CHAR8,
    //         LineNumber: UINT16,
    //         pMsgStr: *const CHAR8,
    //     ),
    // >;

    #[no_mangle]
    pub extern "C" fn debug_callback(
        pRefCon: *mut raw::c_void,
        categrory: u32,
        pTime: *const i8,
        pFile: *const i8,
        LineNumber: u16,
        pMsgStr: *const i8,
    ) {
        println!("Whatever");
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
    //     #[doc = "< pointer to static or allocated memory"]
    //     pub p: *mut UINT8,
    //     #[doc = "< size of static or allocated memory"]
    //     pub size: UINT32,
    //     #[doc = "< memory block structure"]
    //     pub prealloc: [UINT32; 15usize],
    // }
    //
    //
    #[test]
    fn test_tlc_init() {
        let err: TRDP_ERR_T;
        //let pPrintDebugString= ptr::null() as std::os::raw::c_void;
        //let pRefCon= ptr::null() as std::os::raw::c_void;

        // `Option<unsafe extern "C" fn(*mut c_void, u32, *const i8, *const i8, u16, *const i8)>`
        let debug = &debug_callback;

        /*    let pMemConfig = TRDP_MEM_CONFIG_T{
                p : ptr::null(),
                size :
                prealloc :
            };
        */
        //let pMemConfig : *const TRDP_MEM_CONFIG_T  = ptr::null();
        //let err = unsafe { tlc_init(pPrintDebugString, pRefCon, pMemConfig)};
    }
}
