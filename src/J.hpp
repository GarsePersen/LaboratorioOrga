#ifndef _H_J_
#define _H_J_

#include <string>
using namespace std;
#include "Instruccion.hpp" 

/* Clase J, ayuda a la ejecucion de las instrucciones J*/
class J: public Instruccion{
    private:
        size_t pos;
    public:
        J(size_t pos);
        void run(Estado &estado, LineaControl &lineaControl);
};

#endif 
