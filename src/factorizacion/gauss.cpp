#include "../clases/Matriz.h"
//#include <assert.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define EPSILON 1.19e-7f

bool igualdadConTolerancia(float a, float b) {
  if (a - b < EPSILON) {
    return true;
  } else {
    return false;
  }
}

Matriz crearMatriz(std::string file){ //en la primer línea #filas #columnas y después la matriz
  std::string line;
  std::ifstream fileData (file.c_str());

  getline(fileData, line);
  std::istringstream iss(line);
  int filas, columnas;
  iss >> filas;
  iss >> columnas;

  Matriz res(filas, columnas);

  for(int i = 0; i < filas; ++i){
    getline(fileData, line);
    std::istringstream iss(line);
    for(int j = 0; j < columnas; ++j){
      iss >> res[i][j];
    }
  }
  return res;
}

void combLineal(Matriz &m, int j, float k, int i){ //E_j = E_j - k*E_i
  assert (i < m.dimensionFilas());
  assert (j < m.dimensionFilas());
  
  for(int t = 0; t < m.dimensionColumnas(); ++t) m[j][t] = m[j][t] - k*m[i][t]; 
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

void gauss(Matriz& m) {
  int n = m.dimensionFilas();
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
      if( !igualdadConTolerancia(m[i][i], 0) ){
        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j - k * fila i
      } else {
        permutar(m, i, i+1);
      }
    }
  }
}


Matriz gaussLU(Matriz& m) { //devuelve matriz L
  int n = m.dimensionFilas();
  Matriz res = Matriz(n, m.dimensionColumnas()); // res = L
  
  for(int k = 0; k < n; ++k){ //completo con 1 en la diagonal de L
    res[k][k] = 1;
  }
  
  for(int i = 0; i < n-1; ++i){
    for(int j = i+1; j < n; ++j){
      if( !igualdadConTolerancia(m[i][i], 0) ){
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

void test_gauss(Matriz& m) { //no es exactamente 0
  gauss(m);
  std::cout << "La matriz diagonalizada es: " << std::endl; 
  m.mostrar();
}

void test_gaussLU(Matriz& m) { //no es exactamente 0
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
  m.mostrar();
  //test_gauss(m);
  test_gaussLU(m);
   
  return 0;
}
*/
