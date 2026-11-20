# SYN86 roadmap

One editing environment, multiple format exporters. No new proprietary sound format is required as an export format.

## v0.1 foundation
- [x] C11, SDL3 and CART config
- [x] Reuse pinned emu8950 from Wolf3D Revive
- [x] Keyboard playable OPL2 proof of concept
- [x] Original Wolf3D-compatible length-prefixed 700 Hz IMF demo export
- [x] Headless test for IMF encoding
- [ ] Verify build and sound on Debian 13

## v0.2 authoring
- [ ] Full nine-channel OPL2 instrument editor and presets
- [ ] Pattern tracker/piano roll, tempo, transport and loop tools
- [ ] Import/export IMF without losing register events
- [ ] Undo, redo and an editable project representation
- [ ] Deterministic offline audio rendering tests

## v0.3 target exporters
- [ ] Wolf3D AUDIOHED.WL6 and AUDIOT.WL6 import/export, preserving original chunk structure
- [ ] Wolf3D native AdLib sound effect editor
- [ ] DOS/QBASIC 700 Hz IMF playback example using safe timer servicing
- [ ] WAV rendering for modern games such as Ironclaw3D
- [ ] PC Speaker tone-sequence exporter

## Later
- [ ] MIDI import/export (with documentation of conversion limitations)
- [ ] OPL3 and other retro sound chips
- [ ] Native graphical instrument and song editing

## Architecture rules
- Audio authoring core independent of exporters and SDL UI
- A small documented native C API; headless testing
- No dependency on owning Wolfenstein 3D
- No copyrighted game assets bundled
- Validate produced output against target players before claiming compatibility
