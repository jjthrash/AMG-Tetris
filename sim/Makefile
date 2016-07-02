sim: copied_files main.o board.o bigtetris.o image.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o bigtetris.o image.o

%.o: %.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

copied_files: ../bigtetris/bigtetris.cpp ../bigtetris/platform.h ../bigtetris/image.c ../bigtetris/image.h
	cp ../bigtetris/bigtetris.cpp ../bigtetris/platform.h ../bigtetris/image.c ../bigtetris/image.h .

clean:
	rm -f *.o sim bigtetris.cpp platform.h
