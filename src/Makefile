CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = main matriz matrizsimetrica gauss descomposicionLU

.PHONY: main matriz matrizsimetrica gauss descomposicionLU

all: $(BINARIES)

main: main.cpp
	$(CC) main.cpp clases/Matriz.cpp clases/MatrizSimetrica.cpp $(CFLAGS) main

matriz: clases/Matriz.cpp
	$(CC) clases/Matriz.cpp $(CFLAGS) matriz

matrizsimetrica: clases/MatrizSimetrica.cpp
	$(CC) clases/MatrizSimetrica.cpp $(CFLAGS) matrizsimetrica

gauss: factorizacion/gauss.cpp
	$(CC) clases/Matriz.cpp factorizacion/gauss.cpp $(CFLAGS) gauss

descomposicionLU: factorizacion/descomposicionLU.cpp
	$(CC) factorizacion/descomposicionLU.cpp $(CFLAGS) descomposicionLU

clean:
	rm -f ./*.o main
	rm -f clases/*.o matriz
	rm -f clases/*.o matrizsimetrica
	rm -f factorizacion/*.o gauss
	rm -f factorizacion/*.o descomposicionLU
