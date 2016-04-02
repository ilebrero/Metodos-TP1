#include "clases/Matriz.h"
#include "clases/MatrizSimetrica.h"
//#include "crearTests/crearTests.cpp" Incluir en caso de querer crear matrices de esta manera
#include "factorizacion/gauss.cpp"
#include "factorizacion/cholesky.cpp"
#include "factorizacion/resolucionSistema.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <sys/time.h>

timeval sstart, eend;
double acum = 0;

void init_time() {
  gettimeofday(&sstart, NULL);
}

double get_time() {
  gettimeofday(&eend, NULL);
  return (1000000*(eend.tv_sec-sstart.tv_sec) + (eend.tv_usec-sstart.tv_usec))/1000000.0;
}

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
  std::vector<float> r;
  std::vector<float> y;

  if (method == 2) {
    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2.0 + w[i] + l[i];
      b[i] = w[i] / (w[i] + l[i]); 
    }

  } else {
    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2.0 + w[i] + l[i];
      b[i] = 1.0 + (w[i] - l[i]) / 2.0; 
    }
  }

  switch(method) {
    case 0: {
     // gauss(C, b);
     // C.mostrar();
     // r = resolverSistemaParaAtras(C, b);

      L = gaussLU(C);

      y = resolverSistemaParaAdelante(L, b);
      r = resolverSistemaParaAtras(C, y); //C=U

      break;
    }
    case 1: {
      init_time();
      L = cholesky(C);
      Matriz LT = L;
      LT.transponer();

      y = resolverSistemaParaAdelante(L, b);
      r = resolverSistemaParaAtras(LT, y);
      acum += get_time();
      std::cout << std::fixed << acum << std::endl;
      break;
    }
    case 2: {
      std::cout << "elegite una papu" << std::endl;
      break;
    }
    /*
      gauss(C, b);
      C.mostrar();
      r = resolverSistemaParaAtras(C, b);
    */
    /*
      L = cholesky(C);
      Matriz LT = L;
      LT.transponer();

      y = resolverSistemaParaAdelante(L, b);
      r = resolverSistemaParaAtras(LT, y);
    */
  }

  for (int i = 0 ; i < cantEquipos ; ++i) {
    fileWrite << "equipo: " << i << " ranking: " << std::fixed << r[i] << std::endl; 
  }

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
