sim: main.o board.o bigtetris.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o bigtetris.o

main.o: main.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o main.o main.cpp

board.o: board.cpp
	g++ $(shell fltk-config --cxxflags) -c -o board.o board.cpp

bigtetris.o: bigtetris.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o bigtetris.o bigtetris.cpp

clean:
	rm *.o sim
