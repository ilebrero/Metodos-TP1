#include "Matriz.h"

Matriz::Matriz(int filas, int columnas) {
  this->filas    = filas;
  this->columnas = columnas;
  vector< vector<float> > m(filas, vector<float>(columnas));
  this->matriz = m;

  for (int i = 0; i < filas; ++i) {
    vector<float> columna(filas);
    matriz[i] = columna;
  }

}

int Matriz::dimensionFilas() {
  return this->filas;
}

int Matriz::dimensionColumnas(){
  return this->columnas;
}

	/*******************************
	 *          Operadores         *
	 *******************************/ 

Matriz& Matriz::operator * (int i) {
  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      matriz [f][c] *= i;
    }
  }
  
  return *this;
}

Matriz& Matriz::operator * (Matriz& m) {
  assert(this->columnas == m.dimensionFilas());

  Matriz * nueva = new Matriz(this->columnas, m.dimensionFilas());

  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      for (int k = 0; k < this->columnas; ++k) {
        nueva->matriz[f][c] += this->matriz[f][k] * m.matriz[k][c];
      }
    }
  }

  return *nueva;
}

Matriz& Matriz::operator * (MatrizSimetrica& m) {
  assert(this->columnas == m.dimensionFilas());

  Matriz * nueva = new Matriz(this->columnas, m.dimensionFilas());

  for (int f = 0; f < this->filas; ++f) {
    for (int c = 0; c < this->columnas; ++c) {
      for (int k = 0; k < this->columnas; ++k) {
        nueva->matriz[f][c] += this->matriz[f][k] * m.get(k,c);
      }
    }
  }

  return *nueva;
}

Matriz& Matriz::operator + (Matriz& m) {
  if (m.dimensionFilas() == this->filas && m.dimensionColumnas() == this->columnas) {
  
    for (int f = 0; f < this->filas; ++f) {
      for (int c = 0; c < this->columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] + m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}

Matriz& Matriz::operator - (Matriz& m) {
  if (m.dimensionFilas() == this->filas && m.dimensionColumnas() == this->columnas) {
  
    for (int f = 0; f < this->filas; ++f) {
      for (int c = 0; c < this->columnas; ++c) {
        this->matriz[f][c] = this->matriz[f][c] - m.matriz[f][c];
      }
    }
  
  }
  
  return *this;
}

vector<float>& Matriz::operator [] (int fila) {
      return this->matriz[fila];
}

void Matriz::randomizar(int semilla) {
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