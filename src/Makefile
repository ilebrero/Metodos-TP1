CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = main matriz gauss descomposicionLU

.PHONY: main matriz gauss descomposicionLU

all: $(BINARIES)

main: main.cpp
	$(CC) clases/Matriz.cpp main.cpp $(CFLAGS) main

matriz: clases/Matriz.cpp
	$(CC) clases/Matriz.cpp $(CFLAGS) matriz

gauss: factorizacion/gauss.cpp
	$(CC) factorizacion/gauss.cpp $(CFLAGS) gauss

descomposicionLU: factorizacion/descomposicionLU.cpp
	$(CC) factorizacion/descomposicionLU.cpp $(CFLAGS) descomposicionLU

clean:
	rm -f ./*.o main
	rm -f clases/*.o matriz
	rm -f factorizacion/*.o gauss
	rm -f factorizacion/*.o descomposicionLU
