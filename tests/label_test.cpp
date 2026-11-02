#include <gtest/gtest.h>
#include "arinc429/label.hpp"

const std::uint8_t label_203 = 0x83;
const std::uint8_t label_203_reversed = 0xC1;
const std::uint8_t low_bit_only = 0x01;
const std::uint8_t high_bit_only = 0x80;
const std::uint8_t all_zeros = 0x00;
const std::uint8_t all_ones = 0xFF;
const std::uint8_t label_007 = 0x07;

// Reversal Tests
TEST(Label, ReversesLabel203) {
    EXPECT_EQ(arinc429::reverse_label_bits(label_203), label_203_reversed);
}

TEST(Label, ReversesSingleLowBit) {
    EXPECT_EQ(arinc429::reverse_label_bits(low_bit_only), high_bit_only);
}

TEST(Label, ReversesSingleHighBit) {
    EXPECT_EQ(arinc429::reverse_label_bits(high_bit_only), low_bit_only);
}

TEST(Label, ReversingZerosGivesZeros) {
    EXPECT_EQ(arinc429::reverse_label_bits(all_zeros), all_zeros);
}

TEST(Label, ReversingOnesGivesOnes) {
    EXPECT_EQ(arinc429::reverse_label_bits(all_ones), all_ones);
}

TEST(Label, ReversingTwiceGivesOriginal) {
    EXPECT_EQ(arinc429::reverse_label_bits(arinc429::reverse_label_bits(label_203)), label_203);
}

// Formatting Tests
TEST(Label, FormatsLabel203) {
    EXPECT_EQ(arinc429::format_label_octal(label_203), "203");
}

TEST(Label, FormatsMaxLabel) {
    EXPECT_EQ(arinc429::format_label_octal(all_ones), "377");
}

TEST(Label, FormatsWithLeadingZeros) {
    EXPECT_EQ(arinc429::format_label_octal(label_007), "007");
}




