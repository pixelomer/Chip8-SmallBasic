# Chip8 Emulator Written In SmallBasic

A Chip8 emulator written in Microsoft SmallBasic with just the official standard library.

## Files

### `Chip8.sb` file

Contains the emulator and UI code. Compile and run with a Microsoft SmallBasic IDE.

### `SmallBasicConverter.c` file

When a SmallBasic program attempts to read a binary file with non-ASCII characters, the file gets corrupted while reading. To get around this, a small C program is used to replace non-ASCII characters with multiple ASCII characters. This program can be compiled using most (if not all) C compilers (TinyCC is recommended). Usage can be found below.

```
Encode a Chip8 program called "program.c8" and save it to a new file called encoded.sbbin to be used by the emulator.

C:\> SmallBasicConverter.exe encode program.c8 encoded.sbbin
```

```
Decode the encoded program to get back the original file.

C:\> SmallBasicConverter.exe decode encoded.sbbin program.c8
```

All programs must be encoded using this converter before being used with the emulator.