#include <vector>

using namespace std;

class Matriz {

  public:

    Matriz(const int filas, const int columnas);

    Matriz& operator * (const int i);
    Matriz& operator * (const Matriz& m);

    Matriz& operator + (const Matriz& m);

    Matriz& operator - (const Matriz& m);

    vector<float>& operator [] (const int fila);

    void randomizar(const int semilla);
    void mostrar();

  private:

	/*******************************
	 *          Variables          *
	 *******************************/ 

    int filas, columnas;
    vector< vector<float> > matriz;

	/*******************************
	 *          Funciones          *
	 *******************************/ 

    void clean();
};
