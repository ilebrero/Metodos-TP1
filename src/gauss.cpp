#include "clases/Matriz.cpp"
//#include <assert.h>

void combLineal(Matriz &m, int j, float k, int i){ //E_j = E_j + k*E_i
  assert (i <= m.filas);
  assert (j <= m.filas);
  
  for(int t = 1; t <= m.columnas; ++t) m[j][t] = m[j][t] + k*m[i][t]; 
}

void permutar(Matriz &m, int i, int j){ //permuta fila i con j
  assert (i <= m.filas);
  assert (j <= m.filas);

  float aux;

  for(int k = 1; k <= m.columnas; ++k){
    aux = m[j][k];
    m[j][k] = m[i][k];
    m[i][k] = aux;
  }
}

void gauss(Matriz& m) {
  int n = m.filas;
  for(int i = 1; i <= n-1; ++i){
    for(int j = i+1; j <= n; ++j){
      if(m[i][i] != 0){
        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j + k * fila i
      } else {
        permutar(m, i, i+1);
      }
    }  
  }
}

