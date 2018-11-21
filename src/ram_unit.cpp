#include <ram_unit.hpp>


namespace NES
{

Ram::Ram(uint32_t sz) {
    size = sz;
    memory = new uint8_t[sz];
}

Ram::~Ram() {
    delete[] memory;
}

uint8_t Ram::getByteAt(uint16_t pos) const{
    return memory[pos];
}

void Ram::setByteAt(uint16_t pos, uint8_t val) {
    memory[pos] = val;
}

} // NES

