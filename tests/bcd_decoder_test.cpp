#include <gtest/gtest.h>
#include "arinc429/bcd_decoder.hpp"

const arinc429::Word bcd_12345_field = 0x12345u;
const arinc429::Word bcd_zero_field = 0x00000u;
const arinc429::Word bcd_max_field = 0x79999u;
const arinc429::Word bcd_123_padded_field = 0x12300u;
const arinc429::Word bcd_invalid_digit_field = 0x1234Au;
const int five_digits = 5;
const int three_digits = 3;
const double unit_resolution = 1.0;
const double tenth_resolution = 0.1;

TEST(BcdDecoder, Decodes12345) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bcd(bcd_12345_field, five_digits, unit_resolution), 12345.0);
}

TEST(BcdDecoder, DecodesZero) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bcd(bcd_zero_field, five_digits, unit_resolution), 0.0);
}

TEST(BcdDecoder, DecodesMaximum) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bcd(bcd_max_field, five_digits, unit_resolution), 79999.0);
}

TEST(BcdDecoder, IgnoresPaddingDigits) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bcd(bcd_123_padded_field, three_digits, unit_resolution), 123.0);
}

TEST(BcdDecoder, AppliesResolution) {
    EXPECT_DOUBLE_EQ(arinc429::decode_bcd(bcd_12345_field, five_digits, tenth_resolution), 1234.5);
}

TEST(BcdDecoder, AcceptsValidDigits) {
    EXPECT_TRUE(arinc429::has_valid_bcd_digits(bcd_12345_field, five_digits));
}

 TEST(BcdDecoder, RejectsDigitAboveNine) {
    EXPECT_FALSE(arinc429::has_valid_bcd_digits(bcd_invalid_digit_field, five_digits));
}  
    
    
    
    
    
    
    
    
    
    
    
    
