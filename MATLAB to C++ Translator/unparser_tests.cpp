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
#include "unparser_tests.h"

static UnparserTestSuite suite_UnparserTestSuite;

static CxxTest::List Tests_UnparserTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UnparserTestSuite( "unparser_tests.h", 10, "UnparserTestSuite", suite_UnparserTestSuite, Tests_UnparserTestSuite );

static class TestDescription_UnparserTestSuite_test_p1 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p1() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 30, "test_p1" ) {}
 void runTest() { suite_UnparserTestSuite.test_p1(); }
} testDescription_UnparserTestSuite_test_p1;

static class TestDescription_UnparserTestSuite_test_p2 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p2() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 45, "test_p2" ) {}
 void runTest() { suite_UnparserTestSuite.test_p2(); }
} testDescription_UnparserTestSuite_test_p2;

static class TestDescription_UnparserTestSuite_test_p3 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p3() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 60, "test_p3" ) {}
 void runTest() { suite_UnparserTestSuite.test_p3(); }
} testDescription_UnparserTestSuite_test_p3;

static class TestDescription_UnparserTestSuite_test_p4 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p4() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 75, "test_p4" ) {}
 void runTest() { suite_UnparserTestSuite.test_p4(); }
} testDescription_UnparserTestSuite_test_p4;

static class TestDescription_UnparserTestSuite_test_p5 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p5() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 90, "test_p5" ) {}
 void runTest() { suite_UnparserTestSuite.test_p5(); }
} testDescription_UnparserTestSuite_test_p5;

static class TestDescription_UnparserTestSuite_test_p6 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p6() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 105, "test_p6" ) {}
 void runTest() { suite_UnparserTestSuite.test_p6(); }
} testDescription_UnparserTestSuite_test_p6;

static class TestDescription_UnparserTestSuite_test_p7 : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_p7() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 120, "test_p7" ) {}
 void runTest() { suite_UnparserTestSuite.test_p7(); }
} testDescription_UnparserTestSuite_test_p7;

static class TestDescription_UnparserTestSuite_test_final : public CxxTest::RealTestDescription {
public:
 TestDescription_UnparserTestSuite_test_final() : CxxTest::RealTestDescription( Tests_UnparserTestSuite, suiteDescription_UnparserTestSuite, 135, "test_final" ) {}
 void runTest() { suite_UnparserTestSuite.test_final(); }
} testDescription_UnparserTestSuite_test_final;

#include <cxxtest/Root.cpp>
