CC=g++
CFLAGS=-std=c++17 -Wall -O2 -Iinclude -fopenmp -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=src/*.cpp
EXECUTABLE=dendrite

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -rf dendrite out
