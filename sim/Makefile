sim: copied_files main.o board.o bigtetris.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o bigtetris.o

%.o: %.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

copied_files: ../bigtetris/bigtetris.cpp ../bigtetris/platform.h
	cp ../bigtetris/bigtetris.cpp ../bigtetris/platform.h .

clean:
	rm *.o sim bigtetris.cpp platform.h
