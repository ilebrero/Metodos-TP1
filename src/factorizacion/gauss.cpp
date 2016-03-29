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
void combLineal(Matriz &m, int j, float k, int i){ //E_j = E_j - k*E_i
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
 
      if( !igualdadConTolerancia(m[i][i], 0) ){
        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j - k * fila i
        combLinealV(b, j, k, i);
      } else {
        permutar(m, i, i+1);
      }
    
    }
  }
}

//gauss con cálculo de matriz LU
Matriz gaussLU(Matriz& m) { //devuelve matriz L

  int n = m.dimensionFilas();
  Matriz res = Matriz(n, m.dimensionColumnas()); // res = L
  
  for(int k = 0; k < n; ++k){ //completo con 1 en la diagonal de L
    res[k][k] = 1;
  }
  

  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){

      if( m[i][i] != 0){ //cambiar por tolerancia!!!!
        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j - k * fila i
        res[j][i] = k; //completo matriz L
      } else {
        permutar(m, i, i+1); //creo que no entra en este caso. VER
      }
    
    }
  }
  return res;
}

void test_gauss(Matriz& m, vector<float>& b) { 
  gauss(m, b);
  std::cout << "La matriz diagonalizada es: " << std::endl; 
  m.mostrar();
}

void test_gaussLU(Matriz& m) { 
  Matriz lu = gaussLU(m);
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
