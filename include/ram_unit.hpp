#ifndef RAM_H_
#define RAM_H_

#include <cstdint>

namespace NES
{

class Ram {
    const static uint32_t DEFAULT_SIZE = 0x0800;
    private:
        uint32_t size;
        uint8_t *memory;
    public:
        Ram(uint32_t sz = DEFAULT_SIZE);
        ~Ram();
        Ram(const Ram &);
        Ram &operator=(const Ram &);
        uint8_t getByteAt(uint16_t pos) const;
        void setByteAt(uint16_t pos, uint8_t val);
};

} // NES

#endif