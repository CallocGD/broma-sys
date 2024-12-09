
extern crate cc;
use bindgen::builder;


fn main(){
    let bind = builder()
        .header("broma/include/ast.hpp")
        .header("broma/include/broma.hpp")
        .clang_args(&["--std=c++17"])

        .generate().unwrap();
    bind.write_to_file(std::path::PathBuf::from(
        std::env::var("OUT_DIR").unwrap()
    ).join("bindings.rs")).unwrap();


    let manifest_dir = std::path::Path::new(env!("CARGO_MANIFEST_DIR"));
    // let ghc = manifest_dir.join("ghc");
    let mut build = cc::Build::new();
    // build.cpp(true);
    build.flag_if_supported("-std=c++17");
    build.flag_if_supported("/std:c++17");
    build.flag_if_supported("-fexceptions");
    build.flag_if_supported("/fexceptions");
    build.flag_if_supported("/EHsc");

    // // just so we can reach ghc. That's fucked up and I spent 2 hours just figuring that out.
    build.include(manifest_dir);
    build.include(manifest_dir.join("broma").join("include"));
    build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include"));
    // build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include").join("tao").join("pegtl"));
    // build.include(manifest_dir.join("broma").join("PEGTL-3.2.7").join("include").join("tao").join("pegtl").join("contrib"));
    build.file(manifest_dir.join("broma/src/broma.cpp"));
    build.compile("broma");

    
    



}