#ifndef _H_ESTADO_
#define _H_ESTADO_

#include <string>
using namespace std;

#define NUMERO_REGISTROS 33

/* Clase Estado, almacena los estados de los 32 registros */
class Estado{
    private:
        int registros[NUMERO_REGISTROS];
        void verificarRegistro(size_t numero) const;
    public:
        Estado();
	int programCounter();
	void programCounter(int valor);
	void modificarRegistro(size_t numero, int valor);
        int obtenerValor(size_t numero) const;
        string toString() const;
};



#endif
