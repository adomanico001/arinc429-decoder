#ifndef ARINC429_LABEL_HPP
#define ARINC429_LABEL_HPP

#include <cstdint>
#include <string>

namespace arinc429 {
    
    std::uint8_t reverse_label_bits(std::uint8_t label);
    std::string format_label_octal(std::uint8_t label);
}

#endif
