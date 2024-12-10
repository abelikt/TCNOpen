#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

// ./target/debug/build/lib_sdtv2-da9531089bfd4630/out/bindings.rs
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

/*
unsafe extern "C" {
    pub fn sdt_get_validator(
        type_: sdt_bus_type_t,
        sid1: u32,
        sid2: u32,
        sid2red: u8,
        version: u16,
        p_hnd: *mut sdt_handle_t,
    ) -> sdt_result_t;
}

 * */
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn test_types() {
        let result: sdt_result_t = sdt_result_t_SDT_OK;
        println!("{:?}", result);
        let result: sdt_result_t = sdt_result_t_SDT_ERR_SID;
        println!("{:?}", result);
    }

    #[test]
    fn test_get_validator() {
        let bus_type: sdt_bus_type_t = sdt_bus_type_t_SDT_IPT;
        let sid1: u32 = 40;
        let sid2: u32 = 41;
        let sid2red: u8 = 8;
        let version: u16 = 2;
        let mut sdt_handle: i32 = 0;

        let p_handle: *mut sdt_handle_t = &mut sdt_handle as *mut i32;
        let result = unsafe { sdt_get_validator(bus_type, sid1, sid2, sid2red, version, p_handle) };

        println!("Get Validator: {:?}", result);
    }
}
