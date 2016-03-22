#include <vector>

//h :D

using namespace std;

class Matriz {

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

	//falta
	Matriz& operator* (const Matriz& m) { return *this; }


	Matriz& operator[][] (const Matriz& m, int i, int j) { 
		return this->matriz[i][j];
	}

	void set(int i, int j, int valor) {
		this->matriz[i][j] = valor;
	}

	void get(int i, int j) {
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