// decode_bnr takes output of `extract_data` (data fields), not a full 32-bit word

#include "arinc429/bnr_decoder.hpp"

namespace arinc429 {

    double decode_bnr(Word data_field, int significant_bits, double resolution) {
        std::int32_t raw = static_cast<std::int32_t>(data_field);
    
        if ((data_field & 0x40000) != 0) {
            raw -= 524288;
        }
        
        int padding_bits = 18 - significant_bits;

        double scale = resolution / static_cast<double>(1u << padding_bits);
        
        return raw * scale;
    }
}
