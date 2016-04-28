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
double acum2 = 0;

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

int evaluarTests(std::string fileTestData, std::string fileTestResult, int method) {
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

    for (int i = 0 ; i < cantEquipos ; ++i) {
      C[i][i] = 2.0 + w[i] + l[i];
      b[i] = 1.0 + (w[i] - l[i]) / 2.0; 
    }

    Matriz L(cantEquipos, cantEquipos);

    switch(method) {
      case 0: {

          /* eliminación gaussiana */      
          //gauss(C, b);
          //resolverSistemaParaAtras(C, b, r);
          
          /* eliminación gaussiana con factorización LU */

        int cantResultados = 750;
        for (int k = 0; k < 3; ++k) {


          for (int i = 0; i < cantResultados; ++i) {
          init_time();

          gauss(C, b);

          resolverSistemaParaAtras(C, b, r);

          acum += get_time();
          }
            
        }
        acum /= 3;
        fileWrite << std::fixed << acum << std::endl;
        cantResultados += 50;
        acum = 0;

                /*
        int cantResultados = 500;
        while (cantResultados <= 10000) {

          for (int k = 0; k < 5; ++k) {

            init_time();

            gaussLU(C, L);

            acum += get_time();

            for (int j = 0; j < cantResultados; ++j) {
              vector<float> b2(b); // Vector del sistema Cr = b
              init_time();

              resolverSistemaParaAdelante(L, b, y);
              resolverSistemaParaAtras(C, y, r); //C=U

              acum += get_time();
            }
          }
          acum /= 5;
          fileWrite << std::fixed << acum << std::endl;
          acum = 0;
          std::cout << cantResultados << std::endl;
          cantResultados += 500;
        }
        */


        break;
      }
      case 1: {
//        int cantResultados = 500;
//        while (cantResultados <= 10000) {
//
//          for (int k = 0; k < 5; ++k) {
            init_time();

            cholesky(C, L);
            Matriz LT = L;
            LT.transponer();

//            acum += get_time();
//
//            for (int j = 0; j < cantResultados; ++j) {
//              vector<float> b2(b); // Vector del sistema Cr = b
//
//              init_time();

            LT.mostrar();
            std::cout << "-------------------------------" << std::endl;
            L.mostrar();
              resolverSistemaParaAdelante(L, b, y);
              resolverSistemaParaAtras(LT, y, r);

//              acum += get_time();
//
//            }
//          }
//          acum /= 5;
//          fileWrite << std::fixed << acum << std::endl;
//          acum = 0;
//          std::cout << cantResultados << std::endl;
//          cantResultados += 500;
//        }

        break;
      }
      case 2: {
        for (int i = 0 ; i < cantEquipos ; ++i) {
          r[i] = (float)(w[i] / (float)((w[i] + l[i]))); 
          fileWrite << std::fixed << r[i] << std::endl;
        }
       
        break;
      }
      case 3: {
        for (int k = 0; k < 2; ++k) {
          init_time();

          gaussLU(C, L);

          resolverSistemaParaAdelante(L, b, y);
          resolverSistemaParaAtras(C, y, r); //C=U          
          /*
          cholesky(C, L);
          Matriz LT = L;
          LT.transponer();

          resolverSistemaParaAdelante(L, b, y);
          resolverSistemaParaAtras(LT, y, r);
          */
          
          acum += get_time();
        }
        acum /= 2;
        fileWrite << std::fixed << acum << std::endl; 
        acum = 0;

        break;
              
       }
      case 4: {
        MatrizSimetrica L(cantEquipos, cantEquipos);

        for (int k = 0; k < 3; ++k) {

          init_time();
          choleskySimetrico(C, L);
          MatrizSimetrica LT = L;
          L.setTriangular(true);
          LT.setTriangular(true);
          LT.transponer();

          //LT.mostrar();
          //std::cout << "-------------" << std::endl;
          //L.mostrar();

          resolverSistemaParaAdelanteSim(L, b, y);
          resolverSistemaParaAtrasSim(LT, y, r);

          acum += get_time();

        }
        acum /= 3;
        fileWrite << std::fixed << acum << std::endl; 
        acum = 0;

        break;
          }

      case 5: {
        break;
              }

    }

    //for (int i = 0 ; i < cantEquipos ; ++i) {
    //  fileWrite << "equipo: " << i << " ranking: " << std::fixed << r[i] << std::endl; 
    //}
    ++z;
    std::cout << z << std::endl;

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


/* ESTO ES DE CHACHO */
                /*
                 *
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
          std::cout << "hola escribi aclgo" << std::endl;
                 *
    std::vector<float> r2(cantEquipos, 0);
    std::vector<float> y2(cantEquipos, 0);
    Matriz C2(cantEquipos, cantEquipos);
    vector<float> b2(cantEquipos, cantEquipos);

        int cantResultados = 50;
        while (cantResultados <= 1000) {
          C2 = C;
          y2 = y;
          r2 = r;

          for (int k = 0; k < 5; ++k) {
            init_time();

            cholesky(C2, L);
            Matriz LT = L;
            LT.transponer();

            for (int z = 0; z < cantResultados; ++z) {
              b2 = b;

            resolverSistemaParaAdelante(L, b2, y2);
            resolverSistemaParaAtras(LT, y2, r2);
            }
          acum += get_time();
          }
        acum /= 5;
        fileWrite << std::fixed << acum << std::endl; 
        acum = 0;
        std::cout << cantResultados << std::endl;
        cantResultados += 50;
        }*/

        /*
        int cantResultados = 100;

          for (int k = 0; k < 10; ++k) {
            C2 = C;
            y2 = y;
            r2 = r;

            init_time();

            cholesky(C2, L);
            Matriz LT = L;
            LT.transponer();

            for (int z = 0; z < cantResultados; ++z) {
              b2 = b;

            resolverSistemaParaAdelante(L, b2, y2);
            resolverSistemaParaAtras(LT, y2, r2);
            }
          acum += get_time();
          }
        acum /= 10;
        fileWrite << std::fixed << acum << std::endl; 
        acum = 0;
        std::cout << cantResultados << std::endl;
*/
