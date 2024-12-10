#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

// ./target/debug/build/lib_sdtv2-da9531089bfd4630/out/bindings.rs
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

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
        let mut sdt_handle: i32 = 88;

        let p_handle: *mut sdt_handle_t = &mut sdt_handle as *mut i32;
        let result = unsafe { sdt_get_validator(bus_type, sid1, sid2, sid2red, version, p_handle) };

        println!("Get Validator: {:?}", result);
        assert_ne!(sdt_handle, 88);
        assert_eq!(result, sdt_result_t_SDT_OK);
    }

    #[test]
    fn test_sdt_set_sdsink_parameters() {
        let bus_type: sdt_bus_type_t = sdt_bus_type_t_SDT_IPT;
        let sid1: u32 = 42;
        let sid2: u32 = 43;
        let sid2red: u8 = 8;
        let version: u16 = 2;
        let mut sdt_handle: i32 = 88;

        let p_handle: *mut sdt_handle_t = &mut sdt_handle as *mut i32;
        let result = unsafe { sdt_get_validator(bus_type, sid1, sid2, sid2red, version, p_handle) };

        assert_ne!(sdt_handle, 88);
        assert_eq!(result, sdt_result_t_SDT_OK);

        let result = unsafe {
            sdt_set_sdsink_parameters(
                sdt_handle, 100,  /*ms Trx*/
                120,  /*ms Ttx*/
                5,    /*n_rxsafe*/
                2,    /*n_guard*/
                1000, /*cmthr*/
                200,  /*lmi_max*/
            )
        };
        assert_eq!(result, sdt_result_t_SDT_OK);
    }

    #[test]
    fn test_sdt_ipt_secure_pd() {
        let bus_type: sdt_bus_type_t = sdt_bus_type_t_SDT_IPT;
        let sid1: u32 = 1;
        let sid2: u32 = 2;
        let sid2red: u8 = 8;
        let version: u16 = 2;
        let mut sdt_handle: i32 = 88;

        let p_handle: *mut sdt_handle_t = &mut sdt_handle as *mut i32;
        let result = unsafe { sdt_get_validator(bus_type, sid1, sid2, sid2red, version, p_handle) };

        assert_ne!(sdt_handle, 88);
        assert_eq!(result, sdt_result_t_SDT_OK);

        let result = unsafe {
            sdt_set_sdsink_parameters(
                sdt_handle, 100,  /*ms Trx*/
                120,  /*ms Ttx*/
                5,    /*n_rxsafe*/
                2,    /*n_guard*/
                1000, /*cmthr*/
                200,  /*lmi_max*/
            )
        };
        assert_eq!(result, sdt_result_t_SDT_OK);

        let mut buffer: [u8; 32] = [0; 32];
        let p_buffer = buffer.as_mut_ptr();
        let mut ssc: u32 = 88;
        let p_ssc = &mut ssc as *mut u32;
        let p_buf: *mut ::std::os::raw::c_void = p_buffer as *mut std::os::raw::c_void;
        let len = 32;
        let sid = 33;
        let udv = 2;
        let result = unsafe { sdt_ipt_secure_pd(p_buf, len, sid, udv, p_ssc) };
        assert_eq!(result, sdt_result_t_SDT_OK);
    }
}
