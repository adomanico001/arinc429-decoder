#include <gtest/gtest.h>
#include "arinc429/field_extraction.hpp"

const arinc429::Word altitude_35000_ft = 0x6445C083u;
const arinc429::Word all_zeros = 0x00000000u;
const arinc429::Word all_ones = 0xFFFFFFFFu;
const arinc429::Word label_bits_only = 0x000000FFu;
const arinc429::Word sdi_bits_only = 0x00000300u;
const arinc429::Word data_bits_only = 0x1FFFFC00u;
const arinc429::Word ssm_bits_only = 0x60000000u;
const arinc429::Word parity_bit_only = 0x80000000u;

TEST(FieldExtraction, ExtractsLabel) {
    EXPECT_EQ(arinc429::extract_label(altitude_35000_ft), 0x83u);
}

TEST(FieldExtraction, ExtractsSDI) {
    EXPECT_EQ(arinc429::extract_sdi(altitude_35000_ft), 0u);
}

TEST(FieldExtraction, ExtractsData) {
    EXPECT_EQ(arinc429::extract_data(altitude_35000_ft), 0x11170u);
}

TEST(FieldExtraction, ExtractsSSM) {
    EXPECT_EQ(arinc429::extract_ssm(altitude_35000_ft), 3u);
}

TEST(FieldExtraction, ExtractsParity) {
    EXPECT_EQ(arinc429::extract_parity_bit(altitude_35000_ft), 0u);
}

// All-zeros edge case test
TEST(FieldExtraction, AllZerosWordGivesZeroInEveryField) {
    EXPECT_EQ(arinc429::extract_label(all_zeros), 0u);
    EXPECT_EQ(arinc429::extract_sdi(all_zeros), 0u);
    EXPECT_EQ(arinc429::extract_data(all_zeros), 0u);
    EXPECT_EQ(arinc429::extract_ssm(all_zeros), 0u);
    EXPECT_EQ(arinc429::extract_parity_bit(all_zeros), 0u);
}

// All-ones edge case test
TEST(FieldExtraction, AllOnesWordGivesMaxInEveryField) {
    EXPECT_EQ(arinc429::extract_label(all_ones), 0xFFu);
    EXPECT_EQ(arinc429::extract_sdi(all_ones), 0x03u);
    EXPECT_EQ(arinc429::extract_data(all_ones), 0x7FFFFu);
    EXPECT_EQ(arinc429::extract_ssm(all_ones), 0x03u);
    EXPECT_EQ(arinc429::extract_parity_bit(all_ones), 0x01u);
}

// Single-field edge case tests - expects the mask
TEST(FieldExtraction, LabelOnlyWordIsolatesLabel) {
    EXPECT_EQ(arinc429::extract_label(label_bits_only), 0xFFu);
    EXPECT_EQ(arinc429::extract_sdi(label_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_data(label_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_ssm(label_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_parity_bit(label_bits_only), 0u);
}

TEST(FieldExtraction, SDIOnlyWordIsolatesSDI) {
    EXPECT_EQ(arinc429::extract_label(sdi_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_sdi(sdi_bits_only), 0x03u);
    EXPECT_EQ(arinc429::extract_data(sdi_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_ssm(sdi_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_parity_bit(sdi_bits_only), 0u);
}

TEST(FieldExtraction, DataOnlyWordIsolatesData) {
    EXPECT_EQ(arinc429::extract_label(data_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_sdi(data_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_data(data_bits_only), 0x7FFFFu);
    EXPECT_EQ(arinc429::extract_ssm(data_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_parity_bit(data_bits_only), 0u);
}

TEST(FieldExtraction, SSMOnlyWordIsolatesSSM) {
    EXPECT_EQ(arinc429::extract_label(ssm_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_sdi(ssm_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_data(ssm_bits_only), 0u);
    EXPECT_EQ(arinc429::extract_ssm(ssm_bits_only), 0x03u);
    EXPECT_EQ(arinc429::extract_parity_bit(ssm_bits_only), 0u);
}

TEST(FieldExtraction, ParityOnlyWordIsolatesParity) {
    EXPECT_EQ(arinc429::extract_label(parity_bit_only), 0u);
    EXPECT_EQ(arinc429::extract_sdi(parity_bit_only), 0u);
    EXPECT_EQ(arinc429::extract_data(parity_bit_only), 0u);
    EXPECT_EQ(arinc429::extract_ssm(parity_bit_only), 0u);
    EXPECT_EQ(arinc429::extract_parity_bit(parity_bit_only), 0x01u);
}
