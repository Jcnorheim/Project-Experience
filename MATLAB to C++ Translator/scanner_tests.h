#include <cxxtest/TestSuite.h>
#include <iostream> 
#include "scanner.h"
#include "readInput.h"

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:

    void test_noScan ( void ) {
        token *ts = scan (" " ) ;
        TS_ASSERT (ts->terminal == endOfFile) ;
    }

    void test_oneScan ( void ) {
        token *ts = scan (" 12 " ) ;
        TS_ASSERT_EQUALS (ts->terminal, integerConst);
        TS_ASSERT_EQUALS (ts->next->terminal, endOfFile) ;
    }

    void test_twoScan ( void ) {
        token *ts = scan (" 12 abc " ) ;
        TS_ASSERT_EQUALS (ts->terminal, integerConst) ;
        TS_ASSERT (ts->next != NULL) ;
        ts = ts->next ;
        TS_ASSERT_EQUALS (ts->terminal, varName) ;
        TS_ASSERT_EQUALS (ts->next->terminal, endOfFile) ;
    }

    void test_threeScan ( void ) {
        token *ts = scan (" 12 abc let " ) ;
        TS_ASSERT_EQUALS (ts->terminal, integerConst) ;
        TS_ASSERT (ts->next != NULL) ;
        ts = ts->next ;
        TS_ASSERT_EQUALS (ts->terminal, varName) ;
        TS_ASSERT (ts->next != NULL) ;
        ts = ts->next ;
        TS_ASSERT_EQUALS (ts->terminal, letKwd) ;
        TS_ASSERT_EQUALS (ts->next->terminal, endOfFile) ;
    }

} ;





