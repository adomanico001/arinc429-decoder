#ifndef ARINC429_FIELD_EXTRACTION_HPP
#define ARINC429_FIELD_EXTRACTION_HPP

#include <cstdint>

namespace arinc429 {
    using Word = std::uint32_t;
    
    Word extract_label(Word word);
    Word extract_sdi(Word word);
    Word extract_data(Word word);
    Word extract_ssm(Word word);
    Word extract_parity_bit(Word word);
}

#endif
