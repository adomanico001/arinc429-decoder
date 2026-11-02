#include "arinc429/label.hpp"
#include <sstream>
#include <iomanip>

namespace arinc429 {
    std::uint8_t reverse_label_bits(std::uint8_t label) {
        std::uint8_t result = 0u;
        for (int i = 0; i < 8; i++) {
            result <<= 1;
            result |= (label & 0x01);
            label >>= 1;
        }
        return result;
    }
    
    std::string format_label_octal(std::uint8_t label) {
        std::ostringstream octal_label;
        
        octal_label << std::oct << std::setw(3) << std::setfill('0') << static_cast<unsigned 
            int>(label);
        return octal_label.str();
    }
}


