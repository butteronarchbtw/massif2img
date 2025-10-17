{
  stdenv,
  lib,
  pkgs,
}:
stdenv.mkDerivation rec {
  pname = "massif2img";
  version = "0.0.1";
  src = lib.cleanSourceWith {
    src = lib.cleanSource ./..;
    filter =
      name: type:
      let
        baseName = baseNameOf name;
      in
      baseName != "build";
  };
  buildInputs = [ ];
  nativeBuildInputs = with pkgs; [
    cmake
    ninja
  ];
  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DBUILD_TESTS=OFF"
    "-G Ninja"
  ];
  configurePhase = ''
    	cmake -B build ${toString cmakeFlags} -DCMAKE_INSTALL_PREFIX=$out
  '';
  buildPhase = ''
    	cmake --build build
  '';
  installPhase = ''
    	cmake --install build
  '';
}
