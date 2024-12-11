
extern crate cc;
// extern  crate 
use bindgen::builder;


fn main(){
    let manifest_dir = std::path::Path::new(env!("CARGO_MANIFEST_DIR"));

    let bind = builder()
        .header("cbroma/cbroma.h")
        .generate().unwrap();

    bind.write_to_file(std::path::PathBuf::from(
        std::env::var("OUT_DIR").unwrap()
    ).join("bindings.rs")).unwrap();

    let mut build = cc::Build::new();
    build.flag_if_supported("-std=c++17");
    build.flag_if_supported("/std:c++17");
    build.flag_if_supported("-fexceptions");
    build.flag_if_supported("-fpermissive");
    build.flag_if_supported("-Wunused-parameter");
    build.flag_if_supported("/EHsc");

    // just so we can reach ghc. That's fucked up and I spent 2 hours just figuring that out.
    build.include(manifest_dir);
    build.include(manifest_dir.join("broma").join("include"));
    build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include"));
    // build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include").join("tao").join("pegtl"));
    // build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include").join("tao").join("pegtl").join("contrib"));
    // build.include(manifest_dir.join("cbroma"));

    build.file(manifest_dir.join("broma/src/broma.cpp"));
    // Compile C Port so Rust knows how to use broma correctly...
    build.file(manifest_dir.join("cbroma/cbroma.cpp"));
    build.include(manifest_dir.join("cbroma"));
    build.compile("broma");
}

