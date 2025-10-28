{ lib, stdenv, bintools }:

stdenv.mkDerivation {
  pname = "a653lib";
  version = "unstable-2024-04-17";

  src = ./..;

  patches = [ ../patches/allow-cc-override.patch ];
  preConfigure = ''
    mkdir home
    export PROJECT_HOME="$PWD/home"
  '';

  buildInputs = [ bintools ];

  makeFlags = [
    "CC=${stdenv.cc.targetPrefix}gcc"
    "AR=${stdenv.cc.targetPrefix}ar"
    "RANLIB=${stdenv.cc.targetPrefix}ranlib"
  ];

  installPhase = ''
    mkdir --parent -- $out/bin
    mv $PROJECT_HOME/bin/* $out/bin
  '';
  dontStrip = true;

  # TODO investigate why hardening causes crashes
  hardeningDisable = [ "all" ];
}
