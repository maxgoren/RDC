repl:
	g++ --std=c++17 -g -c ./ast.cpp
	g++ --std=c++17 -g -c ./astbuilder.cpp
	g++ --std=c++17 -g -c ./buffer.cpp
	g++ --std=c++17 -g -c ./lexer.cpp
	g++ --std=c++17 -g -c ./parser.cpp
	g++ --std=c++17 -g -c ./repl.cpp
	g++ --std=c++17 -g -c ./main.cpp
	g++ *.o -o repl