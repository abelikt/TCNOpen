use std::env;
use std::path::PathBuf;

// ldd target/debug/deps/lib_trdp-5264ca412fdf29cf
// export LD_LIBRARY_PATH=../../trdp/bld/output/linux-rel/

fn main() {

    println!("cargo::rustc-env=LD_LIBRARY_PATH=../../trdp/bld/output/linux-rel/");

    // Tell cargo to look for shared libraries in the specified directory
    println!("cargo:rustc-link-search=../../trdp/bld/output/linux-rel/");

    // Tell cargo to tell rustc to link the shared library.
    println!("cargo:rustc-link-lib=trdp");
    println!("cargo:rustc-link-lib=uuid");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        .clang_arg("-v")
        .clang_arg("-I../../trdp/src/api")
        .clang_arg("-I../../trdp/src/vos/api")
        .clang_arg("-I../../trdp/src/common")
        .clang_arg("-DLINUX")
        .clang_arg("-D_GNU_SOURCE")
        .clang_arg("-DPOSIX")
        .clang_arg("-DTARGET_VOS=posix")
        .clang_arg("-DTARGET_OS=LINUX")
        .clang_arg("-DHAS_UUID")
        // The input header we would like to generate
        // bindings for.
        .header("wrapper.h")
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
