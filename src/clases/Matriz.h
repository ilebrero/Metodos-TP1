#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <vector>
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "MatrizSimetrica.h"

using namespace std;

class Matriz {

  public:

    Matriz(const int filas, const int columnas);

    Matriz& operator * (const int i);
    Matriz& operator * (const Matriz& m);
    Matriz& operator * (const MatrizSimetrica& m);

    Matriz& operator + (const Matriz& m);

    Matriz& operator - (const Matriz& m);

    vector<float>& operator [] (const int fila);

    void randomizar(const int semilla);
    void mostrar();

    int dimensionFilas() const;
    int dimensionColumnas() const; 

  private:

	/*******************************
	 *          Variables          *
	 *******************************/ 

    int filas, columnas;
    vector< vector<float> > matriz;

	/*******************************
	 *          Funciones          *
	 *******************************/ 

    void clean();
};

#endif
