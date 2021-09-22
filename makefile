
CC = g++
CFLAGS = -c

OPTFLAGS = -O3 -std=c++11 -Wall

BIN = cb

${BIN}	: main.o cb.o 
			$(CC) $(OPTFLAGS) cb.o main.o -o cb
main.o 	   	: src/main.cpp 
			$(CC)  $(OPTFLAGS) $(CFLAGS) src/main.cpp
cb.o	: src/cb.cpp src/cb.h
			$(CC) $(OPTFLAGS) $(CFLAGS) src/cb.cpp
clean:
		rm -rf *.o  ${BIN}

