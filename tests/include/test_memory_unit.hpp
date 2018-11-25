#ifndef CPP_UNIT_MEMORY_UNIT_HPP
#define CPP_UNIT_MEMORY_UNIT_HPP


#include <memory_unit.hpp>

#include <cppunit/extensions/HelperMacros.h>


using namespace NES;


class MemoryUnitTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( MemoryUnitTest );
        CPPUNIT_TEST( testGetByteAtRam );
        CPPUNIT_TEST( testSetByteAtRam );
    CPPUNIT_TEST_SUITE_END();


    private:
        MemoryUnit *mem;
    public:
        void setUp() {
            mem = new MemoryUnit();
        }

        void tearDown() {
            delete mem;
        }

        void testGetByteAtRam();
        void testSetByteAtRam();
};

#endif