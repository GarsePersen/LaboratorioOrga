#include <string>
#include "BufferEx.hpp"

void BufferEx::operacion(string valor){
    this->nombreOperacion = valor;
}


void BufferEx::registros(size_t valor, size_t valor2){
    this->registro = valor;
    this->registro2 = valor;

}
