#ifndef ARINC429_LABEL_DATABASE_HPP
#define ARINC429_LABEL_DATABASE_HPP

#include <cstdint>
#include <string>

namespace arinc429 {

    enum class Encoding {Bnr, Bcd};
    
    struct LabelDefinition {
        std::uint8_t label = 0;
        std::string name;
        Encoding encoding = Encoding::Bnr;
        int significant_bits = 0;
        int digit_count = 0;
        double resolution = 0.0;
        std::string units;
    };

}



#endif

