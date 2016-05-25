sim: main.o board.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o

main.o: main.cpp
	g++ $(shell fltk-config --cxxflags) -c -o main.o main.cpp

board.o: board.cpp
	g++ $(shell fltk-config --cxxflags) -c -o board.o board.cpp
