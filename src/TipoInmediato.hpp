#ifndef _H_TIPOINMEDIATO_
#define _H_TIPOINMEDIATO_

#include <string>
using namespace std;

#include "Instruccion.hpp"
#include "Estado.hpp"
#include "LineaControl.hpp"

/* Clase TipoInmediato, implementa lo necesario para las funciones de tipo Inmediate */
class TipoInmediato: public Instruccion{
    private:
        size_t r1, r2;
	int valor;
    public:
        TipoInmediato(NombreInstruccion nombre, size_t r1, size_t r2, int valor);
        TipoInmediato(string nombre, string r1, string r2, string valor);
        void run(Estado &estado, LineaControl &lineaControl);
};

#endif
