#include <cxxtest/TestSuite.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "readInput.h"

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:

    Parser p ;
    ParseResult pr ;

    char **makeArgs ( const char *a0, const char *a1) {
        char **aa = (char **) malloc (sizeof(char *) * 2) ;
        aa[0] = (char *) malloc ( sizeof(char) * (strlen(a0) + 1) ) ;
        strcpy (aa[0], a0 ) ;
        aa[1] = (char *) malloc ( sizeof(char) * (strlen(a1) + 1) ) ;
        strcpy (aa[1], a1 ) ;
        return aa ;
    }

    const char *readFile ( const char *fn ) {
        return readInput (2, makeArgs("translator", fn) ) ;
    }

    void test_p1 ( void ) {
        TS_ASSERT ( p.parse( "main () { } " ).ok ) ;
    }
    void test_p2 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = x; } " ).ok ) ;
    }
    void test_p3 ( void ) {
        TS_ASSERT ( p.parse( readFile("../samples/sample_2.dsl")).ok ) ;
    }
    void test_arithmetic_1 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = x + 2 * y ; } " ).ok ) ;
    }
    void test_arithmetic_2 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = 4 / x - 2 + 3 ; } " ).ok ) ;
    }
    void test_matrix_ref ( void ) {
        TS_ASSERT ( p.parse( "main () { x = data [ 4, y + 3 * z ] ; } " ).ok ) ;
    }
    void test_parens_1 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = ( 4 ) ; } " ).ok ) ;
    }
    void test_parens_2 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = ( 4 + y ) * 5 ; } " ).ok ) ;
    }
    void test_parens_3 ( void ) {
        TS_ASSERT ( p.parse( "main () { x = 4 + ( y * 5 ) ; } " ).ok ) ;
    }
    void test_equalTo ( void ) {
        TS_ASSERT ( p.parse( "main () { b = x == y ; } " ).ok ) ;
    }
    void test_notEqualTo ( void ) {
        TS_ASSERT ( p.parse( "main () { b = x != y ; } " ).ok ) ;
    }
    void test_less ( void ) {
        TS_ASSERT ( p.parse( "main () { b1 = x < 4; b2 = y <= 4 ; } " ).ok ) ;
    }
    void test_greater ( void ) {
        TS_ASSERT ( p.parse( "main () { b1 = x > 4; b2 = y >= 4 ; } " ).ok ) ;
    }
    void test_relational_semantic_errors ( void ) {
        TS_ASSERT ( p.parse( "main () { b = x > 4 > y ; } " ).ok ) ;
    }
    void test_logical ( void ) {
        TS_ASSERT ( p.parse( "main () { b1 = x > 4 && y < 1 ; b2 = y || ! b3 ; } " ).ok ) ;
    }
    void test_assdecl ( void ) {
        TS_ASSERT (p.parse( "main () { I = 5; }" ).ok );
    }

    void test_parse_forest_loss ( void ) {
        TS_ASSERT ( p.parse( readFile("../samples/forest_loss_v2.dsl")).ok ) ;
    }

} ;





