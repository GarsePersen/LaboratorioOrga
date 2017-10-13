#include <string>
#include <iostream>
#include "BufferEx.hpp"

void BufferEx::setRdRt(size_t rd, size_t rt){
    this->rt = rt;
    this->rd = rd; 
}

void BufferEx::opCode(string valor){
    this->nombreOperacion = valor;
}

string BufferEx::opCode(){
    return this->nombreOperacion;
}

void BufferEx::registros(size_t valor, size_t valor2){
    this->rd = valor;
    this->rt = valor2;
}

LineaControl &BufferEx::getLineaControl(){
    return this->lineaControl;
}

void BufferEx::iniciarLineaControl(LineaControl &lineaControl){
    this->lineaControl = lineaControl;
}

void BufferEx::calcularOperacion(int rs, int rt, int rd, int signExt){
    
    if(this->nombreOperacion == "addi"){
        this->resultado = rs+signExt;
    }else if(this->nombreOperacion == "subi"){
        this->resultado = rs-signExt;
    }else{
        this->resultado = -1;
    }
}

int BufferEx::getResultado(){
    return this->resultado;
}

size_t BufferEx::getRd(){
    return this->rd;
}

size_t BufferEx::getRt(){
    return this->rt;
}
