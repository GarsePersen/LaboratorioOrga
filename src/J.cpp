#include "J.hpp"
#include "Instruccion.hpp"

/* Constructor de la clase J, recibe la posicion a donde debe saltar el label. Hereda de instruccion */
J::J(size_t pos): Instruccion(NombreInstruccion::J){
    this->pos = pos;
}
/* Funcion que ejecuta la instruccion J, cambia el porgamCounter de acuerdo al label y modifica las lineas de control
 * Entrada: Clase Estado, Clase LineaControl
 * Salida: Void
 * */
void J::run(Estado &estado, LineaControl &lineaControl){
    estado.programCounter(this->pos);
    lineaControl.modificarLinea(0, -1);
    lineaControl.modificarLinea(1, 1);
    lineaControl.modificarLinea(2, 0);
    lineaControl.modificarLinea(3, 0);
    lineaControl.modificarLinea(4, -1);
    lineaControl.modificarLinea(5, -1);
    lineaControl.modificarLinea(6, -1);
    lineaControl.modificarLinea(7, 0);
    lineaControl.modificarLinea(8, -1);
    lineaControl.modificarLinea(9, 0);
}
