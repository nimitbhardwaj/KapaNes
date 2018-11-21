#ifndef ABSTRACT_UNIT_HPP_
#define ABSTRACT_UNIT_HPP_

#include <cstdint>

namespace NES
{


class AbstractUnit {
    public:
        virtual uint8_t getByteAt(uint16_t pos) const = 0;
        virtual void setByteAt(uint16_t pos, uint8_t val) = 0;

};


}
#endif