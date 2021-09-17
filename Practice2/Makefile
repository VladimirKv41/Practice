CC=g++
CFLAGS=-c -g
EXECUTABLE=main

all:	$(EXECUTABLE) clean

$(EXECUTABLE): main.o
	$(CC) -g main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
clean:
	del /q *.o
