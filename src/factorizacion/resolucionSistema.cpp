#include "../clases/Matriz.h"
#include "../clases/MatrizSimetrica.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<float> resolverSistemaParaAdelante(Matriz& m, vector<float>& b) { //m diagonalizada, inversible 
  assert (m.dimensionColumnas() == b.size()); //condición necesaria para la multiplicación
  
  vector<float> res (b.size());

  int n = m.dimensionFilas();
  int k = m.dimensionColumnas();

  float aux;

  for(int i = 0; i < n; ++i){
    aux = 0;
    for (int j = 0; j < i ; ++j){
      aux = aux + m[i][j] * res[j];
    }
    res[i] = (b[i] - aux) / m[i][i]; //m[i][i] != 0 si m inversible
  }
  return res;
}

std::vector<float> resolverSistemaParaAtras(Matriz& m, vector<float>& b) { //m diagonalizada, inversible
  assert (m.dimensionColumnas() == b.size()); //condición necesaria para la multiplicación
  
  vector<float> res (b.size());

  int n = m.dimensionFilas();
  int k = m.dimensionColumnas();

  float aux;

  for(int i = n-1; i >= 0; --i){
    aux = 0;
    for (int j = k-1; j > i; --j){
      aux = aux + m[i][j] * res[j];
    }
    res[i] = (b[i] - aux) / m[i][i]; //siempre va a estar definido ?
  }
  return res;
}
/* Esto se usa para algo?
std::vector<float> multiplicarVectorIncognita(Matriz& m) {
  vector<float> res (m.dimensionColumnas());

}
*/
