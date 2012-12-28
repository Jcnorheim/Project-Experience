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
#include "i3_assessment_tests.h"

static ScannerTestSuite suite_ScannerTestSuite;

static CxxTest::List Tests_ScannerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScannerTestSuite( "i3_assessment_tests.h", 12, "ScannerTestSuite", suite_ScannerTestSuite, Tests_ScannerTestSuite );

static class TestDescription_ScannerTestSuite_test_simple_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_simple_1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 112, "test_simple_1" ) {}
 void runTest() { suite_ScannerTestSuite.test_simple_1(); }
} testDescription_ScannerTestSuite_test_simple_1;

static class TestDescription_ScannerTestSuite_test_simple_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_simple_2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 113, "test_simple_2" ) {}
 void runTest() { suite_ScannerTestSuite.test_simple_2(); }
} testDescription_ScannerTestSuite_test_simple_2;

static class TestDescription_ScannerTestSuite_test_simple_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_simple_3() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 114, "test_simple_3" ) {}
 void runTest() { suite_ScannerTestSuite.test_simple_3(); }
} testDescription_ScannerTestSuite_test_simple_3;

static class TestDescription_ScannerTestSuite_test_simple_4 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_simple_4() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 115, "test_simple_4" ) {}
 void runTest() { suite_ScannerTestSuite.test_simple_4(); }
} testDescription_ScannerTestSuite_test_simple_4;

static class TestDescription_ScannerTestSuite_test_simple_5 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_simple_5() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 116, "test_simple_5" ) {}
 void runTest() { suite_ScannerTestSuite.test_simple_5(); }
} testDescription_ScannerTestSuite_test_simple_5;

static class TestDescription_ScannerTestSuite_test_forest_loss : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_forest_loss() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 117, "test_forest_loss" ) {}
 void runTest() { suite_ScannerTestSuite.test_forest_loss(); }
} testDescription_ScannerTestSuite_test_forest_loss;

#include <cxxtest/Root.cpp>
