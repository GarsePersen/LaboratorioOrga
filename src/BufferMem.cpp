#include <string>
#include "BufferMem.hpp"

void BufferMem::opCode(string valor){
    this->nombreOperacion = valor;
}

void BufferMem::setRsRdRt(size_t rs, size_t rd, size_t rt){
    this->rt = rt;
    this->rd = rd;
    this->rs = rs;
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

size_t BufferMem::getRs(){
    return this->rs;
}

int BufferMem::getValorRd(){
    return this->valorRd;
}

int BufferMem::getValorRt(){
    return this->valorRt;
}

int BufferMem::getValorRs(){
    return this->valorRs;
}

string BufferMem::opCode(){
    return this->nombreOperacion;
}

void BufferMem::regWrite(){
    if((this->nombreOperacion == "addi") || (this->nombreOperacion == "subi")){
        this->valorRd = this->resultado;
    }else if(this->nombreOperacion == "add"){
        this->valorRs = this->resultado;
    }
    
    
    else{
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
