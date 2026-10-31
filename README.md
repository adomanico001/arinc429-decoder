# ARINC 429 Decoder

A command-line tool and C++17 library that decodes and encodes ARINC 429 avionics data words, with parity, status (SSM), and range validation.
> **Status:** In development. The build system, test framework, and project layout are in place. Decoding features are being added one milestone at a time (see [Roadmap](#roadmap)).
    
## About

ARINC 429 is the most widely used data bus in commercial and military avionics. It carries values such as altitude, airspeed, and heading between aircraft systems. Every message is a single 32-bit word made up of five fields: label, SDI, data, SSM, and parity.

This project reads captured ARINC 429 words from a file, splits each word into its fields, decodes the data into engineering values, and flags any word that should not be trusted. In avionics, a wrong value that looks right is worse than no value, so the decoder reports bad data instead of passing it along.

## Planned Features

- Decode BNR (binary) and BCD (binary-coded decimal) labels into values with units
- Validate every word: odd parity, SSM status, unknown labels, and out-of-range values
- Read binary captures and hex-text captures (one word per line)
- Load label definitions from a config file instead of hard-coding them
- Encode values into valid words, with round-trip tests for every label
- Output a readable table on screen or CSV for spread sheets
- Summary report of counts per label and errors by type

## Requirements

- Linux (developed and tested on Ubuntu)
- Git
- CMake 4.2.3 or newer
- A C++17 compiler (GCC or Clang)

GoogleTest does not need to be installed. CMake downloads a pinned release (v1.18.0) automatically the first time you configure the project.

## Build and Test

Clone the repository:

```bash
git clone https://github.com/adomanico/arinc429-decoder.git
cd arinc429-decoder
```

Configure, build, and run the tests (all commands run from the repository's top folder):

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

The first configure takes a little longer while GoogleTest downloads.

Run the command-line tool:

```bash
./build/arinc429_cli
```

To start over from a clean state, delete the `build` folder and run the three build commands again.

## Conventions

- **Bit numbering:** bits are numbered 1 to 32, matching the ARINC 429 specification. Bit 1 is the first label bit and bit 32 is the parity bit.
- **Parity:** odd. A valid word always contains an odd number of 1s across all 32 bits.
- **Label display:** labels are shown as three-digit octal numbers (for example, 203).

See [`docs/conventions.md`](docs/conventions.md) for label bit order, byte order, and naming rules.

## Project Layout

| Folder | Contents |
| --- | --- |
| `include/arinc429/` | Public headers for the decoder library |
| `src/` | Library source files |
| `cli/` | Command-line program (`main.cpp` and on-screen table output) |
| `tests/` | GoogleTest unit tests, one file per library component |
| `data/` | Label database and sample capture files |
| `docs/` | Conventions and design notes |

The decoder logic lives in a library (`arinc429`) so the command-line program and the tests share the same code. Nothing in the library depends on the command-line program.

## Roadmap

- [x] Project skeleton: CMake build, GoogleTest, folder layout
- [x] Represent a word and extract its fields
- [ ] Check parity
- [ ] Convert and display labels in octal
- [ ] Decode BNR values
- [ ] Decode BCD values
- [ ] Load the label database
- [ ] Read binary and hex-text capture files
- [ ] Encode values into words, with round-trip tests
- [ ] Table, CSV, and summary output
- [ ] CI, static analysis, and test coverage

## References

The official ARINC 429 specification is published by SAE ITC and is not freely available. This project is built from publicly available tutorials and documentation. Its label set is a sample built from public references, not a complete or authoritative label database.

