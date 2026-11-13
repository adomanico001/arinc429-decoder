#include "arinc429/bcd_decoder.hpp"

namespace arinc429 {

    bool has_valid_bcd_digits(Word data_field, int digit_count) {
        for (int i = 0; i < digit_count; i++) {
            int shift = 16 - (4 * i);
            std::uint32_t digit = (data_field>>shift) & 0xF;
        
            if (digit > 9) {
                return false;
            }
        }
        
            return true;
    }
    
    double decode_bcd(Word data_field, int digit_count, double resolution) {
        std::uint32_t value = 0;
        for (int i = 0; i < digit_count; i++) {
            int shift = 16 - (4 * i);
            std::uint32_t digit = (data_field>>shift) & 0xF;
            value = (value * 10) + digit;
        }
        
        return static_cast<double>(value) * resolution;
    }

}
