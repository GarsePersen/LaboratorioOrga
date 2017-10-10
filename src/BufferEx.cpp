#include <string>
#include "BufferEx.hpp"

void BufferEx::opCode(string valor){
    this->nombreOperacion = valor;
}

void BufferEx::registros(size_t valor, size_t valor2){
    this->registro = valor;
    this->registro2 = valor2;
}

LineaControl &BufferEx::getLineaControl(){
    return this->lineaControl;
}

void BufferEx::iniciarLineaControl(LineaControl &lineaControl){
    this->lineaControl = lineaControl;
}

void BufferEx::calcularOperacion(size_t rs, size_t rt, size_t rd, int signExt){
    if(this->nombreOperacion == "addi"){
       rt = rs+signExt;
       this->resultado = rt;
    }
    
}

int BufferEx::getResultado(){
    return this->resultado;
}
