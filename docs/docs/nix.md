# Nix

This project can also be built using [nix](https://nixos.org/).
The `nix/` directory contains all the necessarry files.

To just build the project, run e.g.

```sh
nix build -A massif2img nix/default.nix
```

The root directory contains a `shell.nix` file for quick use.
Just run `nix-shell`.