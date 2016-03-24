#include "../clases/Matriz.h"
//#include <assert.h>

void combLineal(Matriz &m, int j, float k, int i){ //E_j = E_j + k*E_i
  assert (i < m.dimensionFilas());
  assert (j < m.dimensionFilas());
  
  for(int t = 0; t < m.dimensionColumnas(); ++t) m[j][t] = m[j][t] - k*m[i][t]; 
}

void permutar(Matriz &m, int i, int j){ //permuta fila i con j
  assert (i < m.dimensionFilas());
  assert (j < m.dimensionFilas());

  float aux;

  for(int k = 0; k < m.dimensionColumnas(); ++k){
    aux = m[j][k];
    m[j][k] = m[i][k];
    m[i][k] = aux;
  }
}

void gauss(Matriz& m) {
  int n = m.dimensionFilas();
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
      if(m[i][i] != 0){
        float k = m[j][i]/m[i][i];
        combLineal(m, j, k, i); //fila j + k * fila i
      } else {
        permutar(m, i, i+1);
      }
    }
  }
}

/*
int main(){
  
  Matriz m (4,4);
  m[0][0] = 1; 
  m[1][2] = 1; 
  m[1][3] = 1; 
  m[2][1] = 1; 
  m[3][1] = 2; 
  m[3][2] = 1;
  m[3][3] = 1;

  m.mostrar();
  gauss(m);
  m.mostrar();

  return 0;
}
*/
