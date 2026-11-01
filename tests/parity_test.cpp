#include <gtest/gtest.h>
#include "arinc429/parity.hpp"

const arinc429::Word altitude_35000_ft = 0x6445C083u;
const arinc429::Word all_zeros = 0x00000000u;
const arinc429::Word all_ones = 0xFFFFFFFFu;
const arinc429::Word altitude_parity_bit_flipped = 0xE445C083u;
const arinc429::Word altitude_bit_one_flipped = 0x6445C082u;
const arinc429::Word altitude_two_bits_flipped = 0x6445C080u;

TEST(Parity, AcceptsValidAltitudeWord) {
    EXPECT_TRUE(arinc429::has_odd_parity(altitude_35000_ft));
}

TEST(Parity, RejectsAllZerosWord) {
    EXPECT_FALSE(arinc429::has_odd_parity(all_zeros));
}

TEST(Parity, RejectsAllOnesWord) {
    EXPECT_FALSE(arinc429::has_odd_parity(all_ones));
}

TEST(Parity, RejectsFlippedParityBit) {
    EXPECT_FALSE(arinc429::has_odd_parity(altitude_parity_bit_flipped));
}

TEST(Parity, RejectsFlippedLabelBit) {
    EXPECT_FALSE(arinc429::has_odd_parity(altitude_bit_one_flipped));
}

TEST(Parity, AcceptsWordWithTwoBitsFlipped) {
    EXPECT_TRUE(arinc429::has_odd_parity(altitude_two_bits_flipped));
}
