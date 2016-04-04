#include "../clases/Matriz.h"
#include "../crearTests/crearTests.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define EPSILON 1.19e-4f

bool igualdadConTolerancia(float a, float b) {
  if (a - b < EPSILON) {
    return true;
  } else {
    return false;
  }
}

//combinación lineal de filas de una matriz
void combLineal(Matriz &m, int j, float k, int i){ //E_j = E_j - k*E_i, O(m.dimensionColumnas())
  assert (i < m.dimensionFilas());
  assert (j < m.dimensionFilas());
  
  for(int t = 0; t < m.dimensionColumnas(); ++t) m[j][t] = m[j][t] - k*m[i][t]; 
}

//combinación lineal de elementos de un vector
void combLinealV(vector<float> &b, int j, float k, int i){ //V_j = V_j - k*V_i
  assert (i < b.size());
  assert (j < b.size());
  
  b[j] = b[j] - k*b[i]; 
}

void permutar(Matriz &m, int i, int j){ //permuta fila i con j
  assert (i < m.dimensionFilas());
  assert (j < m.dimensionFilas());

  float aux;

  for(int k = 0; k < m.dimensionColumnas(); ++k){
    aux = m[j][k];
    m[j][k] = m[i][k];
    m[i][k] = aux;
  }
}

//gaus sin calcular matriz LU
void gauss(Matriz& m, vector<float>& b) {
  assert (m.dimensionColumnas() == b.size());

  int n = m.dimensionFilas();
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
 
      float k = m[j][i]/m[i][i];
      combLineal(m, j, k, i); //fila j - k * fila i
      combLinealV(b, j, k, i);
    
    }
  }
}

//gauss con cálculo de matriz LU
void gaussLU(Matriz& m, Matriz& L) { //devuelve matriz L
  int n = m.dimensionFilas();

  for(int i = 0; i < n; ++i){
    for(int j = i; j < n; ++j){

      if (j == i) {

        L[j][j] = 1; 

      } else {

        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j - k * fila i
        L[j][i] = k; //completo matriz L
      }

    }
  }
}

void test_gauss(Matriz& m, vector<float>& b) { 
  gauss(m, b);
  std::cout << "La matriz diagonalizada es: " << std::endl; 
  m.mostrar();
}

void test_gaussLU(Matriz& m) { 
  Matriz lu(m.dimensionFilas(), m.dimensionColumnas());
  gaussLU(m, lu);
  std::cout << "La matriz diagonalizada es: " << std::endl; 
  m.mostrar();
  std::cout << "La matriz LU es: " << std::endl; 
  lu.mostrar();
}
/*
int main(int arc, char** argv) {  
  
  std::string fileTestData(argv[1]);
  std::cout << "La matriz original es: " << std::endl; 
  Matriz m = crearMatriz(fileTestData);
  vector<float> v(3);
  m.mostrar();
  //test_gauss(m,v);
  test_gaussLU(m);
   
  return 0;
}
*/
