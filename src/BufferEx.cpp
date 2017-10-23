#include <string>
#include <iostream>
#include "BufferEx.hpp"

void BufferEx::setRsRdRt(size_t rs, size_t rd, size_t rt){
    this->rt = rt;
    this->rd = rd;
    this->rs = rs; 
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
        this->resultado = rd+signExt;
    }else if(this->nombreOperacion == "subi"){
        this->resultado = rd-signExt;
    }else if(this->nombreOperacion == "add"){
        this->resultado = rt+rd;
    }
    
    
    else{
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

size_t BufferEx::getRs(){
    return this->rs;
}
