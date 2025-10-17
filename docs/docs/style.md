# Style

C++ code style is enforced using `clangd` rules (found in `.clangd`), `clang-format` rules (found in `.clang-format`) and `cppcheck`.
To check whether the code adheres to the specified guidelines, there is a script `scripts/check-format.sh`, which checks the code using `clang-format` and `cppcheck`.

To format nix files, `nixfmt-rfc-style` is used as a formatter in `flake.nix`.
A script to format all nix files is found at `scripts/format-nix.sh` and should be run after making any changes to the nix files.
