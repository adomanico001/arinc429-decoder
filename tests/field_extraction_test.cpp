#include <gtest/gtest.h>
#include "arinc429/field_extraction.hpp"

const arinc429::Word altitude_35000_ft = 0x6445C083;

TEST(FieldExtraction, ExtractsLabel) {
    EXPECT_EQ(arinc429::extract_label(altitude_35000_ft), 0x83u);
}

TEST(FieldExtraction, ExtractsSDI) {
    EXPECT_EQ(arinc429::extract_sdi(altitude_35000_ft), 0u);
}

TEST(FieldExtraction, ExtractsSSM) {
    EXPECT_EQ(arinc429::extract_ssm(altitude_35000_ft), 3u);
}

TEST(FieldExtraction, ExtractsData) {
    EXPECT_EQ(arinc429::extract_data(altitude_35000_ft), 0x11170u);
}

TEST(FieldExtraction, ExtractsParity) {
    EXPECT_EQ(arinc429::extract_parity_bit(altitude_35000_ft), 0u);
}
