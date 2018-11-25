#ifndef CPP_UNIT_CPU_HPP
#define CPP_UNIT_CPU_HPP


#include <cpu.hpp>
#include <memory_unit.hpp>

#include <cppunit/extensions/HelperMacros.h>


using namespace NES;


class CPUTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( CPUTest );
        CPPUNIT_TEST( testOraImm );
        CPPUNIT_TEST( testOraIndX );
        CPPUNIT_TEST( testOraZeroPg );
        CPPUNIT_TEST( testOraAbsolute );
        CPPUNIT_TEST( testOraIndirectY );
        CPPUNIT_TEST( testOraZeroPgX );
        CPPUNIT_TEST( testOraAbsY );
        CPPUNIT_TEST( testOraAbsX );
        
    CPPUNIT_TEST_SUITE_END();


    private:
        MemoryUnit *mem;
        CPU *cpu;
    public:
        void setUp() {
            mem = new MemoryUnit();
            cpu = new CPU();
        }

        void tearDown() {
            delete mem;
            delete cpu;
        }

        void testOraIndX();
        void testOraZeroPg();
        void testOraImm();
        void testOraAbsolute();
        void testOraIndirectY();
        void testOraZeroPgX();
        void testOraAbsY();
        void testOraAbsX();
};

#endif