#include <string>
#include <stdexcept>

using namespace std;

#include "BEQ.hpp" 
#include "BeqFalso.hpp"

/* Constructor de la clase BeqFalso, recibe el nombreLabel, y los registros en size_t */
BeqFalso::BeqFalso(string nombreLabel, size_t r1, size_t r2): InstruccionFalsa(NombreInstruccion::Beq){
    this->r1 = r1;
    this->r2 = r2;
    this->nombreLabel = nombreLabel;
}

/* Constructor de la clase BeqFalso, recibe el nombreLabel y los registros en string */
BeqFalso::BeqFalso(string nombreLabel, string r1, string r2): InstruccionFalsa(NombreInstruccion::Beq){
    this->r1 = this->storeg(r1);
    this->r2 = this->storeg(r2);
    this->nombreLabel = nombreLabel;
}

/* Funcion que ejecuta el BeqFalso, indica un error ya que no debiese pasar por aqui 
 * Entrada: Clase Estado, clase LineaControl
 * Salida: Vacio*/
void BeqFalso::run(Estado &estado, LineaControl &lineaControl){
    throw logic_error("Error, Beq falso no se puede ejecutar");
}

/* Funcion que obtiene el BEQ real
 * Entrada: Size_t pos
 * Salida: Instruccion Clase BEQ */
Instruccion *BeqFalso::getReal(size_t pos){
    return new BEQ(pos, this->r1, this->r2);
}

/* Funcion que obtiene el label del BeqFalso
 * Entrada: Vacio
 * Salida: String */
string BeqFalso::getLabel(){
   return this->nombreLabel;
}
