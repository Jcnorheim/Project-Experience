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


    void xxtest_unparse_forest_loss ( void ) {
        string file = "simple_1.dsl" ;   // forest_loss_v2.dsl" ;
        string path = "../samples/" + file ; 

        // Test that the file can be parsed.
        ParseResult pr1 = p.parse ( 
            readInput (2, makeArgs("translator", path.c_str() ) ) 
          ) ;
        TSM_ASSERT ( file + " failed to parse.", pr1.ok ) ;

        // Compute the "unparsing" of this program and then verify
        // that it is non-empty.
        string up1 = pr1.ast->unparse() ;
        TSM_ASSERT ( file + " failed to generate non-empty unparsing.", 
                     up1.length() > 0 ) ;

        // Verify that the un-parsed string can be parsed.
        ParseResult pr2 = p.parse ( up1.c_str() ) ;
        TSM_ASSERT ( file + " failed to parse the first un-parsing.", 
                     pr2.ok ) ;

        // From this result, ensure that its "unparsing" can be parsed.
        string up2 = pr2.ast->unparse() ;
        ParseResult pr3 = p.parse ( up2.c_str() ) ;
        TSM_ASSERT ( file + " failed to pares the second un-parsing.",
                     pr3.ok ) ;

        // Verify that the first and second unparsings and the second
        // and third unparsings are the exact same string.
        string up3 = pr3.ast->unparse() ;
        TSM_ASSERT_EQUALS ( file + " unparse-1 != unparse-2.", up1, up2 ) ;
        TSM_ASSERT_EQUALS ( file + " unparse-2 != unparse-3.", up2, up3 ) ;
    }

    void unparse_tests ( string file ) {
        string path = "../samples/" + file ; 

        // 1. Test that the file can be parsed.
        ParseResult pr1 = p.parse ( 
            readInput (2, makeArgs("translator", path.c_str() ) ) 
          ) ;
        TSM_ASSERT ( file + " failed to parse.", pr1.ok ) ;

        // 2. Verify that the ast field is not null
        TSM_ASSERT ( file + " failed to generate an AST.", pr1.ast != NULL );

        // 3. Verify that the "unparsing" is non-empty.
        string up1 = pr1.ast->unparse() ;
        TSM_ASSERT ( file + " failed to generate non-empty unparsing.", 
                     up1.length() > 0 ) ;

        // 4. Verify that the un-parsed string can be parsed.
        ParseResult pr2 = p.parse ( up1.c_str() ) ;
        TSM_ASSERT ( file + " failed to parse the first un-parsing.", 
                     pr2.ok ) ;

        // 5. Verify that the ast field is not null after first unparsing
        TSM_ASSERT ( file + " first unparsing failed to generate an AST.", 
                     pr2.ast != NULL );

        // 6. Verify that this second unparsing can be parsed.
        string up2 = pr2.ast->unparse() ;
        ParseResult pr3 = p.parse ( up2.c_str() ) ;
        TSM_ASSERT ( file + " failed to pares the second un-parsing.",
                     pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;

        // 7. Verify that the first and second unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-1 != unparse-2.", up1, up2 ) ;
        // 8. Verifty that the second and third unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-2 != unparse-3.", up2, up3 ) ;
    }

    void test_simple_1 ( void ) { unparse_tests ( "simple_1.dsl" ); }
    void test_simple_2 ( void ) { unparse_tests ( "simple_2.dsl" ); }
    void test_simple_3 ( void ) { unparse_tests ( "simple_3.dsl" ); }
    void test_simple_4 ( void ) { unparse_tests ( "simple_4.dsl" ); }
    void test_simple_5 ( void ) { unparse_tests ( "simple_5.dsl" ); }
    void test_forest_loss ( void ) { unparse_tests ( "forest_loss_v2.dsl" ); }
} ;




