#ifndef _H_INSTRUCCION_
#define _H_INSTRUCCION_

#include <string>
using namespace std;

#include "LineaControl.hpp"
#include "Estado.hpp"

/* Enum con los tipos de instrucciones que permite el programa */
enum class NombreInstruccion{
    Add,
    Sub,
    Addi,
    Subi,
    J,
    Beq,
    Mul,
    Div,
    Lw,
    Sw,
    Label
};

/* Clase Instruccion, ayuda a identificar las instrucciones. El metodo virtual void run se ejecuta en las instrucciones
 * que heredan de esta clase */
class Instruccion{
    protected:
        NombreInstruccion nombre;

        size_t storeg(string str);

    public:
        Instruccion(NombreInstruccion nombre);
        Instruccion(string nombre);

        virtual void run(Estado &estado, LineaControl &lineaControl) = 0;

        /*Retorna una reresentacion en string de la instruccion*/
        string toString() const;
};

#endif
