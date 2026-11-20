#!/bin/sh
set -eu
cd "$(dirname "$0")"
mkdir -p build
if [ "${1:-}" = test ]; then
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Isrc tests/imf_tests.c src/imf.c -o build/imf_tests
    exec ./build/imf_tests
fi
if [ "${1:-}" != "" ]; then
    echo "Usage: ./build.sh [test]" >&2
    exit 2
fi
pkg-config --exists sdl3 || { echo "SDL3 development package required (pkg-config sdl3)" >&2; exit 1; }
# Intentionally split pkg-config arguments for the compiler invocation.
# shellcheck disable=SC2046
"${CC:-cc}" -std=c11 -O2 -Wall -Wextra -Isrc -Ithird_party/emu8950 \
 src/main.c src/opl.c src/imf.c \
 third_party/emu8950/emu8950.c third_party/emu8950/emuadpcm.c \
 -o build/syn86 $(pkg-config --cflags --libs sdl3) -lm
echo "Built build/syn86"
