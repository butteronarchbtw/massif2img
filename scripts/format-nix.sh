#!/usr/bin/env bash

if [[ -z "$(command -v "nix")" ]]; then
    echo "skipping: nix not found"
    exit 0
fi

find . -type f -name "*.nix" ! -name "Dockerfile.nix" -exec nix fmt --quiet {} +
