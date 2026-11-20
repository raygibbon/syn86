# Formats

## IMF type 1: initial export
A 16-bit little-endian byte length is followed by 4-byte events: `register, value, delay_low, delay_high`. Delay is in Wolfenstein's 700 Hz ticks and follows the register write. The payload byte length excludes the 2-byte prefix.

IMF is a stream of OPL register writes, **not** MIDI. It has no separate instrument definitions. Other IMF players may use different timing conventions.

## Wolfenstein audio archives: planned
`AUDIOHED.WL6` stores offsets into `AUDIOT.WL6`; the latter contains PC Speaker, AdLib and IMF music chunks. Digitised sound samples are stored in `VSWAP.WL6` alongside artwork. Replacing Wolf3D music will require a safe archive writer; a bare IMF cannot simply be renamed to AUDIOT.

## DOS/QBASIC: planned
AdLib hardware uses I/O ports 0x388 and 0x389. Streaming a 700 Hz IMF song needs a reliable timer service. Standard QBASIC TIMER alone is not sufficiently precise.

## Modern game audio: planned
WAV output could capture emu8950 PCM. MIDI is note-oriented and cannot always losslessly represent arbitrary OPL register automation.
