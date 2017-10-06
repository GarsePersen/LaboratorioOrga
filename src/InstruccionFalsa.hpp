#ifndef _H_INSTRUCCIONFALSA
#define _H_INSTRUCCIONFALSA

#include <string>
using namespace std;

#include "Instruccion.hpp"

/* Clase InstruccionFalsa, sirve como prototipo para las instrucciones falsas, las BEQ y J que aun no se han modificado */
class InstruccionFalsa: public Instruccion{
    public:
        InstruccionFalsa(string nombre);
        InstruccionFalsa(NombreInstruccion nombre);
        virtual void run(Estado &estado, LineaControl &lineaControl) = 0;
        virtual string getLabel() = 0;
        virtual Instruccion *getReal(size_t pos) = 0;
};

#endif 
