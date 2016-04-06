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

int maximo(vector<float>& a) {
  int max = 0;
  int n = a.size();

  for (int i = 1; i < n; ++i) {
    if (a[i] > a[max])
      max = i;
  }
  return max;
}

int evaluarTests(std::string fileTestData, std::string fileTestResult, int equipo) {
  std::string line;
  std::ifstream fileData (fileTestData.c_str());
  std::ofstream fileWrite (fileTestResult.c_str());
  std::string s;
  std::string res;
  int cantEquipos;
  int cantPartidos;
  int z = 0;


  while (getline (fileData, line)) {

    std::istringstream iss(line);
    iss >> cantEquipos;
    iss >> cantPartidos;
    Matriz C(cantEquipos, cantEquipos);
    vector<int> w(cantEquipos, 0); // Cada posición tiene el numero de partidos ganados por el equipo i
    vector<int> l(cantEquipos, 0); // Cada posición tiene el numero de partidos perdidos por el equipo i
    vector<float> b(cantEquipos, 0); // Vector del sistema Cr = b

    for (int k = 0; k < cantPartidos; ++k) {
    
      getline (fileData, line);

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
      C[i][i] = 2.0 + w[i] + l[i];
      b[i] = 1.0 + (w[i] - l[i]) / 2.0; 
    }

    std::vector<float> r(cantEquipos, 0);
    std::vector<float> y(cantEquipos, 0);

    Matriz L(cantEquipos, cantEquipos);

    equipo -= 1;
    cholesky(C, L);
    Matriz LT = L;
    LT.transponer();

    resolverSistemaParaAdelante(L, b, y);
    resolverSistemaParaAtras(LT, y, r);

    int cantidadDePartidos = 0;
    int ganador = maximo(r);
    while (ganador != equipo) {
      std::cout << ganador << std::endl;
      cantidadDePartidos++;

      C[ganador][equipo]--;
      C[equipo][ganador]--; // Los hago jugar una vez más
      w[equipo]++; // El equipo que quiero llevar arriba gano
      l[ganador]--; // El mejor perdio
      C[equipo][equipo]++;
      C[ganador][ganador]++; // Ambos jugaron un partido más

      b[equipo] = 1.0 + (w[equipo] - l[equipo]) / 2.0;
      b[ganador] = 1.0 + (w[ganador] - l[ganador]) / 2.0; //Actualizo vector resultado

      // Resuelvo el sistema de nuevo
      cholesky(C, L);
      Matriz LT = L;
      LT.transponer();

      resolverSistemaParaAdelante(L, b, y);
      resolverSistemaParaAtras(LT, y, r);
      //

      ganador = maximo(r);
      
    }

    std::cout << "cantidad de partidos: " << cantidadDePartidos << std::endl;
    for (int i = 0 ; i < cantEquipos ; ++i) {
      fileWrite << "equipo: " << i << " ranking: " << std::fixed << r[i] << std::endl; 
    }

  }

  ++z;
  std::cout << z << std::endl;

  return 0;
}

int main(int argc, char** argv) {
  std::string fileTestData(argv[1]);
  std::string fileTestResult(argv[2]);
  int equipo(atoi(argv[3]));
  // Recibo por parametro tres archivos
  // El primero del cual leo los datos a evaluar
  // El segundo en el cual evaluo si los resultados fueron correctos
  // El tercero el método a realizar (0 CMM-EG, 1 CMM-CL, 2 WP)

  evaluarTests(fileTestData, fileTestResult, equipo);

  return 0;
}