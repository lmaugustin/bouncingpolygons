# Makefile for the Game of Life

GFLAGS=-g -c -std=c++11

polybounce: polybounce.o polygon.o
	g++ polybounce.o polygon.o gfx.o -lX11 -o polybounce

polygon.o: polygon.cpp polygon.h
	g++ ${GFLAGS} polygon.cpp -o polygon.o

polybounce.o: polybounce.cpp
	g++ ${GFLAGS} polybounce.cpp -o polybounce.o

clean:
	rm -f *.o *~ crossword

push:
	-git commit -m "Update" *.h *.cpp Makefile
	git push https://github.com/lmaugustin/crossword-anagram master
