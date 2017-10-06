#ifndef _H_LABE
#define _H_LABEL

#include <string>
using namespace std;
#include "Instruccion.hpp" 

/* Clase Label, implementa lo necesario para los labels del programa */
class Label: public Instruccion{
    private:
       string nombre; 
    public:
        Label(string nombre);
        void run(Estado &estado, LineaControl &lineaControl);
        string getLabel() const;
};

#endif 
