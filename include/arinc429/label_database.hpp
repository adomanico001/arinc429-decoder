#ifndef ARINC429_LABEL_DATABASE_HPP
#define ARINC429_LABEL_DATABASE_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
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

    class LabelDatabase {
        public:
            bool add(const LabelDefinition& definition);
            std::optional<LabelDefinition> find(std::uint8_t label) const;
            std::size_t size() const;
    
        private:
            std::map<std::uint8_t, LabelDefinition> definitions_;
    };
}

#endif

