#include "clases/Matriz.h"
#include "clases/MatrizSimetrica.h"
#include "factorizacion/gauss.cpp"
#include "factorizacion/cholesky.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

//Matriz crearMatriz(std::string file){ //en la primer línea #filas #columnas y después la matriz
//  std::string line;
//  std::ifstream fileData (file.c_str());
//
//  getline(fileData, line);
//  std::istringstream iss(line);
//  int filas, columnas;
//  iss >> filas;
//  iss >> columnas;
//
//  Matriz res(filas, columnas);
//
//  for(int i = 0; i < filas; ++i){
//    getline(fileData, line);
//    std::istringstream iss(line);
//    for(int j = 0; j < columnas; ++j){
//      iss >> res[i][j];
//    }
//  }
//
//  res.mostrar();
//
//}

int evaluarTests(std::string fileTestData, std::string fileTestResult, int method) {
  std::string line;
  std::ifstream fileData (fileTestData.c_str());
  std::ofstream fileWrite (fileTestResult.c_str());
  std::string s;
  std::string res;
  int cantEquipos;
  int cantPartidos;

  getline(fileData, line);
  std::istringstream iss(line);
  iss >> cantEquipos;
  iss >> cantPartidos;
  Matriz C(cantEquipos, cantEquipos);
  vector<int> w(cantEquipos, 0); // Cada posición tiene el numero de partidos ganados por el equipo i
  vector<int> l(cantEquipos, 0); // Cada posición tiene el numero de partidos perdidos por el equipo i
  vector<float> b(cantEquipos, 0); // Vector del sistema Cr = b
  vector<float> r(cantEquipos, 0); // Solución del sistema Cr = b

  while (getline (fileData, line)) {

    std::istringstream iss(line);

    std::string fecha;
    int equipo1;
    int equipo2;
    int golesEquipo1;
    int golesEquipo2;

    iss >> fecha;
    iss >> equipo1;
    iss >> golesEquipo1;
    iss >> equipo2;
    iss >> golesEquipo2;

    equipo1 -= 1;
    equipo2 -= 1;

    if (golesEquipo1 > golesEquipo2) { // Gano el equipo 1
      w[equipo1]++;
      l[equipo2]++;
    } else {
      w[equipo2]++;
      l[equipo1]++;
    }

    C[equipo1][equipo2]--;
    C[equipo2][equipo1]--;

  }


  Matriz L(cantEquipos, cantEquipos);

  if (method == 0) {
    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2 + w[i] + l[i];
      b[i] = 1 + (w[i] - l[i]) / 2; 
    }

    gauss(C);
    //resolver sistema
  }

  if (method == 1) {
    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2 + w[i] + l[i];
      b[i] = 1 + (w[i] - l[i]) / 2; 
    }

    L = cholesky(C);
    //resoler sistema
  }

  if (method == 2) {
    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2 + w[i] + l[i];
      b[i] = w[i] / (w[i] + l[i]); 
    }

    // Aca se llama tanto a cholesky como a gauss?
    
  }

  C.mostrar();

  std::cout << "------------------------------------------" << std::endl;

  L.mostrar();

//  for (int i = 0 ; i < cantEquipos ; ++i) {
//    fileWrite << "equipo: " << i << " ranking: " << std::fixed << r[i] << std::endl; 
//  }

  return 0;
}

std::vector<float> resolverSistema(Matriz& m, vector<float>& b) { //m diagonalizada, 
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


int main(int argc, char** argv) {
  std::string fileTestData(argv[1]);
  std::string fileTestResult(argv[2]);
  int method(atoi(argv[3]));
  // Recibo por parametro tres archivos
  // El primero del cual leo los datos a evaluar
  // El segundo en el cual evaluo si los resultados fueron correctos
  // El tercero el método a realizar (0 CMM-EG, 1 CMM-CL, 2 WP)

  //evaluarTests(fileTestData, fileTestResult, method);

  return 0;
}

