#include "arinc429/label_database.hpp"

namespace arinc429 {
    
    bool LabelDatabase::add(const LabelDefinition& definition) {
        return false;
    }
    
    std::optional<LabelDefinition> LabelDatabase::find(std::uint8_t label) const {
        return std::nullopt;
    }
    
    std::size_t LabelDatabase::size() const {
        return 0;
    }
}
