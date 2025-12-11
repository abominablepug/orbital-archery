#!/usr/bin/env bash
set -euo pipefail

# Simple helper to compile and run main.cpp (raylib program).
# Usage: ./run.sh

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRCS="$DIR/main.cpp $DIR/particle.cpp"
OUT="$DIR/main"

echo "Compiling $SRCS -> $OUT"

if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists raylib; then
  echo "Using pkg-config to get raylib flags"
  PKG_CFLAGS=$(pkg-config --cflags raylib)
  PKG_LIBS=$(pkg-config --libs raylib)
  g++ -std=c++17 $PKG_CFLAGS $SRCS -o "$OUT" $PKG_LIBS
else
  echo "pkg-config or raylib not found; using fallback link flags"
  g++ -std=c++17 $SRCS -o "$OUT" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
fi

# Determine libdir for runtime; prefer pkg-config value, fallback to /usr/local/lib
LIBDIR=""
if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists raylib; then
  LIBDIR=$(pkg-config --variable=libdir raylib 2>/dev/null || true)
fi
LIBDIR=${LIBDIR:-/usr/local/lib}

export LD_LIBRARY_PATH="$LIBDIR:${LD_LIBRARY_PATH:-}"

echo "Running $OUT with LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
exec "$OUT"
