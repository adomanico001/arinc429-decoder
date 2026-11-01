#include "arinc429/parity.hpp"

namespace arinc429 {
    bool has_odd_parity(Word word) {
        int counter = 0;
        for (int i = 0; i < 32; i++) {
            counter += (word & 0x01);
            word >>= 1;
        }
        return ((counter % 2) == 1);
    }
}
