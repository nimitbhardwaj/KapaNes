#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>

#include "include/test_ram_unit.hpp"
#include "include/test_memory_unit.hpp"
#include "include/test_cpu.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION( RamUnitTest );
CPPUNIT_TEST_SUITE_REGISTRATION( MemoryUnitTest );
CPPUNIT_TEST_SUITE_REGISTRATION( CPUTest );

int main( int argc, char **argv)
{
    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run();

    return 0;
}
