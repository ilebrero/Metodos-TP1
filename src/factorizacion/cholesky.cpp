#include "../clases/Matriz.h"
#include <math.h>

void cholesky(Matriz &m, Matriz &L) {
  int n = m.dimensionFilas();
  L[0][0] = (float)sqrt(m[0][0]);

  for (int j = 1 ; j < n ; ++j)
    L[j][0] = m[j][0] / L[0][0];

  for (int i = 1 ; i < n - 1 ; ++i) {
    float auxL = m[i][i];

    for (int k = 0 ; k < i ; ++k) {
      auxL -= (L[i][k] * L[i][k]);
    }

    L[i][i] = (float)sqrt(auxL);

    for (int j = i+1 ; j < n ; ++j) { //(*L)a matriz es cuadrada así que n = columnas
      float auxL = m[j][i];

      for (int k = 0 ; k < i ; ++k)
        auxL -= (L[j][k] * L[i][k]);

    L[j][i] = auxL / L[i][i];
    
    }

  }

  float auxL = m[n-1][n-1];

  for (int k = 0 ; k < n - 1 ; ++k) {
    auxL -= (L[n-1][k] * L[n-1][k]);
  }

  L[n-1][n-1] = (float)sqrt(auxL);

}
/*
int main() {
  Matriz m(3, 3);

  m[0][0] = 4;
  m[1][0] = -1;
  m[2][0] = 1;
  m[0][1] = -1;
  m[1][1] = 4.25;
  m[2][1] = 2.75;
  m[0][2] = 1;
  m[1][2] = 2.75;
  m[2][2] = 3.5;

  m[0][0] = 25;
  m[1][0] = 15;
  m[2][0] = -5;
  m[0][1] = 15;
  m[1][1] = 18;
  m[2][1] = 0;
  m[0][2] = -5;
  m[1][2] = 0;
  m[2][2] = 11;
  m.mostrar();

  Matriz L = cholesky(m);

  std::cout << "------------------------------------------------" << std::endl;

  L.mostrar();

  return 0;
}
*/
