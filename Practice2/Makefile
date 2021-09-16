CC=g++
CFLAGS=-c -g
SOURCES=main.cpp
EXECUTABLE=main

all:	$(EXECUTABLE)

$(EXECUTABLE): main.o
	$(CC)  main.o -o $(EXECUTABLE)

main.o: main.cpp
	g++ $(CFLAGS) main.cpp
clean:
	rm -rf *.o $(EXECUTABLE)
