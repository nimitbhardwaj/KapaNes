#include "../include/test_ram_unit.hpp"

void RamUnitTest::testGetByteAt() {
    r->setByteAt(0x0011, 0x11);
    CPPUNIT_ASSERT(r->getByteAt(0x0011) == 0x11);
}
void RamUnitTest::testSetByteAt() {
    r->setByteAt(0x0011, 0x11);
    r->setByteAt(0x0011, 0x22);
    CPPUNIT_ASSERT(r->getByteAt(0x0011) == 0x22);
}
