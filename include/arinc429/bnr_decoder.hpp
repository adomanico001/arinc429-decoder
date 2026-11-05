#ifndef ARINC429_BNR_DECODER_HPP
#define ARINC429_BNR_DECODER_HPP

#include "arinc429/field_extraction.hpp"

namespace arinc429 {

    double decode_bnr(Word data_field, int significant_bits, double resolution);
}

#endif
