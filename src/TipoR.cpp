#include "TipoR.hpp"
#include <stdexcept>
using namespace std;

/* Constructor de la clase TipoR, recibe el nombre de la instruccion y los registros como size_t*/
TipoR::TipoR(NombreInstruccion nombre, size_t r1, size_t r2, size_t r3): Instruccion(nombre){
    this->r1 = r1;
    this->r2 = r2;
    this->r3 = r3;
}

/* Constructor de la clase TipoR, recibe el nombre de la instruccion y los registros como string*/
TipoR::TipoR(string nombre, string r1, string r2, string r3): Instruccion(nombre){
    this->r1 = this->storeg(r1);
    this->r2 = this->storeg(r2);
    this->r3 = this->storeg(r3);
}

/* Funcion que ejecuta las instrucciones TipoR, modifica las lineas de control y los registros
 * junto con el programCounter
 * Entrada: Clase Estado, Clase LineaControl
 * Salida: Void*/
void TipoR::run(Estado &estado, LineaControl &lineaControl){
    int valorR2 = estado.obtenerValor(this->r2);
    int valorR3 = estado.obtenerValor(this->r3);
    int result;
    
    switch(this->nombre){
        case NombreInstruccion::Add:
            result = valorR2 + valorR3;
            break;
        case NombreInstruccion::Sub:
            result = valorR2 - valorR3;
            break;
        case NombreInstruccion::Mul:
            result = valorR2 * valorR3;
            break;
        case NombreInstruccion::Div:
	    //Verifica que no se divida por cero
	    if(valorR3 == 0){
                result = 0;
            }else{
                result = valorR2 / valorR3;
	    }
            break;
        default:
            throw logic_error("La instruccion no corresponde a un TipoR");
    }

    lineaControl.modificarLinea(0, 1);
    lineaControl.modificarLinea(1, 0);
    lineaControl.modificarLinea(2, 0);
    lineaControl.modificarLinea(3, 0);
    lineaControl.modificarLinea(4, 0);
    lineaControl.modificarLinea(5, 1);
    lineaControl.modificarLinea(6, 0);
    lineaControl.modificarLinea(7, 0);
    lineaControl.modificarLinea(8, 0);
    lineaControl.modificarLinea(9, 1);
    
    estado.programCounter(estado.programCounter() + 1);
    estado.modificarRegistro(this->r1, result);
}

