#include <gtest/gtest.h>
#include "arinc429/bnr_decoder.hpp"

const arinc429::Word altitude_35000_field = 0x11170u;
const arinc429::Word zero_field = 0x00000u;
const arinc429::Word minus_one_field = 0x7FFFEu;  // -1 ft
const arinc429::Word most_negative_field = 0x40000u;
const arinc429::Word most_positive_field = 0x3FFFEu;  // largest positive value: 131,071 ft
const int altitude_significant_bits = 17;
const double altitude_resolution = 1.0;


TEST(BnrDecoder, DecodesAltitude35000) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bnr(altitude_35000_field, altitude_significant_bits, altitude_resolution), 35000.0);
}

TEST(BnrDecoder, DecodesZero) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bnr(zero_field, altitude_significant_bits, altitude_resolution), 0.0);
}

TEST(BnrDecoder, DecodesMinusOne) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bnr(minus_one_field, altitude_significant_bits, altitude_resolution), -1.0);
}

TEST(BnrDecoder, DecodesMostNegative) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bnr(most_negative_field, altitude_significant_bits, altitude_resolution), -131072.0);
}

TEST(BnrDecoder, DecodesMostPositive) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bnr(most_positive_field, altitude_significant_bits, altitude_resolution), 131071.0);
}
