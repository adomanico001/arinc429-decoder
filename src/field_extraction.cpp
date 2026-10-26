#include "arinc429/field_extraction.hpp"

namespace arinc429 {
    Word extract_label(Word word) {
        return word & 0xFF;
    }
    
    Word extract_sdi(Word word) {
        return (word >> 8) & 0x03;
    }
    
    Word extract_data(Word word) {
        return (word >> 10) & 0x7FFFF;
    }
    
    Word extract_ssm(Word word) {
        return (word >> 29) & 0x03;
    }
    
    Word extract_parity_bit(Word word) {
        return (word >> 31);
    }
}

