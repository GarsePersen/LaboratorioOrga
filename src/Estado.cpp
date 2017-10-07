#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Estado.hpp"

using namespace std;

/* Constructor de la clase estado, inicializa los registros en cero */
Estado::Estado(){
    for(size_t i = 0; i < NUMERO_REGISTROS; i++){
        this->registros[i] = 0;
    }
    this->ciclos = 0;
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

int Estado::obtenerCiclo(){
    return this->ciclos;
}

void Estado::modificarCiclo(int valor){
    this->ciclos = obtenerCiclo() + valor;
}


void Estado::pipeline(string operacion, size_t registro, size_t registro2){
    if(this->obtenerCiclo()==0){
        cout << "Paso if" << endl;
        bufferIf.operacion(operacion);
    //If+Id
    }else if(this->obtenerCiclo()==1){
        cout << "Paso id" << endl;
        bufferId.operacion(bufferIf.operacion());                   
        bufferId.registros(registro, registro2);
        
        bufferIf.operacion(operacion);
        
    //If+Id+Ex
    }else if(this->obtenerCiclo()==2){
        cout << "Paso ex" << endl;
    //If+Id+Ex+Mem                
    }else if(this->obtenerCiclo()==3){
        cout << "Paso mem" << endl;                
    //If+Id+Ex+Mem+Wb
    }else if(this->obtenerCiclo()==4){
        cout << "Paso wb" << endl;                
    }else{
        cout << "Paso mas del wb" << endl;                
    }
    cout << bufferIf.operacion() << endl;
    programCounter(programCounter() + 1);
    modificarCiclo(1);
}

































