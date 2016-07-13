sim: copied_files main.o board.o bigtetris.o image.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o bigtetris.o image.o

%.o: %.cpp
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

copied_files:
	cp ../bigtetris/*.cpp ../bigtetris/*.h ../bigtetris/*.c .

clean:
	rm -f *.o sim bigtetris.cpp platform.h
