#include "../clases/Matriz.h"
#include <math.h>

Matriz& cholesky(Matriz &m) {
  int n = m.dimensionFilas();
  Matriz *matriz = new Matriz(n, n); 
  Matriz L(n, n);
  L = *matriz;
  L[1][1] = (float)sqrt(m[1][1]);

  for (int j = 1 ; j < n ; ++j)
    L[j][1] = m[j][1] / L[1][1];

  for (int i = 1 ; i < n - 1 ; ++i) {
    float auxL = m[i][i];

    for (int k = 0 ; k < i ; ++k)
      auxL -= (L[i][k] * L[i][k]);

    L[i][i] = sqrt(auxL);

    for (int j = i+1 ; j < n ; ++j) { //La matriz es cuadrada así que n = columnas
      float auxL = m[j][i];

      for (int k = 0 ; k < i ; ++k)
        auxL -= (L[j][k] * L[i][k]);

    L[j][i] = auxL / L[i][i];
    
    }

  }

  float auxL = m[n-1][n-1];

  for (int k = 0 ; k < n - 1 ; ++k)
    auxL -= (L[n-1][k]);

  L[n-1][n-1] = sqrt(auxL);

  return *matriz;

}
