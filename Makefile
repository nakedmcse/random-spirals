all: randomspirals

randomspirals: raylib.h randomspirals.c
	gcc -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -O3 -o randomspirals randomspirals.c libraylib.a

raylib:
	git clone https://github.com/raysan5/raylib.git
	make -C raylib/src
	cp raylib/src/libraylib.a libraylib.a
	cp raylib/src/raylib.h raylib.h
	rm -rf raylib

clean:
	rm -f *.o
	rm -f randomspirals