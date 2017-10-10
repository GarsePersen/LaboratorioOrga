#include <string>
#include "BufferIf.hpp"

string BufferIf::getOpCode(){
    return this->nombreOperacion;
}

size_t BufferIf::getRs(){
    return this->rs;
}

size_t BufferIf::getRt(){
    return this->rt;
}

size_t BufferIf::getRd(){
    return this->rd;
}

int BufferIf::getSignExt(){
    return this->signExt;
}

void BufferIf::operacion(string valor, size_t rs, size_t rt, size_t rd, int signExt, LineaControl &lineaControl){
    this->nombreOperacion = valor;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->signExt = signExt;
    this->lineaControl = lineaControl;
}

LineaControl &BufferIf::getLineaControl(){
    return this->lineaControl;
}
