#include <cxxtest/TestSuite.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "readInput.h"

class ScannerTestSuite : public CxxTest::TestSuite {
    char **makeArgs ( const char *a0, const char *a1) {
        char **aa = (char **) malloc (sizeof(char *) * 2) ;
        aa[0] = (char *) malloc ( sizeof(char) * (strlen(a0) + 1) ) ;
        strcpy (aa[0], a0 ) ;
        aa[1] = (char *) malloc ( sizeof(char) * (strlen(a1) + 1) ) ;
        strcpy (aa[1], a1 ) ;
        return aa ;
    }

    public:
    void testNoFileNull( void ) {
        char *buffer = readInput(1, makeArgs("translator", "whatever"));
        TS_ASSERT(buffer == NULL);
    }

    void testFileNotFoundNull( void ) {
        char *buffer = readInput(2, makeArgs("translator", "file.notfound"));
        TS_ASSERT(buffer == NULL);
    }
    
    void testFileNotNull( void ) {
        char *buffer = readInput(2, makeArgs("translator", "readInput_tests.h"));
        TS_ASSERT(buffer != NULL);
    }
};
