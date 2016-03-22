#include <vector>
#include <assert.h>

//h :D

using namespace std;

class Matriz {

private:
	void clean() {
		for (int f = 0; f < filas; ++f) {
			for (int c = 0; c < columnas; ++c) {
				matriz[f][c] = 0;
			}	
		}
	}

public:
	int filas, columnas;
	vector< vector<float> > matriz;

	Matriz(const int filas, const int columnas) {
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

	Matriz& operator * (const int i) {
		for (int f = 0; f < filas; ++f) {
			for (int c = 0; c < columnas; ++c) {
				matriz [f][c] *= i;
			}
		}
		
		return *this;
	}

	Matriz& operator * (const Matriz& m) {
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

	Matriz& operator + (const Matriz& m) {
		if (m.filas == this->filas && m.columnas == this->columnas) {
		
			for (int f = 0; f < filas; ++f) {
				for (int c = 0; c < columnas; ++c) {
					this->matriz[f][c] = this->matriz[f][c] + m.matriz[f][c];
				}
			}
		
		}
		
		return *this;
	}

	Matriz& operator - (const Matriz& m) {
		if (m.filas == this->filas && m.columnas == this->columnas) {
		
			for (int f = 0; f < filas; ++f) {
				for (int c = 0; c < columnas; ++c) {
					this->matriz[f][c] = this->matriz[f][c] - m.matriz[f][c];
				}
			}
		
		}
		
		return *this;
	}

	vector<float>& operator [] (const int fila) {
        return this->matriz[fila];
    }
};
