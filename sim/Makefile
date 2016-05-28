sim: main.o board.o bigtetris.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o bigtetris.o

%.o: %.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

clean:
	rm *.o sim
