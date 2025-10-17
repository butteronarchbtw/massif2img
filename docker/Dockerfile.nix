FROM ghcr.io/lix-project/lix:latest

WORKDIR /app
COPY . .
RUN nix  --experimental-features 'nix-command flakes' build
