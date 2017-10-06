#ifndef _H_JFALSO
#define _H_JFALSO

#include <string>
using namespace std;
#include "InstruccionFalsa.hpp" 

/* Clase JFalso, sirve como prototipo para los J que no se han implementado */
class JFalso: public InstruccionFalsa{
    private:
        string nombreLabel;
    public:
        JFalso(string nombreLabel);
        void run(Estado &estado, LineaControl &lineaControl);
        Instruccion *getReal(size_t pos);
        string getLabel();
};

#endif 
