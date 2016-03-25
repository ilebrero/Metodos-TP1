#include "MatrizSimetrica.h"

MatrizSimetrica::MatrizSimetrica(const int filas, const int columnas) {
  this->filas    = filas;
  this->columnas = columnas;
  vector< vector<float> > m(filas, vector<float>(filas));
  this->matriz = m;

  for (int i = 0; i < filas; ++i) {
    vector<float> fila(i+1); // <- para la matriz simetrica
    matriz[i] = fila;
  }
}

int MatrizSimetrica::dimensionFilas() const {
  return this->filas;
}

int MatrizSimetrica::dimensionColumnas() const {
  return this->columnas;
}

    /*******************************
     *          Operadores         *
     *******************************/ 

float MATRIZ_H_

float MatrizSimetrica::get(const int f, const int c) {
  if (c < f) {
    return m [f][c];
  } else {
    return m [c][f];
  }
}

float MatrizSimetrica::set(const int f, const int c, const float valor) {
  if (c < f) {
    m [f][c] = valor;
  }
}

MatrizSimetrica& MatrizSimetrica::operator * (const int i) {
  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      matriz.get(f, c) *= i;
    }
  }
  
  return *this;
}

Matriz& MatrizSimetrica::operator * (const Matriz& m) {
  assert(this->columnas == m.dimensionFilas());

  Matriz * nueva = new Matriz(this->columnas, m.dimensionFilas());

  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      for (int k = 0; k < this->columnas; ++k) {
        nueva->matriz[f][c] += this->get(f,k) + m.matriz[k][c];
      }
    }
  }

  return *nueva;
}

Matriz& MatrizSimetrica::operator * (const MatrizSimetrica& m) {
  assert(this->columnas == m.dimensionFilas());

  Matriz * nueva = new Matriz(this->columnas, m.dimensionFilas());

  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      for (int k = 0; k < this->columnas; ++k) {
        nueva->matriz[f][c] += this->get(f,k) + m.get(k,c);
      }
    }
  }

  return *nueva;
}

/*
Matriz& MatrizSimetrica::operator + (const Matriz& m) {

  Matriz * nueva = new Matriz(this->columnas, m.dimensionFilas());

  if (m.dimensionFilas() == this->filas && m.dimensionColumnas() == this->columnas) {
  
    for (int f = 0; f < this->filas; ++f) {
      for (int c = 0; c < this->columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] + m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}

Matriz& MatrizSimetrica::operator - (const Matriz& m) {
  if (m.dimensionFilas() == this->filas && m.dimensionColumnas() == this->columnas) {
  
    for (int f = 0; f < this->filas; ++f) {
      for (int c = 0; c < this->columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] - m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}
*/

void MatrizSimetrica::randomizar(const int semilla) {
  srand( semilla );

  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      matriz[f][c] = rand() % 1000 + 1;
    }   
  } 
}

void MatrizSimetrica::mostrar() {
  for (int f = 0; f < filas; ++f) {
    cout << "  ";
    for (int c = 0; c < columnas; ++c) {
      if (this->get(f,c) < 0) {
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

void MatrizSimetrica::clean() {
  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      matriz[f][c] = 0;
    }
  }
}

int main() {
  MatrizSimetrica m(5, 5);
  m.set(0,0)
}