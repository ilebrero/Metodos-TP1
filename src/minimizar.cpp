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

void sort(vector<float>& a, vector<int>& b) {
  for (int i = 0; i < a.size() - 1; ++i) {
    for (int j = 0; j < a.size() - i - 1; ++j) {
      if (a[j] < a[j+1]) {
        float auxA = a[j];
        int auxB = b[j];

        a[j] = a[j+1];
        b[j] = b[j+1];

        a[j+1] = auxA;
        b[j+1] = auxB;
      }
    }
  }
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

int evaluarTests(std::string fileTestData, std::string fileTestResult, int method, int equipo) {
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


    std::vector<float> r(cantEquipos, 0);
    std::vector<float> y(cantEquipos, 0);

    Matriz L(cantEquipos, cantEquipos);

    equipo -= 1;

    if (method == 1) {
      for (int i = 0 ; i < cantEquipos ; ++i) {
        C[i][i] = 2.0 + w[i] + l[i];
        b[i] = 1.0 + (w[i] - l[i]) / 2.0; 
      }

      cholesky(C, L);
      Matriz LT = L;
      LT.transponer();

      resolverSistemaParaAdelante(L, b, y);
      resolverSistemaParaAtras(LT, y, r);

      int cantidadDePartidos = 0;
      int ganador = maximo(r);
      while (ganador != equipo) {
        //std::cout << "ganador: " << ganador << " ranking " << r[ganador] << " ganadas: " << w[ganador] << " perdidas: " << l[ganador] << std::endl;
        //std::cout << "equipo: " << equipo << " ranking " << r[equipo] << " ganadas: " << w[equipo] << " perdidas: " << l[equipo]<< std::endl;
        cantidadDePartidos++;

        C[ganador][equipo]--;
        C[equipo][ganador]--; // Los hago jugar una vez más
        w[equipo]++; // El equipo que quiero llevar arriba gano
        l[ganador]++; // El mejor perdio
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
      vector<int> equipos(cantEquipos);

      for (int i = 0; i < cantEquipos; ++i)
        equipos[i] = i;

      sort(r, equipos);

      for (int j = 0 ; j < cantEquipos ; ++j) {
        if (equipos[j] >= 10) {
          fileWrite << "equipo: " << equipos[j] << " | ranking: " << std::fixed << r[j]; 
        } else {
          fileWrite << "equipo: " << equipos[j] << "  | ranking: " << std::fixed << r[j]; 
        }
        fileWrite << " | ganados: " << std::fixed << w[equipos[j]]; 
        fileWrite << " | perdidos: " << std::fixed << l[equipos[j]] << std::endl; 
      }

    } else {
        if (method == 2) {
          for (int i = 0 ; i < cantEquipos ; ++i) {
            r[i] = w[i] / (float)((w[i] + l[i]));
          }

          int cantidadDePartidos = 0;
          int ganador = maximo(r);

          while (ganador != equipo) {
            cantidadDePartidos++;
            //std::cout << "ganador: " << ganador << " ranking " << r[ganador] << " ganadas: " << w[ganador] << " perdidas: " << l[ganador] << std::endl;
            //std::cout << "equipo: " << equipo << " ranking " << r[equipo] << " ganadas: " << w[equipo] << " perdidas: " << l[equipo]<< std::endl;
            w[equipo]++;
            l[ganador]++;

            r[equipo] = w[equipo] /  (float)((w[equipo] + l[equipo]));
            r[ganador] = w[ganador] /  (float)((w[ganador] + l[ganador]));

            ganador = maximo(r);
          
          }

          std::cout << "cantidad de partidos: " << cantidadDePartidos << std::endl;
          vector<int> equipos(cantEquipos);

          for (int i = 0; i < cantEquipos; ++i)
            equipos[i] = i;

          sort(r, equipos);

          for (int j = 0 ; j < cantEquipos ; ++j) {
            if (equipos[j] >= 10) {
              fileWrite << "equipo: " << equipos[j] << " | ranking: " << std::fixed << r[j]; 
            } else {
              fileWrite << "equipo: " << equipos[j] << "  | ranking: " << std::fixed << r[j]; 
            }
            fileWrite << " | ganados: " << std::fixed << w[equipos[j]]; 
            fileWrite << " | perdidos: " << std::fixed << l[equipos[j]] << std::endl; 
          }

      } else {
          for (int i = 0 ; i < cantEquipos ; ++i) {
            C[i][i] = 2.0 + w[i] + l[i];
            b[i] = 1.0 + (w[i] - l[i]) / 2.0; 
          }

          cholesky(C, L);
          Matriz LT = L;
          LT.transponer();

          resolverSistemaParaAdelante(L, b, y);
          resolverSistemaParaAtras(LT, y, r);

          int cantidadDePartidos = 0;
          int ganador = maximo(r);
          while (ganador != equipo) {
            //std::cout << "ganador: " << ganador << " ranking " << r[ganador] << " ganadas: " << w[ganador] << " perdidas: " << l[ganador] << std::endl;
            //std::cout << "equipo: " << equipo << " ranking " << r[equipo] << " ganadas: " << w[equipo] << " perdidas: " << l[equipo]<< std::endl;
            cantidadDePartidos++;

            C[ganador][equipo]--;
            C[equipo][ganador]--; // Los hago jugar una vez más
            w[equipo]++; // El equipo que quiero llevar arriba gano
            l[ganador]++; // El mejor perdio
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
          vector<int> equipos(cantEquipos);

          for (int i = 0; i < cantEquipos; ++i)
            equipos[i] = i;

          sort(r, equipos);

          for (int j = 0 ; j < cantEquipos ; ++j) {
            if (equipos[j] >= 10) {
              fileWrite << "equipo: " << equipos[j] << " | ranking: " << std::fixed << r[j]; 
            } else {
              fileWrite << "equipo: " << equipos[j] << "  | ranking: " << std::fixed << r[j]; 
            }
            fileWrite << " | ganados: " << std::fixed << w[equipos[j]]; 
            fileWrite << " | perdidos: " << std::fixed << l[equipos[j]] << std::endl; 
          }
      
      }
      }
    }


  return 0;
}

int main(int argc, char** argv) {
  std::string fileTestData(argv[1]);
  std::string fileTestResult(argv[2]);
  int method(atoi(argv[3]));
  int equipo(atoi(argv[4]));
  // Recibo por parametro tres archivos
  // El primero del cual leo los datos a evaluar
  // El segundo en el cual evaluo si los resultados fueron correctos
  // El tercero el método a realizar (0 CMM-EG, 1 CMM-CL, 2 WP)

  evaluarTests(fileTestData, fileTestResult, method, equipo);

  return 0;
}
