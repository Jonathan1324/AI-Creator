#!/bin/bash

set -e

DENO_DIR="./tools"
DENO_BIN="$DENO_DIR/deno"

mkdir -p "$DENO_DIR"

if [ -f "$DENO_BIN" ]; then
    exit 0
fi

OS=$(uname -s)

if [ "$OS" = "Linux" ]; then
    PLATFORM="unknown-linux-gnu"
elif [ "$OS" = "Darwin" ]; then
    PLATFORM="apple-darwin"
else
    echo "Unsupported OS: $OS"
    exit 1
fi

DENO_VERSION="v2.2.11"
DENO_ZIP="deno-x86_64-$PLATFORM.zip"
DENO_URL="https://github.com/denoland/deno/releases/download/$DENO_VERSION/$DENO_ZIP"

curl -fsSL -o "$DENO_DIR/deno.zip" "$DENO_URL"

unzip -o "$DENO_DIR/deno.zip" -d "$DENO_DIR"
rm "$DENO_DIR/deno.zip"

chmod +x "$DENO_BIN"