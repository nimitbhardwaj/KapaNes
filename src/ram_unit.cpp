#include <ram_unit.hpp>
#include <cstring>

namespace NES
{

Ram::Ram(uint32_t sz) {
    size = sz;
    memory = new uint8_t[sz];
    memset(memory, 0, sz*sizeof(uint8_t));
}

Ram::~Ram() {
    delete[] memory;
}

Ram::Ram(const Ram &r) {
    size = r.size;
    memory = new uint8_t[size];
    memcpy(memory, r.memory, size*sizeof(uint8_t));
}

Ram &Ram::operator=(const Ram &r) {
    size = r.size;
    memory = new uint8_t[size];
    memcpy(memory, r.memory, size*sizeof(uint8_t));
    return *this;
}


uint8_t Ram::getByteAt(uint16_t pos) const{
    return memory[pos];
}

void Ram::setByteAt(uint16_t pos, uint8_t val) {
    memory[pos] = val;
}

} // NES

