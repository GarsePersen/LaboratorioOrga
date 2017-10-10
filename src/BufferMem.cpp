#include <string>
#include "BufferMem.hpp"

void BufferMem::opCode(string valor){
    this->nombreOperacion = valor;
}

void BufferMem::regWrite(size_t rt, size_t rd, int resultado){

}

LineaControl &BufferMem::getLineaControl(){
    return this->lineaControl;
}

void BufferMem::iniciarLineaControl(LineaControl &lineaControl){
    this->lineaControl = lineaControl;
}
