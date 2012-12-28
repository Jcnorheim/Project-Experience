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
#include "parser_tests.h"

static ScannerTestSuite suite_ScannerTestSuite;

static CxxTest::List Tests_ScannerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScannerTestSuite( "parser_tests.h", 10, "ScannerTestSuite", suite_ScannerTestSuite, Tests_ScannerTestSuite );

static class TestDescription_ScannerTestSuite_test_p1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 30, "test_p1" ) {}
 void runTest() { suite_ScannerTestSuite.test_p1(); }
} testDescription_ScannerTestSuite_test_p1;

static class TestDescription_ScannerTestSuite_test_p2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 33, "test_p2" ) {}
 void runTest() { suite_ScannerTestSuite.test_p2(); }
} testDescription_ScannerTestSuite_test_p2;

static class TestDescription_ScannerTestSuite_test_p3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p3() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 36, "test_p3" ) {}
 void runTest() { suite_ScannerTestSuite.test_p3(); }
} testDescription_ScannerTestSuite_test_p3;

static class TestDescription_ScannerTestSuite_test_arithmetic_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_arithmetic_1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 39, "test_arithmetic_1" ) {}
 void runTest() { suite_ScannerTestSuite.test_arithmetic_1(); }
} testDescription_ScannerTestSuite_test_arithmetic_1;

static class TestDescription_ScannerTestSuite_test_arithmetic_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_arithmetic_2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 42, "test_arithmetic_2" ) {}
 void runTest() { suite_ScannerTestSuite.test_arithmetic_2(); }
} testDescription_ScannerTestSuite_test_arithmetic_2;

static class TestDescription_ScannerTestSuite_test_matrix_ref : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_matrix_ref() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 45, "test_matrix_ref" ) {}
 void runTest() { suite_ScannerTestSuite.test_matrix_ref(); }
} testDescription_ScannerTestSuite_test_matrix_ref;

static class TestDescription_ScannerTestSuite_test_parens_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 48, "test_parens_1" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_1(); }
} testDescription_ScannerTestSuite_test_parens_1;

static class TestDescription_ScannerTestSuite_test_parens_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 51, "test_parens_2" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_2(); }
} testDescription_ScannerTestSuite_test_parens_2;

static class TestDescription_ScannerTestSuite_test_parens_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_3() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 54, "test_parens_3" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_3(); }
} testDescription_ScannerTestSuite_test_parens_3;

static class TestDescription_ScannerTestSuite_test_equalTo : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_equalTo() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 57, "test_equalTo" ) {}
 void runTest() { suite_ScannerTestSuite.test_equalTo(); }
} testDescription_ScannerTestSuite_test_equalTo;

static class TestDescription_ScannerTestSuite_test_notEqualTo : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_notEqualTo() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 60, "test_notEqualTo" ) {}
 void runTest() { suite_ScannerTestSuite.test_notEqualTo(); }
} testDescription_ScannerTestSuite_test_notEqualTo;

static class TestDescription_ScannerTestSuite_test_less : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_less() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 63, "test_less" ) {}
 void runTest() { suite_ScannerTestSuite.test_less(); }
} testDescription_ScannerTestSuite_test_less;

static class TestDescription_ScannerTestSuite_test_greater : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_greater() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 66, "test_greater" ) {}
 void runTest() { suite_ScannerTestSuite.test_greater(); }
} testDescription_ScannerTestSuite_test_greater;

static class TestDescription_ScannerTestSuite_test_relational_semantic_errors : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_relational_semantic_errors() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 69, "test_relational_semantic_errors" ) {}
 void runTest() { suite_ScannerTestSuite.test_relational_semantic_errors(); }
} testDescription_ScannerTestSuite_test_relational_semantic_errors;

static class TestDescription_ScannerTestSuite_test_logical : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_logical() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 72, "test_logical" ) {}
 void runTest() { suite_ScannerTestSuite.test_logical(); }
} testDescription_ScannerTestSuite_test_logical;

static class TestDescription_ScannerTestSuite_test_assdecl : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_assdecl() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 75, "test_assdecl" ) {}
 void runTest() { suite_ScannerTestSuite.test_assdecl(); }
} testDescription_ScannerTestSuite_test_assdecl;

static class TestDescription_ScannerTestSuite_test_parse_forest_loss : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parse_forest_loss() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 79, "test_parse_forest_loss" ) {}
 void runTest() { suite_ScannerTestSuite.test_parse_forest_loss(); }
} testDescription_ScannerTestSuite_test_parse_forest_loss;

#include <cxxtest/Root.cpp>
