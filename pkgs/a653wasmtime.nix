{ lib, stdenv, bintools, c-abi-lens, wasmtime, pkgsWasm }:

stdenv.mkDerivation {
  pname = "a653-wasmtime";
  version = "unstable-2024-04-17";

  src = ./..;

  patches = [ ../patches/allow-cc-override.patch ];
  preConfigure = ''
    mkdir home
    export PROJECT_HOME="$PWD/home"
  '';

  buildInputs = [ bintools wasmtime.dev ];

  preBuild = ''
    mkdir -p $PWD/home/tmp/arinc653-wasm/pkgs/c-abi-lens/target/debug
    # Use the pre-built c-abi-lens from the flake input
    ln -s ${c-abi-lens}/bin/c-abi-lens $PWD/home/tmp/arinc653-wasm/pkgs/c-abi-lens/target/debug/c-abi-lens
  '';

  buildPhase = ''
    runHook preBuild

    # Build wasm_host target
    CC=${stdenv.cc.targetPrefix}gcc \
    AR=${stdenv.cc.targetPrefix}ar \
    RANLIB=${stdenv.cc.targetPrefix}ranlib \
    make wasm_host

    ## Build wasm_guest target with WASI_SYSROOT
    WASMCC=${pkgsWasm.stdenv.cc}/bin/${pkgsWasm.stdenv.cc.targetPrefix}clang \
    WASI_SYSROOT=${pkgsWasm.wasilibc.dev}/share/wasi-sysroot \
    make wasm_guest

    runHook postBuild
  '';

  installPhase = ''
    mkdir --parent -- $out/bin
    mv $PROJECT_HOME/bin/* $out/bin
  '';

  dontStrip = true;
  hardeningDisable = [ "all" ];
}
