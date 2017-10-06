#include <string>
#include <stdexcept>
using namespace std;

#include "Label.hpp"

/* Constructor de la clase Label, recibe el nombre y hereda de Instruccion con el NombreInstruccion::Label */
Label::Label(string nombre): Instruccion(NombreInstruccion::Label){
    this->nombre = nombre;
}

/* Funcion que ejecuta la clase Label, indica de un error ya que no debiese pasar por aqui
 * Entrada: Clase Estado, clase LineaControl
 * Salida: Void */
void Label::run(Estado &estado, LineaControl &lineaControl){
    throw logic_error("Error, label no se puede ejecutar");

}

/* Funcion que obtiene el nombre del label
 * Entrada: Vacio
 * Salida: String */
string Label::getLabel() const{
    return this->nombre;
}


