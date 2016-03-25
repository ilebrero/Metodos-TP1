#ifndef MATRIZSIMETRICA_H_
#define MATRIZSIMETRICA_H_

#include <vector>
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Matriz.h"

using namespace std;

class MatrizSimetrica {

  public:

    MatrizSimetrica(const int filas, const int columnas);

    MatrizSimetrica& operator * (const int i);
    Matriz& operator * (const MatrizSimetrica& m);
    Matriz& operator * (const Matriz& m);

    //Matriz& operator + (const Matriz& m);
    //Matriz& operator - (const Matriz& m);

    //vector<float>& operator [] (const int fila); no va mas :(

    int   get(const float, const float);
    void  set(const float, const float, const float);

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
