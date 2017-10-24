#include "BEQ.hpp"
#include "Instruccion.hpp"

/* Constructor de la clase BEQ, recibe los registros y la posicion a saltar del label. Hereda de instruccion */
BEQ::BEQ(size_t pos, int r1, int r2): Instruccion(NombreInstruccion::Beq){
    this->pos = pos;
    this->r1 = r1;
    this->r2 = r2;
}

/* Funcion que ejecuta la instruccion BEQ. Modifica las lineas de control y dependiendo si se cumple
 * la igualdad de los registros, salta o no a la posicion del label
 * Entrada: Clase Estado, clase LineaControl
 * Salida: Void
 * */
void BEQ::run(Estado &estado, LineaControl &lineaControl){
    /*int valorR1 = estado.obtenerValor(this->r1);
    int valorR2 = estado.obtenerValor(this->r2);
    if(valorR1 == valorR2){
    	estado.programCounter(this->pos);
    }else{
        estado.programCounter(estado.programCounter() + 1);
    }*/
    lineaControl.modificarLinea(0, -1);
    lineaControl.modificarLinea(1, 0);
    lineaControl.modificarLinea(2, 1);
    lineaControl.modificarLinea(3, 0);
    lineaControl.modificarLinea(4, -1);
    lineaControl.modificarLinea(5, 0);
    lineaControl.modificarLinea(6, 1);
    lineaControl.modificarLinea(7, 0);
    lineaControl.modificarLinea(8, 0);
    lineaControl.modificarLinea(9, 0);
    estado.pipeline("beq", this->r1, this->pos, this->r2, 0, lineaControl);
}
