#include <string>
#include "BufferMem.hpp"

void BufferMem::opCode(string valor){
    this->nombreOperacion = valor;
}

void BufferMem::setRdRt(size_t rd, size_t rt){
    this->rt = rt;
    this->rd = rd;
}

void BufferMem::setResultado(int resultado){
    this->resultado = resultado;
}

size_t BufferMem::getRd(){
    return this->rd;
}

size_t BufferMem::getRt(){
    return this->rt;
}

int BufferMem::getValorRd(){
    return this->valorRd;
}

int BufferMem::getValorRt(){
    return this->valorRt;
}
void BufferMem::regWrite(){
    if((this->nombreOperacion == "add") || (this->nombreOperacion == "sub")){
        this->valorRd = this->resultado;
        this->valorRt = -1;
    }else{
        this->valorRt = this->resultado;
        this->valorRd = -1;
    }
}

LineaControl &BufferMem::getLineaControl(){
    return this->lineaControl;
}

void BufferMem::iniciarLineaControl(LineaControl &lineaControl){
    this->lineaControl = lineaControl;
}
