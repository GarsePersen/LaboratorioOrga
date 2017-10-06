#include <string>
#include <stdexcept>
using namespace std;

#include "JFalso.hpp"
#include "J.hpp"

/* Constructor de la clase JFalso, recibe el nombre del label y hereda de InstruccionFalsa, con el NombreInstruccion::J*/
JFalso::JFalso(string nombreLabel): InstruccionFalsa(NombreInstruccion::J){
    this->nombreLabel = nombreLabel;
}

/* Funcion que ejecuta el JFalso. Solo notifica de un error ya que no debiese pasar por aqui
 * Entrada: Clase Estado, clase LineaControl
 * Salida: Void */
void JFalso::run(Estado &estado, LineaControl &lineaControl){
    throw logic_error("Error, j falso no se puede ejecutar");
}

/* Funcion que obtiene el J verdadero
 * Entrada: size_t pos
 * Salida: Instruccion Clase J*/
Instruccion *JFalso::getReal(size_t pos){
   return new J(pos);
}

/* Funcion que obtiene el label del J
 * Entrada: Vacio
 * Salida: String */
string JFalso::getLabel(){
   return this->nombreLabel;
}
