#ifndef _H_BEQFALSO
#define _H_BEQFALSO

#include <string>
using namespace std;
#include "InstruccionFalsa.hpp" 

/* Clase BeqFalso, funciona como prototipo para la instruccion BEQ */
class BeqFalso: public InstruccionFalsa{
    private:
        string nombreLabel;
	size_t r1, r2;
    public:
        BeqFalso(string nombreLabel, size_t r1, size_t r2);
        BeqFalso(string nombreLabel, string r1, string r2);
        void run(Estado &estado, LineaControl &lineaControl);
        Instruccion *getReal(size_t pos);
        string getLabel();
};

#endif 
