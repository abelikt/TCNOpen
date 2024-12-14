#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::os::raw;
use std::ffi::CStr;

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
        let msg_str : &str = CStr::from_ptr(pMsgStr).to_str().unwrap();
        let msg: &str  = msg_str.strip_suffix("\n").unwrap();
        println!("Log: {}", msg);
    }

#[cfg(test)]
mod tests {

    // cargo test -- --nocapture

    use std::ptr;
    use super::*;

    #[test]
    fn test_tlc_init() {

        let pRefCon: *mut raw::c_void = ptr::null_mut();

        // Todo direct assignment fails, so we pipe through callback
        // = note: expected enum `Option<unsafe extern "C" fn(_, _, _, _, _, _)>`
        // found enum `Option<unsafe extern "C" fn(_, _, _, _, _, _) {debug_callback}>`
        // let debug = Some( debug_callback );
        let callback : unsafe extern "C" fn(_, _, _, _, _, _)  = debug_callback;
        let debug = Some( callback );

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