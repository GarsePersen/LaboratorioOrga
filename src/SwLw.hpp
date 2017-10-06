#ifndef _H_SwLw_
#define _H_SwLw_

#include <string>
using namespace std;

#include "Instruccion.hpp"
#include "Estado.hpp"
#include "LineaControl.hpp"

/* Clase SwLw, implementa lo necesario para las instrucciones sw y lw*/
class SwLw: public Instruccion{
    private:
        size_t r1, r2;
	    int offset;
    public:
        SwLw(NombreInstruccion nombre, size_t r1, int offset, size_t r2);
        SwLw(string nombre, string r1, string offset, string r2);
        void run(Estado &estado, LineaControl &lineaControl);
};

#endif
