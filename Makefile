all: prog

prog: o/main.o o/source.o
	gcc o/main.o o/source.o -o prog -lSDL2 -lSDL2_image -lSDL2_ttf -lm -g

o/main.o: main.c header.h
	mkdir -p o
	gcc -c main.c -g -o o/main.o `sdl2-config --cflags`

o/source.o: source.c header.h
	mkdir -p o
	gcc -c source.c -g -o o/source.o `sdl2-config --cflags`

clean:
	rm -f prog
	rm -rf o
