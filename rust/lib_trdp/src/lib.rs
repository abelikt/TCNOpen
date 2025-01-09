#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

//! Very crude implementation of some tests that use lib_trdp

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
    // use std::thread;
    // use std::time;
    use libc;

    #[test]
    fn test_stuff() {
    }
}