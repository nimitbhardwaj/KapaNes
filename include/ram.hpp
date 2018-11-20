#ifndef RAM_HPP_
#define RAM_HPP_

#include <cstdint>

namespace NES 
{


class Ram{
    private:

    public:
        Ram(uint32_t size);
        Ram();
        uint8_t getByteAt(uint16_t pos) const;
        void setByteAt(uint16_t pos, uint8_t val);
};


}
#endif