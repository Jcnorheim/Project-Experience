#include <cxxtest/TestSuite.h>
#include <iostream> 
#include "parser.h"
#include "readInput.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>

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

    void writeFile ( const string text, const string filename ) {
        ofstream out(filename.c_str()); 
        out << (string) text << endl ;
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

    void test_int_decl_const ( void ) {
        TS_ASSERT ( p.parse( "main () { Integer n ; n = 4 ; } " ).ok ) ;
    }

    void test_float_decl_const ( void ) {
        TS_ASSERT ( p.parse( "main () { Float x ; x = 3.1415 ; } " ).ok ) ;
    }

    void test_boolean_decl_true_const ( void ) {
        TS_ASSERT ( p.parse( "main () { Boolean b ; b = true ; } " ).ok ) ;
    }

    void test_boolean_decl_falsee_const ( void ) {
        TS_ASSERT ( p.parse( "main () { Boolean b ; b = false ; } " ).ok ) ;
    }

    void test_matrix_decl_read ( void ) {
        TS_ASSERT ( p.parse( "main () { Matrix data = readMatrix ( \"myData.dat\" ) ; } " ).ok ) ;
    }

    void test_matrix_decl_comprehension ( void ) {
        TS_ASSERT ( p.parse ( "main () { Matrix m[10, 20] i, j = i * j ; } ").ok ) ; 
    }

    void test_if_then_else ( void ) {
        TS_ASSERT ( p.parse ( "main () { if ( x < 4 ) x = 4; else x = 5 ; } ").ok ) ; 
    }

    void test_if_then ( void ) {
        TS_ASSERT ( p.parse ( "main () { if ( x < 4 ) x = 4; x = 5 ; } ").ok ) ; 
    }

    void test_print ( void ) {
        TS_ASSERT ( p.parse ( "main () { print ( x + 4 * y ) ; } ").ok ) ; 
    }

    void test_for_simple ( void ) {
        TS_ASSERT ( p.parse ( "main () { for(i = 0 to 20) diff = diff + m[i,0] ; } ").ok ) ; 
    }
    void test_for ( void ) {
        TS_ASSERT ( p.parse ( "main () { for(i = 0 to 20) { diff = diff + m[i,0] ; sum = sum + m[i,0] ; } } ").ok ) ; 
    }

    void test_parse_forest_loss ( void ) {
        TS_ASSERT ( p.parse( readFile("../samples/forest_loss_v2.dsl")).ok ) ;
    }

} ;




