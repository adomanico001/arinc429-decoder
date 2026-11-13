#include <gtest/gtest.h>
#include "arinc429/label_database.hpp"

TEST(LabelDatabase, DefinitionStartsWithDefaults) {
    arinc429::LabelDefinition definition;
    EXPECT_EQ(definition.label, 0);
    EXPECT_TRUE(definition.encoding == arinc429::Encoding::Bnr);
    EXPECT_EQ(definition.significant_bits, 0);
    EXPECT_EQ(definition.digit_count, 0);
    EXPECT_DOUBLE_EQ(definition.resolution, 0.0);
    EXPECT_TRUE(definition.name.empty());
    EXPECT_TRUE(definition.units.empty());
}

TEST(LabelDatabase, DefinitionStoresAltitudeValues) {
    arinc429::LabelDefinition altitude;
    altitude.label = 0x83;
    altitude.name = "Pressure Altitude";
    altitude.encoding = arinc429::Encoding::Bnr;
    altitude.significant_bits = 17;
    altitude.resolution = 1.0;
    altitude.units = "ft";
    
    EXPECT_EQ(altitude.label, 0x83);
    EXPECT_EQ(altitude.name, "Pressure Altitude");
    EXPECT_TRUE(altitude.encoding == arinc429::Encoding::Bnr);
    EXPECT_EQ(altitude.significant_bits, 17);
    EXPECT_DOUBLE_EQ(altitude.resolution, 1.0);
    EXPECT_EQ(altitude.units, "ft");
}
