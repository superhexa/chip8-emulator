# CHIP-8 Emulator

A fast and accurate CHIP-8 emulator written in C using SDL2.

## What is CHIP-8?

CHIP-8 is a simple interpreted programming language developed in the 1970s for 8-bit microcomputers like the COSMAC VIP. It was designed to simplify game development on limited hardware. A CHIP-8 program typically consists of 35 opcodes (instructions), each 2 bytes long, and runs in a virtual machine environment with the following characteristics:

- 4 KB memory (starting from 0x000 to 0xFFF)
- 16 8-bit general-purpose registers (V0–VF)
- One 16-bit address register (I)
- A 64x32 monochrome display
- 16-key hexadecimal keypad (0–F)
- A program counter (PC) and stack for subroutines
- Built-in delay and sound timers

Many retro games were developed for CHIP-8, including Pong, Space Invaders, and Tetris clones. Because of its simplicity, it’s a popular target for emulator development.

## Features

- Full CHIP-8 instruction set support
- High compatibility with CHIP-8 games
- SDL2-based graphics and input
- Keyboard mapping for all 16 keys
- Adjustable execution timing

## Requirements

- C compiler (GCC or Clang)
- SDL2 development libraries

## Build

```bash
make
````

## Run

```bash
./chip8 roms/<game_name>.ch8
```

## Keyboard Mapping

| CHIP-8 Key | Mapped Key |
| ---------- | ---------- |
| 1 2 3 C    | 1 2 3 4    |
| 4 5 6 D    | Q W E R    |
| 7 8 9 E    | A S D F    |
| A 0 B F    | Z X C V    |

Some programs may also use:

* Arrow keys
* Enter
* Space

## Example Games

You can run any standard CHIP-8 ROM. Examples include:

* Pong
* Tetris
* Space Invaders
* Breakout

## License

MIT License – see [LICENSE](LICENSE)