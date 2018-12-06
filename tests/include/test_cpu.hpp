#ifndef CPP_UNIT_CPU_HPP
#define CPP_UNIT_CPU_HPP


#include <cpu.hpp>
#include <memory_unit.hpp>

#include <cppunit/extensions/HelperMacros.h>


using namespace NES;


class CPUTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( CPUTest );
        
        CPPUNIT_TEST( testFlags );
    // ORA
        CPPUNIT_TEST( testOraIndX );
        CPPUNIT_TEST( testOraZeroPg );
        CPPUNIT_TEST( testOraImm );
        CPPUNIT_TEST( testOraAbsolute );
        CPPUNIT_TEST( testOraIndirectY );
        CPPUNIT_TEST( testOraZeroPgX );
        CPPUNIT_TEST( testOraAbsY );
        CPPUNIT_TEST( testOraAbsX );
    // AND
        CPPUNIT_TEST( testAndIndX );
        CPPUNIT_TEST( testAndZeroPg );
        CPPUNIT_TEST( testAndImm );
        CPPUNIT_TEST( testAndAbsolute );
        CPPUNIT_TEST( testAndIndirectY );
        CPPUNIT_TEST( testAndZeroPgX );
        CPPUNIT_TEST( testAndAbsY );
        CPPUNIT_TEST( testAndAbsX );
    // EOR
        CPPUNIT_TEST( testEorIndX );
        CPPUNIT_TEST( testEorZeroPg );
        CPPUNIT_TEST( testEorImm );
        CPPUNIT_TEST( testEorAbsolute );
        CPPUNIT_TEST( testEorIndirectY );
        CPPUNIT_TEST( testEorZeroPgX );
        CPPUNIT_TEST( testEorAbsY );
        CPPUNIT_TEST( testEorAbsX );
    // EOR
        CPPUNIT_TEST( testAdcIndX );
        CPPUNIT_TEST( testAdcZeroPg );
        CPPUNIT_TEST( testAdcImm );
        CPPUNIT_TEST( testAdcAbsolute );
        CPPUNIT_TEST( testAdcIndirectY );
        CPPUNIT_TEST( testAdcZeroPgX );
        CPPUNIT_TEST( testAdcAbsY );
        CPPUNIT_TEST( testAdcAbsX );
    // STA
        CPPUNIT_TEST( testStaIndX );
        CPPUNIT_TEST( testStaZeroPg );
        CPPUNIT_TEST( testStaImm );
        CPPUNIT_TEST( testStaAbsolute );
        CPPUNIT_TEST( testStaIndirectY );
        CPPUNIT_TEST( testStaZeroPgX );
        CPPUNIT_TEST( testStaAbsY );
        CPPUNIT_TEST( testStaAbsX );
    // LDA
        CPPUNIT_TEST( testLdaIndX );
        CPPUNIT_TEST( testLdaZeroPg );
        CPPUNIT_TEST( testLdaImm );
        CPPUNIT_TEST( testLdaAbsolute );
        CPPUNIT_TEST( testLdaIndirectY );
        CPPUNIT_TEST( testLdaZeroPgX );
        CPPUNIT_TEST( testLdaAbsY );
        CPPUNIT_TEST( testLdaAbsX );
    // LDA
        // CPPUNIT_TEST( testCmpIndX );
        // CPPUNIT_TEST( testCmpZeroPg );
        CPPUNIT_TEST( testCmpImm );
        // CPPUNIT_TEST( testCmpAbsolute );
        // CPPUNIT_TEST( testCmpIndirectY );
        // CPPUNIT_TEST( testCmpZeroPgX );
        // CPPUNIT_TEST( testCmpAbsY );
        // CPPUNIT_TEST( testCmpAbsX );

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
        void testFlags();
        //ORA
        void testOraIndX();
        void testOraZeroPg();
        void testOraImm();
        void testOraAbsolute();
        void testOraIndirectY();
        void testOraZeroPgX();
        void testOraAbsY();
        void testOraAbsX();
        //AND
        void testAndIndX();
        void testAndZeroPg();
        void testAndImm();
        void testAndAbsolute();
        void testAndIndirectY();
        void testAndZeroPgX();
        void testAndAbsY();
        void testAndAbsX();
        //EOR
        void testEorIndX();
        void testEorZeroPg();
        void testEorImm();
        void testEorAbsolute();
        void testEorIndirectY();
        void testEorZeroPgX();
        void testEorAbsY();
        void testEorAbsX();
        //ADC
        void testAdcIndX();
        void testAdcZeroPg();
        void testAdcImm();
        void testAdcAbsolute();
        void testAdcIndirectY();
        void testAdcZeroPgX();
        void testAdcAbsY();
        void testAdcAbsX();
        //STA
        void testStaIndX();
        void testStaZeroPg();
        void testStaImm();
        void testStaAbsolute();
        void testStaIndirectY();
        void testStaZeroPgX();
        void testStaAbsY();
        void testStaAbsX();
        //LDA
        void testLdaIndX();
        void testLdaZeroPg();
        void testLdaImm();
        void testLdaAbsolute();
        void testLdaIndirectY();
        void testLdaZeroPgX();
        void testLdaAbsY();
        void testLdaAbsX();
        //CMP
        void testCmpIndX();
        void testCmpZeroPg();
        void testCmpImm();
        void testCmpAbsolute();
        void testCmpIndirectY();
        void testCmpZeroPgX();
        void testCmpAbsY();
        void testCmpAbsX();

};

#endif