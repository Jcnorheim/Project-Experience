/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "scanner_tests.h"

static ScannerTestSuite suite_ScannerTestSuite;

static CxxTest::List Tests_ScannerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScannerTestSuite( "scanner_tests.h", 8, "ScannerTestSuite", suite_ScannerTestSuite, Tests_ScannerTestSuite );

static class TestDescription_ScannerTestSuite_test_noScan : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_noScan() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 12, "test_noScan" ) {}
 void runTest() { suite_ScannerTestSuite.test_noScan(); }
} testDescription_ScannerTestSuite_test_noScan;

static class TestDescription_ScannerTestSuite_test_oneScan : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_oneScan() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 17, "test_oneScan" ) {}
 void runTest() { suite_ScannerTestSuite.test_oneScan(); }
} testDescription_ScannerTestSuite_test_oneScan;

static class TestDescription_ScannerTestSuite_test_twoScan : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_twoScan() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 23, "test_twoScan" ) {}
 void runTest() { suite_ScannerTestSuite.test_twoScan(); }
} testDescription_ScannerTestSuite_test_twoScan;

static class TestDescription_ScannerTestSuite_test_threeScan : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_threeScan() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 32, "test_threeScan" ) {}
 void runTest() { suite_ScannerTestSuite.test_threeScan(); }
} testDescription_ScannerTestSuite_test_threeScan;

#include <cxxtest/Root.cpp>
