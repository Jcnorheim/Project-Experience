CXX_DIR = ../../lib/cxxtest
CXXTEST = $(CXX_DIR)/cxxtestgen.pl
all: i2_assessment_tests i3_assessment_tests i4_assessment_tests
	./i2_assessment_tests && ./i3_assessment_tests && ./i4_assessment_tests
translator:     readInput.o scanner.o translator.cpp parser.o Conversion.cpp
	g++ -O0 -g translator.cpp Conversion.cpp readInput.o scanner.o parser.o -o translator

scanner.o:      scanner.cpp scanner.h readInput.h
	g++ -O0 -c -g scanner.cpp

parser.o:       parser.cpp parser.h scanner.h
	g++ -O0 -c -g parser.cpp

readInput.o:    readInput.cpp readInput.h
	g++ -O0 -c -g readInput.cpp

run-tests: scanner_tests parser_tests unparser_tests
	./scanner_tests && ./parser_tests && ./unparser_tests

i4_assessment_tests: i4_assessment_tests.h scanner.o parser.o readInput.o i4_assessment_tests.cpp
	g++ -I$(CXX_DIR) -I. -o i4_assessment_tests i4_assessment_tests.cpp Matrix.cpp scanner.o parser.o readInput.o Conversion.cpp

i4_assessment_tests.cpp: parser.o scanner.o i4_assessment_tests.h parser.h
	$(CXXTEST) --error-printer -o i4_assessment_tests.cpp i4_assessment_tests.h

i3_assessment_tests: i3_assessment_tests.h scanner.o parser.o readInput.o i3_assessment_tests.cpp
	g++ -I$(CXX_DIR) -I. -o i3_assessment_tests i3_assessment_tests.cpp Matrix.cpp scanner.o parser.o readInput.o Conversion.cpp

i3_assessment_tests.cpp: parser.o scanner.o i3_assessment_tests.h parser.h
	$(CXXTEST) --error-printer -o i3_assessment_tests.cpp i3_assessment_tests.h

i2_assessment_tests: i2_assessment_tests.h scanner.o parser.o readInput.o i2_assessment_tests.cpp
	g++ -I$(CXX_DIR) -I. -o i2_assessment_tests i2_assessment_tests.cpp Matrix.cpp scanner.o parser.o readInput.o Conversion.cpp

i2_assessment_tests.cpp: parser.o scanner.o i2_assessment_tests.h parser.h
	$(CXXTEST) --error-printer -o i2_assessment_tests.cpp i2_assessment_tests.h

unparser_tests: unparser_tests.cpp parser.o scanner.o readInput.o Conversion.cpp
	g++ -I$(CXX_DIR) -I. -o unparser_tests -g unparser_tests.cpp readInput.o scanner.o parser.o Conversion.cpp

unparser_tests.cpp: parser.o unparser_tests.h scanner.h
	$(CXXTEST) --error-printer -o unparser_tests.cpp unparser_tests.h

readInput_tests: readInput_tests.o readInput.o
	g++ readInput_tests.o readInput.o -o readInput_tests

readInput_tests.o:	readInput_tests.cpp
	g++ -c -I$(CXX_DIR) -I. -g readInput_tests.cpp

readInput_tests.cpp:	readInput_tests.h
	$(CXXTEST) --error-printer -o readInput_tests.cpp readInput_tests.h

parser_tests:   parser_tests.cpp scanner.o readInput.o Conversion.cpp
	g++ -I$(CXX_DIR) -I. -o parser_tests parser.cpp scanner.o readInput.o parser_tests.cpp Conversion.cpp

parser_tests.cpp:   parser.o parser_tests.h scanner.h
	$(CXXTEST) --error-printer -o parser_tests.cpp parser_tests.h

scanner_tests:  scanner_tests.cpp readInput.o
	g++ -I$(CXX_DIR) -I. -o scanner_tests -g scanner.cpp readInput.o scanner_tests.cpp

scanner_tests.cpp:  scanner.o scanner_tests.h readInput.h
	$(CXXTEST) --error-printer -o scanner_tests.cpp scanner_tests.h

clean:
	rm -f translator *.o readInput_tests.cpp readInput_tests sample_tests sample_tests.cpp parser_tests parser_tests.cpp scanner_tests scanner_tests.cpp unparser_tests unparser_tests.cpp i4_assessment_tests.cpp i4_assessment_tests i3_assessment_tests.cpp i3_assessment_tests i2_assessment_tests.cpp i2_assessment_tests



