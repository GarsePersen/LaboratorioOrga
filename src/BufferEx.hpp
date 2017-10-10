#ifndef _H_BUFFEREX_
#define _H_BUFFEREX_

#include <string>
using namespace std;
#include "LineaControl.hpp"

class BufferEx{
    private:
        string nombreOperacion;
        size_t registro, registro2;
        size_t pos;
        int resultado;
        LineaControl lineaControl;
    public:
        void opCode(string valor);
        string opCode();
        void registros(size_t valor, size_t valor2);
        void calcularOperacion(size_t rs, size_t rt, size_t rd, int signExt);
        int getResultado();
        void iniciarLineaControl(LineaControl &lineaControl);
        LineaControl &getLineaControl();
};

#endif
