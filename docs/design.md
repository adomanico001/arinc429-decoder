# Design Notes

This document explains how the decoder is structured and why. Conventions such as bit numbering and naming rules are in [`conventions.md`](conventions.md).

## Overview

The project decodes ARINC 429 data words. Each word is 32 bits containing five fields: label, SDI, data, SSM and parity. The decoder splits a word into those fields, checks whether it can be trusted, and converts its data into an engineering value such as altitude in feet.

The code is split into a reusable library (`arinc429`), a command-line program (`arinc429_cli`), and a test suite (`arinc429-tests`).

## Components

| Component | Files | Responsibility |
| --- | --- | --- |
| Field extraction | `field_extraction.hpp/.ccp` | Defines the `Word` type and extracts the label, SDI, data, SSM, and parity bit from a word |
| Parity | `parity.hpp/.cpp` | Checks whether a word has odd parity across all 32 bits |
| Label | `label.hpp/.cpp` | Reverses label bit order and formats labels as three-digit octal text |
| BNR decoder | `bnr_decoder.hpp/cpp` | Converts a BNR data field into an engineering value using the label's significant bits and resolution |
| BCD decoder | `bcd_decoder.hpp/cpp` | Validates BCD digits and converts a BCD data field into an engineering value using the label's digit count and resolution |

Planned components: BCD decoding, a label database, capture file reading, an encoder, and table, CSV, and summary output.

## Design Decisions

### The decoder is a library, separate from the command-line program
All ARINC 429 logic lives in the `arinc429` library. The CLI and the tests both link to it, so they exercise exactly the same code, and the library can be used by other programs, such as a test harness or display, without the CLI. Nothing in the library depends on the CLI.

### A word is a 32-bit unsigned integer
`Word` is an alias for `std::uint32_t`. A fixed-width type guarantees exactly 32 bits on every platform, and an unsigned type treats bit 32 as an ordinary bit rather than a sign, which keeps shifts and masks predictable.

### Extraction and validation are separate
The extraction functions only pull bits out of a word; they do not judge whether the word is valid. Validation (parity now, SSM and range checks later) is handled by separate functions. Keeping these jobs apart makes each simpler to write, test, and reuse. For example, an all-zeros word extracts cleanly to all-zero fields but fails the parity check. 

### Fields are extracted by shifting, then masking
Every extraction function shifts the field down to bit 1, then masks it to the field's width. Because the shift happen first, each mask depends only on the field's width, not its position. All five functions follow the same pattern, which makes them easy to check against the word layout table.

### Labels are stored in  normal reading order 
Bit 8 holds the label's most significant bit, so the low byte of a word reads directly as the label value (`0x83` is the label 203). This keeps hex dumps easy to read. Captures from hardware that stores labels reversed can be converted with `reverse_label_bits`.

### Parity is checked by counting bits in a loop
`has_odd_parity` examines each of the 32 bits in turn and counts the 1s. Library alternatives exist (`std::bitset`, or `std::popcount` in C++20), but the explicit loop makes the behavior easy to follow and review. The tests would allow switching implementations later without changing behavior.

### The BNR decoder takes the data field and label parameters
`decode_bnr` takes the 19-bit data field rather than a whole word, plus the label's significant bits and resolution. This keeps the arithmetic independent of any specific label, so the same function can decode ever BNR label. Taking the data field rather than the word also makes the function simpler to test. The label database will supply each label's parameters.

### BNR values are returned as `double`
Decoded values can be negative or fractional, depending on the label's resolution, so `decode_bnr` returns a `double`. Many safety-critical systems avoid or restrict floating point because rounding behavior is harder to verify. For this project, `double` keeps the decoder simple and readable, and tests compare results with `EXPECT_DOUBLE_EQ` rather than exact equality. A fixed-point representation would be the more conservative choice for flight software.

### Tests use boundary values
Each component is tested with a known real example plus boundary cases chosen to expose specific bugs: all zeros, all ones, single-field words for extraction, single and double bit flips for parity, and zero, minus one, and both range extremes for BNR. Each test has a constant input with a descriptive name and a test name describing the expected behavior.

### BCD validation is separate from BCD decoding
`has_vaild_bcd_digits` checks that every digit used by a label is between 0 and 9, while `decode_bcd` converts the digits to a value and assumes they are valid. This follows the same principle as keeping field extraction separate from validation: each function has one job, which keeps both simpler to write and test. Callers are expected to check validity before decoding. Both functions take a digit count so that only the digits a label uses are checked or decoded; unused padding digits at the bottom of the field are ignored.

### Every BCD digit is extracted with the same 4-bit mask
Each digit is extracted by shifting the data field right (16, 12, 8, 4, then 0 bits) and masking with `0xF`. The most significant digit is only 3 bits wide, but the 4-bit mask is still safe for it: the data field is already limited to 19 bits by `extract_data`, so the bit above the top digit is always 0. Using one mask for every digit keeps the loop simple and identical in `decode_bcd` and `has_valid_bcd_digits`.

## Known Limitations

### BNR decoder does  not validate its parameters
`decode_bnr` assumes `significant_bits` is between 1 and 18. A larger value makes the padding count negative, and shifting by a negative amount is undefined behavior in C++. A value of 0 or less is also meaningless. Callers currently must pass valid values; in the label database (Step 7) these will come from checked label definitions. 

**Planned fix:** validate `significant_bits` and reject out-of-range values, with tests for the boundaries (0, 1, 1, 18, and 19).

### Parity cannot detect an even number of flipped bits
Odd parity detects any single-bit error but misses two flipped bits, since the count of 1s stays odd. This is a property of ARINC 429 itself, not a bug. The test `AcceptsWordWithTwoBitsFlipped` documents it. Later SSM and range checks provide additional protection.

### Label set is a sample from public references
The official ARINC 429 specification is not freely available. Label definitions, such as pressure altitude's 17 significant bits and 1 ft resolution, come from public tutorials and are a sample, not a complete or authoritative label database.
