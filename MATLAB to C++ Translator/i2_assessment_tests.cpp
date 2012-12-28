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
#include "i2_assessment_tests.h"

static ScannerTestSuite suite_ScannerTestSuite;

static CxxTest::List Tests_ScannerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScannerTestSuite( "i2_assessment_tests.h", 12, "ScannerTestSuite", suite_ScannerTestSuite, Tests_ScannerTestSuite );

static class TestDescription_ScannerTestSuite_test_p1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 37, "test_p1" ) {}
 void runTest() { suite_ScannerTestSuite.test_p1(); }
} testDescription_ScannerTestSuite_test_p1;

static class TestDescription_ScannerTestSuite_test_p2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 40, "test_p2" ) {}
 void runTest() { suite_ScannerTestSuite.test_p2(); }
} testDescription_ScannerTestSuite_test_p2;

static class TestDescription_ScannerTestSuite_test_p3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_p3() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 43, "test_p3" ) {}
 void runTest() { suite_ScannerTestSuite.test_p3(); }
} testDescription_ScannerTestSuite_test_p3;

static class TestDescription_ScannerTestSuite_test_arithmetic_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_arithmetic_1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 46, "test_arithmetic_1" ) {}
 void runTest() { suite_ScannerTestSuite.test_arithmetic_1(); }
} testDescription_ScannerTestSuite_test_arithmetic_1;

static class TestDescription_ScannerTestSuite_test_arithmetic_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_arithmetic_2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 49, "test_arithmetic_2" ) {}
 void runTest() { suite_ScannerTestSuite.test_arithmetic_2(); }
} testDescription_ScannerTestSuite_test_arithmetic_2;

static class TestDescription_ScannerTestSuite_test_matrix_ref : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_matrix_ref() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 52, "test_matrix_ref" ) {}
 void runTest() { suite_ScannerTestSuite.test_matrix_ref(); }
} testDescription_ScannerTestSuite_test_matrix_ref;

static class TestDescription_ScannerTestSuite_test_parens_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_1() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 55, "test_parens_1" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_1(); }
} testDescription_ScannerTestSuite_test_parens_1;

static class TestDescription_ScannerTestSuite_test_parens_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_2() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 58, "test_parens_2" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_2(); }
} testDescription_ScannerTestSuite_test_parens_2;

static class TestDescription_ScannerTestSuite_test_parens_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parens_3() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 61, "test_parens_3" ) {}
 void runTest() { suite_ScannerTestSuite.test_parens_3(); }
} testDescription_ScannerTestSuite_test_parens_3;

static class TestDescription_ScannerTestSuite_test_equalTo : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_equalTo() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 64, "test_equalTo" ) {}
 void runTest() { suite_ScannerTestSuite.test_equalTo(); }
} testDescription_ScannerTestSuite_test_equalTo;

static class TestDescription_ScannerTestSuite_test_notEqualTo : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_notEqualTo() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 67, "test_notEqualTo" ) {}
 void runTest() { suite_ScannerTestSuite.test_notEqualTo(); }
} testDescription_ScannerTestSuite_test_notEqualTo;

static class TestDescription_ScannerTestSuite_test_less : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_less() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 70, "test_less" ) {}
 void runTest() { suite_ScannerTestSuite.test_less(); }
} testDescription_ScannerTestSuite_test_less;

static class TestDescription_ScannerTestSuite_test_greater : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_greater() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 73, "test_greater" ) {}
 void runTest() { suite_ScannerTestSuite.test_greater(); }
} testDescription_ScannerTestSuite_test_greater;

static class TestDescription_ScannerTestSuite_test_relational_semantic_errors : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_relational_semantic_errors() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 76, "test_relational_semantic_errors" ) {}
 void runTest() { suite_ScannerTestSuite.test_relational_semantic_errors(); }
} testDescription_ScannerTestSuite_test_relational_semantic_errors;

static class TestDescription_ScannerTestSuite_test_logical : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_logical() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 79, "test_logical" ) {}
 void runTest() { suite_ScannerTestSuite.test_logical(); }
} testDescription_ScannerTestSuite_test_logical;

static class TestDescription_ScannerTestSuite_test_int_decl_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_int_decl_const() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 83, "test_int_decl_const" ) {}
 void runTest() { suite_ScannerTestSuite.test_int_decl_const(); }
} testDescription_ScannerTestSuite_test_int_decl_const;

static class TestDescription_ScannerTestSuite_test_float_decl_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_float_decl_const() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 87, "test_float_decl_const" ) {}
 void runTest() { suite_ScannerTestSuite.test_float_decl_const(); }
} testDescription_ScannerTestSuite_test_float_decl_const;

static class TestDescription_ScannerTestSuite_test_boolean_decl_true_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_boolean_decl_true_const() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 91, "test_boolean_decl_true_const" ) {}
 void runTest() { suite_ScannerTestSuite.test_boolean_decl_true_const(); }
} testDescription_ScannerTestSuite_test_boolean_decl_true_const;

static class TestDescription_ScannerTestSuite_test_boolean_decl_falsee_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_boolean_decl_falsee_const() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 95, "test_boolean_decl_falsee_const" ) {}
 void runTest() { suite_ScannerTestSuite.test_boolean_decl_falsee_const(); }
} testDescription_ScannerTestSuite_test_boolean_decl_falsee_const;

static class TestDescription_ScannerTestSuite_test_matrix_decl_read : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_matrix_decl_read() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 99, "test_matrix_decl_read" ) {}
 void runTest() { suite_ScannerTestSuite.test_matrix_decl_read(); }
} testDescription_ScannerTestSuite_test_matrix_decl_read;

static class TestDescription_ScannerTestSuite_test_matrix_decl_comprehension : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_matrix_decl_comprehension() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 103, "test_matrix_decl_comprehension" ) {}
 void runTest() { suite_ScannerTestSuite.test_matrix_decl_comprehension(); }
} testDescription_ScannerTestSuite_test_matrix_decl_comprehension;

static class TestDescription_ScannerTestSuite_test_if_then_else : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_if_then_else() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 107, "test_if_then_else" ) {}
 void runTest() { suite_ScannerTestSuite.test_if_then_else(); }
} testDescription_ScannerTestSuite_test_if_then_else;

static class TestDescription_ScannerTestSuite_test_if_then : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_if_then() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 111, "test_if_then" ) {}
 void runTest() { suite_ScannerTestSuite.test_if_then(); }
} testDescription_ScannerTestSuite_test_if_then;

static class TestDescription_ScannerTestSuite_test_print : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_print() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 115, "test_print" ) {}
 void runTest() { suite_ScannerTestSuite.test_print(); }
} testDescription_ScannerTestSuite_test_print;

static class TestDescription_ScannerTestSuite_test_for_simple : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_for_simple() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 119, "test_for_simple" ) {}
 void runTest() { suite_ScannerTestSuite.test_for_simple(); }
} testDescription_ScannerTestSuite_test_for_simple;

static class TestDescription_ScannerTestSuite_test_for : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_for() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 122, "test_for" ) {}
 void runTest() { suite_ScannerTestSuite.test_for(); }
} testDescription_ScannerTestSuite_test_for;

static class TestDescription_ScannerTestSuite_test_parse_forest_loss : public CxxTest::RealTestDescription {
public:
 TestDescription_ScannerTestSuite_test_parse_forest_loss() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 126, "test_parse_forest_loss" ) {}
 void runTest() { suite_ScannerTestSuite.test_parse_forest_loss(); }
} testDescription_ScannerTestSuite_test_parse_forest_loss;

#include <cxxtest/Root.cpp>
