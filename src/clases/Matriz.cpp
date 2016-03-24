#include "Matriz.h"
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

//h :D


Matriz::Matriz(const int filas, const int columnas) {
  this->filas    = filas;
  this->columnas = columnas;
  vector< vector<float> > m(filas, vector<float>(columnas));
  this->matriz = m;

  for (int i = 0; i < filas; ++i) {
    vector<float> columna(filas);
    matriz[i] = columna;
  }

}

	/*******************************
	 *          Operadores         *
	 *******************************/ 

Matriz& Matriz::operator * (const int i) {
  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      matriz [f][c] *= i;
    }
  }
  
  return *this;
}

Matriz& Matriz::operator * (const Matriz& m) {
  assert(this->columnas == m.filas);

  Matriz * nueva = new Matriz(this->columnas, m.filas);

  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      for (int k = 0; k < this->columnas; ++k) {
        nueva->matriz[f][c] += this->matriz[f][k] + m.matriz[k][c];
      }
    }
  }

  return *nueva;
}

Matriz& Matriz::operator + (const Matriz& m) {
  if (m.filas == this->filas && m.columnas == this->columnas) {
  
    for (int f = 0; f < filas; ++f) {
      for (int c = 0; c < columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] + m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}

Matriz& Matriz::operator - (const Matriz& m) {
  if (m.filas == this->filas && m.columnas == this->columnas) {
  
    for (int f = 0; f < filas; ++f) {
      for (int c = 0; c < columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] - m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}

vector<float>& Matriz::operator [] (const int fila) {
      return this->matriz[fila];
  }

void Matriz::randomizar(const int semilla) {
  srand( semilla );

  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      matriz[f][c] = rand() % 1000 + 1;
    }	
  }	
}

void Matriz::mostrar() {
  for (int f = 0; f < filas; ++f) {
    cout << "  ";
    for (int c = 0; c < columnas; ++c) {
      if (matriz[f][c] < 0) {
        cout << "| " << matriz[f][c] << "  |" << " ";
      } else {
        cout << "|  " << matriz[f][c] << "  |" << " ";
      }
    }

  cout << endl;
  }
}

	/*******************************
	 *     Funciones privadas      *
	 *******************************/ 

void Matriz::clean() {
  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      matriz[f][c] = 0;
    }
  }
}

/*
int main() {
  Matriz A(5,5);
  A[2][3] = -1;
  A.mostrar();

  return 0;
}
*/
