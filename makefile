CC=g++
CFLAGS=-Wall -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2 -Iinclude
SOURCES=src/*.cpp
EXECUTABLE=dendrite

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm dendrite *.dat
