{
  pkgs,
  stdenv,
  lib,
  ...
}:
stdenv.mkDerivation {
  name = "massif2img-docs";
  src = lib.cleanSource ./.;
  buildInputs = with pkgs; [
    mkdocs
  ];
  buildPhase = ''
    mkdocs build
  '';
  installPhase = ''
    mkdir -p $out
    cp -r ./site/* $out
  '';
}
