# SYN86

C11 + SDL3 retro music and sound creation toolkit. Builds independently of CART.

**Goal:** create original music and sound effects once, then export to multiple targets. Wolfenstein 3D is one target, not the application architecture. DOS/QBASIC games, PC Speaker, WAV and MIDI support are on the roadmap.

## v0.1 implemented

- Pinned emu8950 OPL2 emulator, copied from Wolf3D Revive with upstream attribution and local fixes.
- SDL3 interactive monophonic keyboard demo: Z S X D C V G B H N J M (C4 to B4).
- Native Wolf3D-style IMF type-1 demo exporter with original notes, no copyrighted game data.
- A headless test for the IMF binary encoding.

## Building on Linux

Install a C11 compiler, SDL3 development headers and pkg-config, then:

```sh
./build.sh
./build/syn86
./build/syn86 demo.imf
```

For the standalone IMF encoding test:

```sh
./build.sh test
```

CART is a **private, optional developer convenience**, not a supported public prerequisite. The included `cart.toml` may be used locally with an independently supplied SDL3 checkout. Public builds do not need CART, and this project makes no assumption that CART will be published.

The IMF export is a proof of concept, **not yet** a song editor, general IMF importer, or Wolf3D archive builder. Refer to [roadmap](docs/ROADMAP.md) and [format notes](docs/FORMATS.md).

## Licensing

Application code is MIT-licensed. The bundled emu8950 is MIT-licensed by Mitsutaka Okazaki, with its original licence, provenance and Revive's defensive fixes preserved. No commercial game data is bundled.
