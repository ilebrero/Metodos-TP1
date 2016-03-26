#include "../clases/Matriz.h"
#include "../clases/MatrizSimetrica.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
