#ifndef _H_TIPOR_
#define _H_TIPOR_

#include <string>
using namespace std;

#include "Instruccion.hpp"
#include "Estado.hpp"

/* Clase TipoR, implementa lo necesario para las instrucciones tipo R */
class TipoR: public Instruccion{
    private:
        size_t r1, r2, r3;
    public:
        TipoR(NombreInstruccion nombre, size_t r1, size_t r2, size_t r3);
        TipoR(string nombre, string r1, string r2, string r3);
        void run(Estado &estado, LineaControl &lineaControl);
};

#endif
