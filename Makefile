all: compile clean

compile: parser lexer
	g++ -std=c++14 -o kompilator src/parser/parser.tab.cpp src/parser/lexer.c src/*.cpp src/codeGenerator/*.cpp src/variables/*.cpp src/memory/*.cpp

parser: src/parser/parser.ypp
	bison -b src/parser/parser -d src/parser/parser.ypp
	
lexer: src/parser/lexer.l
	flex -o src/parser/lexer.c src/parser/lexer.l

clean:
	rm -f parser.tab.* lexer.* *.o