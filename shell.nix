{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  packages = [
    (import ./nix/default.nix { }).massif2img
  ];

  shellHook = ''
        	alias rm="rm -v"
        	alias mv="mv -v"
        	alias cp="cp -v"
    		alias mkdir="mkdir -v"
  '';
}
