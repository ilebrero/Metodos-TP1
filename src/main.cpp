#include "clases/Matriz.h"
#include "factorizacion/gauss.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int evaluarTests(std::string fileTestData, std::string fileTestResult, int fileTestWrite) {
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

  for (int i = 0 ; i < cantEquipos ; ++i) {
    C[i][i] = 2 + w[i] + l[i];
    b[i] = 1 + (w[i] - l[i]) / 2; 
  }

  C.mostrar();
  std::cout << "lalal" << std::endl;

  gauss(C);

  C.mostrar();
  // Llamado a función con C matriz, b vector y hay que despejar r;
  // Este llamado va a depender del método 

//  for (int i = 0 ; i < cantEquipos ; ++i) {
//    fileWrite << "equipo: " << i << " ranking: " << std::fixed << r[i] << std::endl; 
//  }

  return 0;
}

int main(int argc, char** argv) {
  std::string fileTestData(argv[1]);
  std::string fileTestResult(argv[2]);
  int method(atoi(argv[3]));
  // Recibo por parametro tres archivos
  // El primero del cual leo los datos a evaluar
  // El segundo en el cual evaluo si los resultados fueron correctos
  // El tercero el método a realizar (0 CMM-EG, 1 CMM-CL, 2 WP)

  evaluarTests(fileTestData, fileTestResult, method);
  
  return 0;
}

