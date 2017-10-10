#include <string>
#include <iostream>
#include "BufferId.hpp"

using namespace std;

void BufferId::setRsRtRd(size_t rs, size_t rt, size_t rd){
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
}


void BufferId::decode(string valor, int rs, int rt, int rd, int signExt, LineaControl &lineaControl){
    this->nombreOperacion = valor;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->signExt = signExt;
    this->lineaControl = lineaControl;
}

string BufferId::opCode(){
    return this->nombreOperacion;
}

size_t BufferId::getRs(){
    return this->rs;
}

size_t BufferId::getRt(){
    return this->rt;
}

size_t BufferId::getRd(){
    return this->rd;
}

int BufferId::getValorRs(){
    return this->valorRs;
}

int BufferId::getValorRt(){
    return this->valorRt;
}

int BufferId::getValorRd(){
    return this->valorRd;
}

int BufferId::getSignExt(){
    return this->signExt;
}

LineaControl &BufferId::getLineaControl(){
    return this->lineaControl;
}
