#include <sstream>
#include <stdexcept>
#include "LineaControl.hpp"

/* Constructor de la linea de control, setea las lineas en cero */
LineaControl::LineaControl(){
    for(size_t i = 0; i < NUMERO_LINEAS_CONTROL; i++){
        this->linea[i] = 0;
    }
}

/* Funcion que pasa las lineas de control a string para poder leerlas facilmente. Para uso propio
 * Entrada: vacio
 * Salida: String 
 * */
string LineaControl::toString() const{
    stringstream ss;
    ss << " RegDest  Jump  Branch MemRead MemToReg ALUOp MemWrite ALUSrc RegWrite\n"<< endl;
    for(size_t i = 0; i < NUMERO_LINEAS_CONTROL; i++){
	if(i==6){
            ss <<" "<< this->linea[i] ;
	}else{
            ss << "      " << this->linea[i] ;

	}
    }
    return ss.str();
}

/* Funcion que modifica un valor de las lineas de control
 * Entrada: Size_t numero, int valor
 * Salida: Void
 * */

void LineaControl::modificarLinea(size_t numero, int valor){
    this->linea[numero] = valor;
}

int LineaControl::getLinea(size_t pos){
    return this->linea[pos];
}
