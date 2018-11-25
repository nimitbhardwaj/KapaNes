#ifndef MEMORYUNIT_HPP_
#define MEMORYUNIT_HPP_

#include <cstdint>
#include <ram_unit.hpp>

namespace NES 
{


class MemoryUnit{
    private:
        Ram *randAccMem;
        uint16_t getNormalizedAddr(uint16_t, uint16_t *) const;
    public:
        MemoryUnit();
        ~MemoryUnit();
        uint8_t getByteAt(uint16_t pos) const;
        void setByteAt(uint16_t pos, uint8_t val);
};


}
#endif