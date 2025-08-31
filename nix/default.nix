{
  pkgs ? import <nixpkgs> { },
}:
{
  massif2img = pkgs.callPackage ./massif2img.nix {};
}
