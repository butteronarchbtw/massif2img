# Installing

You might not need to install `massif2img` globally - refer to [the section on nix](nix.md), if you have nix installed.

Installing works as usual with CMake (refer to [Building](building.md) first).

Assuming `build/` is your build directory:

```sh
cmake --install build
```

Or, to specify another install directory, either set `CMAKE_INSTALL_PREFIX` during configuration or use

```
cmake --install <builddir> --prefix <prefix>
```