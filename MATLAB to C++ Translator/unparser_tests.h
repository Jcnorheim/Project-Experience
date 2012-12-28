#include <cxxtest/TestSuite.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "readInput.h"

using namespace std ;

class UnparserTestSuite : public CxxTest::TestSuite
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
        ParseResult pr1 = p.parse( "main() { Integer x;}" );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p2 ( void ) {
        ParseResult pr1 = p.parse( "derp () { Integer x; Float y; y = 3.8 + 2; String s; s = \"yea\"; } " );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p3 ( void ) {
        ParseResult pr1 = p.parse( "lol () { Integer x; x = 5; if (x < 5) y = 4; else y = 5; } " );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p4 ( void ) {
        ParseResult pr1 = p.parse( "main () { Integer y; x = 3; { y = 4; } } " );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p5 ( void ) {
        ParseResult pr1 = p.parse( "main () { if (x < 5) { y = 4; z = 3; } else { y = 3; } }" );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p6 ( void ) {
        ParseResult pr1 = p.parse( "main () { if (x < 5) { print ( \" x < 5 dude \" ); } else x = 5; }" );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_p7 ( void ) {
        ParseResult pr1 = p.parse( "main () { for ( i = a to 5 ) { b = b + 1; print ( \" x < 5 dude \" ); } }" );
        TS_ASSERT ( pr1.ok ) ;
        string up1 = pr1.ast->unparse();
        ParseResult pr2 = p.parse ( up1.c_str() );
        TS_ASSERT ( pr2.ok ) ;
        string up2 = pr2.ast->unparse();
        ParseResult pr3 = p.parse ( up2.c_str() );
        TS_ASSERT ( pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }

    void test_final ( void ) {
        string fn = "../samples/forest_loss_v2.dsl" ;

        // Test that the file can be parsed.
        ParseResult pr1 = p.parse ( 
            readInput (2, makeArgs("translator", fn.c_str() ) ) 
          ) ;
        TS_ASSERT ( pr1.ok ) ;
        // note that makeArgs definition is part of lab 5.

        // Compute the "unparsing" of this program and then verify
        // that that string can be parsed.
        string up1 = pr1.ast->unparse() ;
        ParseResult pr2 = p.parse ( up1.c_str() ) ;
        TS_ASSERT ( pr2.ok ) ;

        // From this result, ensure that its "unparsing" can be parsed.
        string up2 = pr2.ast->unparse() ;
        ParseResult pr3 = p.parse ( up2.c_str() ) ;
        TS_ASSERT ( pr3.ok ) ;

        // Verify that the first and second unparsings and the second
        // and third unparsings are the exact same string.
        string up3 = pr3.ast->unparse() ;
        TS_ASSERT_EQUALS ( up1, up2 ) ;
        TS_ASSERT_EQUALS ( up2, up3 ) ;
    }
} ;
