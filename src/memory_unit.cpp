#include <memory_unit.hpp>
#include <cstdio>

namespace NES
{

MemoryUnit::MemoryUnit() {
    randAccMem = new Ram();
}

MemoryUnit::~MemoryUnit() {
    delete randAccMem;
}

uint16_t MemoryUnit::getNormalizedAddr(uint16_t addr, uint16_t *caseType) const{
    if (addr < 0x2000) {
        // Ram Access
        addr = addr % 0x0800;
        *caseType = 0;
        return addr;
    } else if (0x2000 <= addr && addr < 0x4000) {
        // PPU Reg Access
        *caseType = 1;
        addr = addr - 0x2000;
        addr = addr % 8;
        return addr;
    } else if (0x4000 <= addr && addr < 0x4018) {
        // APU and I/O registers
        *caseType = 2;
        return addr;
    } else if (0x4018 <= addr && addr < 0x4020) {
        // APU and I/O that is normally disabled
        *caseType = 3;
        return addr;
    } else {
        // Cartridge space address
        *caseType = 4;
        return addr;
    }
}

void MemoryUnit::setByteAt(uint16_t pos, uint8_t val) {
    uint16_t type = -1;
    pos = getNormalizedAddr(pos, &type);
    switch (type) {
        case 0:
            // RAM access
            randAccMem->setByteAt(pos, val);
            break;
        case 1:
            // PPU Access
            break;
        case 2:
            // APU and I/O access
            break;
        case 3:
            // APU and IO that is normally disabled
            break;
        case 4:
            // Cartridge Space access
            break;
    }
}

uint8_t MemoryUnit::getByteAt(uint16_t pos) const {
    uint16_t type = -1;
    pos = getNormalizedAddr(pos, &type);
    uint8_t ret = 0xFF;
    switch(type) {
        case 0:
            // RAM access
            ret = randAccMem->getByteAt(pos);
            break;
        case 1:
            // PPU Access
            break;
        case 2:
            // APU and I/O access
            break;
        case 3:
            // APU and IO that is normally disabled
            break;
        case 4:
            // Cartridge Space access
            break;
    }
    return ret;
}


} // NES
