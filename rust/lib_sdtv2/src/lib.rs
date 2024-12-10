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

    /*
    unsafe extern "C" {
        pub fn sdt_set_sdsink_parameters(
            handle: sdt_handle_t,
            rx_period: u16,
            tx_period: u16,
            n_rxsafe: u8,
            n_guard: u16,
            cmthr: u32,
            lmi_max: u16,
        ) -> sdt_result_t;
    }
    */

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
}
