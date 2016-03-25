CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = matriz gauss descomposicionLU main 

.PHONY: main matriz gauss descomposicionLU

all: $(BINARIES)

main: main.cpp
	$(CC) main.cpp clases/Matriz.cpp $(CFLAGS) main

matriz: clases/Matriz.cpp
	$(CC) clases/Matriz.cpp $(CFLAGS) matriz

gauss: factorizacion/gauss.cpp
	$(CC) clases/Matriz.cpp factorizacion/gauss.cpp $(CFLAGS) gauss

descomposicionLU: factorizacion/descomposicionLU.cpp
	$(CC) factorizacion/descomposicionLU.cpp $(CFLAGS) descomposicionLU

clean:
	rm -f ./*.o main
	rm -f clases/*.o matriz
	rm -f factorizacion/*.o gauss
	rm -f factorizacion/*.o descomposicionLU
