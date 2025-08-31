FROM nixos/nix

RUN nix-channel --update
WORKDIR /app
COPY . .
RUN nix-build -A massif2img nix/default.nix
