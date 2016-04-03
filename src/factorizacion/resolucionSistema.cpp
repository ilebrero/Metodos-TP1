#include "../clases/Matriz.h"
#include "../clases/MatrizSimetrica.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void resolverSistemaParaAdelante(Matriz& m, vector<float>& b, vector<float>& y) { //m diagonalizada, inversible 
  assert (m.dimensionColumnas() == b.size()); //condición necesaria para la multiplicación
  
  int n = m.dimensionFilas();
  int k = m.dimensionColumnas();

  float aux;

  for(int i = 0; i < n; ++i){
    aux = 0;
    for (int j = 0; j < i ; ++j){
      aux = aux + m[i][j] * y[j];
    }
    y[i] = (b[i] - aux) / m[i][i]; //m[i][i] != 0 si m inversible
  }

}

void resolverSistemaParaAtras(Matriz& m, vector<float>& b, vector<float>& y) { //m diagonalizada, inversible
  assert (m.dimensionColumnas() == b.size()); //condición necesaria para la multiplicación
  
  int n = m.dimensionFilas();
  int k = m.dimensionColumnas();

  float aux;

  for(int i = n-1; i >= 0; --i){
    aux = 0;
    for (int j = k-1; j > i; --j){
      aux = aux + m[i][j] * y[j];
    }
    y[i] = (b[i] - aux) / m[i][i]; //siempre va a estar definido ?
  }

}
/* Esto se usa para algo?
std::vector<float> multiplicarVectorIncognita(Matriz& m) {
  vector<float> res (m.dimensionColumnas());

}
*/
