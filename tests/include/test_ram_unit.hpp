#ifndef CPP_UNIT_RAM_UNIT_HPP
#define CPP_UNIT_RAM_UNIT_HPP


#include <ram_unit.hpp>

#include <cppunit/extensions/HelperMacros.h>


using namespace NES;


class RamUnitTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( RamUnitTest );
        CPPUNIT_TEST( testGetByteAt );
        CPPUNIT_TEST( testSetByteAt );
    CPPUNIT_TEST_SUITE_END();


    private:
        Ram *r;
    public:
        void setUp() {
            r = new Ram();
        }

        void tearDown() {
            delete r;
        }

        void testGetByteAt();
        void testSetByteAt();
};

#endif