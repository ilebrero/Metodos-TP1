#include <vector>

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
	vector< vector<int> > matriz;

	Matriz() {
		filas    = 5;
		columnas = 5;
		matriz = *(new vector< vector<int> > (5));

		for (int i = 0; i < 5; ++i) {
			matriz.push_back( *(new vector <int> (5)) );
		}
	}

	Matriz(const int filas, const int columnas) {
		this->filas    = filas;
		this->columnas = columnas;
		matriz = *(new vector< vector<int> > (filas));

		for (int i = 0; i < filas; ++i) {
			matriz.push_back( *(new vector <int> (columnas)) );
		}
	}

	Matriz& operator+ (const Matriz& m) {
		if (m.filas == this->filas && m.columnas == this->columnas) {
		
			for (int f = 0; f < filas; ++f) {
				for (int c = 0; c < columnas; ++c) {
					this->matriz[f][c] = this->matriz[f][c] + m.matriz[f][c];
				}
			}
		
		}
		
		return *this;
	}

	Matriz& operator- (const Matriz& m) {
		if (m.filas == this->filas && m.columnas == this->columnas) {
		
			for (int f = 0; f < filas; ++f) {
				for (int c = 0; c < columnas; ++c) {
					this->matriz[f][c] = this->matriz[f][c] - m.matriz[f][c];
				}
			}
		
		}
		
		return *this;
	}

	Matriz& operator* (const Matriz& m) { 
		Matriz* nueva = NULL;

		if (this->columnas == m.filas) {
			Matriz* nueva = new Matriz(m.filas, m.filas);

			for (int f = 0; f < this->filas; ++f) {
				for (int c = 0; c < this->columnas; ++c) {
					for (int k = 0; k < this->columnas; ++k) {
						nueva[f][c] += this->matriz[f][k] + m.matriz[k][c];
					}
				}
			}

		}

		return *nueva;
	}

	void set(const int i, const int j, int valor) {
		this->matriz[i][j] = valor;
	}

	int get(const int i, const int j) {
		return this->matriz[i][j];
	}

	Matriz& operator* (const int i) {
		for (int f = 0; f < filas; ++f) {
			for (int c = 0; c < columnas; ++c) {
				matriz [f][c] *= i;
			}
		}
		
		return *this;
	}
};