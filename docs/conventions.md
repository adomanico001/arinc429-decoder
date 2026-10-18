# Conventions

This document records the decisions needed to read and change this project's code correctly. Update it whenever a decision is made or changed.

## Bit Numbering

Bits are numbered **1 to 32**, matching the ARINC 429 specification. Bit 1 is the first label bit and bit 32 is the parity bit.

C++ shift amounts count from 0, so spec bit *n* sits at shift position *n - 1* in a `std::uint32_t`. For example, spec bit 11 (the first data bit) is at shift position 10.

All comments, tests, and documentation use the 1-32 numbering. Shift amounts in code are the only place 0-based positions appear.


## Word Layout

| Field | Bits | Width | Description |
| --- | --- | --- | --- |
| Label | 1-8 | 8 | Identifies the value carried, shown in octal |
| SDI | 9-10 | 2 | Source/Destination Identifier |
| Data | 11-29 | 19 | The value; for BNR, bit 29 is the sign |
| SSM | 30-31 | 2 | Sign/Status Matrix |
| Parity | 32 | 1 | Odd parity bit |

A word is stored as a single `std::uint32_t`.


## Parity

ARINC 429 uses **odd parity**. A valid word contains an odd number of 1s across all 32 bits, including the parity bit itself. The decoder only checks parity; only the encoder sets the parity bit.


## Label Display

Labels are always displayed as three-digit octal numbers, for example `203`.


## Label Bit Order

*To be decided in Step 4*
Open question: does the capture format store the label bits in transmitted order or reversed? The decoder must state which it expects and, ideally, support both.


# Byte Order

*To be decided in Step 8*
Open question: in a binary capture file, in what order are the 4 bytes of each word stored (little-endian or big-endian)?


## Naming and Style

| Item | Rule | Example |
| --- | --- | --- |
| File names | `snake_case` | `field_extraction` |
| Header extension | `.hpp` | `field_extraction.hpp` |
| Source extension | `.cpp` | `field_extraction.cpp` |
| Test files | `<base name>_test.cpp` | `field_extraction_test.cpp` |
| Test suite and test names | PascalCase, no underscores | `Parity.RejectsAllZerosWord` |
| Namespace | `arinc429` | |
| CMake targets | library `arinc429`, program `arinc429_cli`, tests `arinc429_tests` | |
| Indentation | 4 spaces, no tabs | |

Public headers live in `include/arinc429/` and are included with the project prefix, for example `arinc429/field_extraction.hpp`.
