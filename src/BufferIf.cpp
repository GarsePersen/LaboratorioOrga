#include <string>
#include "BufferIf.hpp"

string BufferIf::operacion(){
    return this->nombreOperacion;
}

void BufferIf::operacion(string valor){
    this->nombreOperacion = valor;

}
