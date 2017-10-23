#include "TipoInmediato.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

/* Constructor de la clase TipoInmediato, recibe el nombre de la instruccion, los registros en size_t y el valor en int */
TipoInmediato::TipoInmediato(NombreInstruccion nombre, size_t r1, size_t r2, int valor): Instruccion(nombre){
    this->r1 = r1;
    this->r2 = r2;
    this->valor = valor;
}

/* Constructor de la clase TipoInmediato, recibe el nombre de la instruccion, los registros en string y el valor en string */
TipoInmediato::TipoInmediato(string nombre, string r1, string r2, string valor): Instruccion(nombre){
    this->r1 = this->storeg(r1);
    this->r2 = this->storeg(r2);
    this->valor = stoi(valor);
}

/* Funcion que ejecuta las instrucciones Inmediate. Modifica las lineas de control, los registros y el programCounter
 * Entrada: Clase Estado, Clase LineaControl
 * Salida: Void*/
void TipoInmediato::run(Estado &estado, LineaControl &lineaControl){
    int valorR2 = estado.obtenerValor(this->r2);
    int result;
    
    lineaControl.modificarLinea(0, 0); 
    lineaControl.modificarLinea(1, 0);
    lineaControl.modificarLinea(2, 0);
    lineaControl.modificarLinea(3, 0);
    lineaControl.modificarLinea(4, 0);
    lineaControl.modificarLinea(5, 0);
    lineaControl.modificarLinea(6, 0);
    lineaControl.modificarLinea(7, 0);
    lineaControl.modificarLinea(8, 1);
    lineaControl.modificarLinea(9, 1);

    switch(this->nombre){
        case NombreInstruccion::Addi:
	     //result = valorR2 + this->valor;
            estado.pipeline("addi", this->r2, this->r1, 0, this->valor, lineaControl);
            break;
        case NombreInstruccion::Subi:
            //result = valorR2 - this->valor;
            estado.pipeline("subi", this->r2, this->r1, 0, this->valor, lineaControl);
            break;
        default:
            throw logic_error("La instruccion no corresponde a un TipoInmediato");
    }
    //estado.modificarRegistro(this->r1, result);
/*    
    lineaControl.modificarLinea(0, 0); 
    lineaControl.modificarLinea(1, 0);
    lineaControl.modificarLinea(2, 0);}
    lineaControl.modificarLinea(3, 0);
    lineaControl.modificarLinea(4, 0);
    lineaControl.modificarLinea(5, 0);
    lineaControl.modificarLinea(6, 0);
    lineaControl.modificarLinea(7, 0);
    lineaControl.modificarLinea(8, 1);
    lineaControl.modificarLinea(9, 1);
    
    estado.programCounter(estado.programCounter() + 1);
    estado.modificarRegistro(this->r1, result);
*/
}

