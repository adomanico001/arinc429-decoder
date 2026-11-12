#ifndef ARINC429_BCD_DECODER_HPP
#define ARINC429_BCD_DECODER_HPP

#include "arinc429/field_extraction.hpp"

namespace arinc429 {

    bool has_valid_bcd_digits(Word data_field, int digit_count);

    double decode_bcd(Word data_field, int digit_count, double resolution);
}

#endif
