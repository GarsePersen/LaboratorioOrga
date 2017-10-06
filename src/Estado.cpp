#include <sstream>
#include <stdexcept>
#include "Estado.hpp"

/* Constructor de la clase estado, inicializa los registros en cero */
Estado::Estado(){
    for(size_t i = 0; i < NUMERO_REGISTROS; i++){
        this->registros[i] = 0;
    }
}

/* Funcion que verifica si el registro se puede modificar, es decir, esta entre el registro cero y treinta y dos
 * Entrada: Size_t numero
 * Salida: Void */
void Estado::verificarRegistro(size_t numero) const{
    if(numero < 0 || numero > NUMERO_REGISTROS){
        throw logic_error("Error en el numero de registro");
    }
}

/* Funcion que modifica el estado de un registro
 * Entrada: Size_t numero, int valor
 * Salida: Void*/
void Estado::modificarRegistro(size_t numero, int valor){
    this->verificarRegistro(numero); 

    this->registros[numero] = valor;
}

/* Funcion que obtiene el valor de un registro
 * Entrada: Size_t numero
 * Salida: Int*/
int Estado::obtenerValor(size_t numero) const{
    return this->registros[numero];
}

/* Funcion que obtiene el valor del programCounter
 * Entrada: Vacio
 * Salida: Int*/
int Estado::programCounter(){
    return this->obtenerValor(32);
}

/* Funcion que modifica el programCounter
 * Entrada: Int valr
 * Salida: Void*/
void Estado::programCounter(int valor){
    return this->modificarRegistro(32, valor);
}

/* Funcion que pasa los registros a string, para uso propio
 * Entrada: Vacio
 * Salida: String*/
string Estado::toString() const{
    stringstream ss;
    
    for(size_t i = 0; i < NUMERO_REGISTROS; i++){
        ss << i << "\t" << this->registros[i] << endl;
    }

    return ss.str();
}
