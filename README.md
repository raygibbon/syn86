# SYN86

C11 + SDL3 + CART retro music and sound creation toolkit.

**Goal:** create original music and sound effects once, then export to multiple targets. Wolfenstein 3D is one target, not the application architecture. DOS/QBASIC games, PC Speaker, WAV and MIDI support are on the roadmap.

## v0.1 implemented

- Pinned emu8950 OPL2 emulator, copied from Wolf3D Revive with upstream attribution and local fixes.
- SDL3 interactive monophonic keyboard demo: Z S X D C V G B H N J M (C4 to B4).
- Native Wolf3D-style IMF type-1 demo exporter with original notes, no copyrighted game data.
- A headless test for the IMF binary encoding.

## Building on Linux

With a system SDL3 development package:

```sh
cc -std=c11 -O2 -Isrc -Ithird_party/emu8950 \
 src/main.c src/opl.c src/imf.c \
 third_party/emu8950/emu8950.c third_party/emu8950/emuadpcm.c \
 -o syn86 $(pkg-config --cflags --libs sdl3) -lm
./syn86
./syn86 demo.imf
```

With [CART](https://github.com/raygibbon/cart), configure a local SDL3 dependency (the default expected location is `vendor/SDL`) and run `cart build`. A `cart-sdl` profile points at `../cart/vendor/SDL`.

```sh
cc -std=c11 -Wall -Wextra -Werror -Isrc tests/imf_tests.c src/imf.c -o /tmp/syn86-imf-tests
/tmp/syn86-imf-tests
```

The IMF export is a proof of concept, **not yet** a song editor, general IMF importer, or Wolf3D archive builder. Refer to [roadmap](docs/ROADMAP.md) and [format notes](docs/FORMATS.md).

## Licensing

Application code is MIT-licensed. The bundled emu8950 is MIT-licensed by Mitsutaka Okazaki, with its original licence, provenance and Revive's defensive fixes preserved. No commercial game data is bundled.
