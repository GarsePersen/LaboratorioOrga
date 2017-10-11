#ifndef _H_BUFFEREX_
#define _H_BUFFEREX_

#include <string>
using namespace std;
#include "LineaControl.hpp"

class BufferEx{
    private:
        string nombreOperacion;
        size_t rd, rt;
        size_t pos;
        int resultado;
        LineaControl lineaControl;
    public:
        void opCode(string valor);
        string opCode();
        void registros(size_t valor, size_t valor2);
        void calcularOperacion(int rs, int rt, int rd, int signExt);
        void setRdRt(size_t rt, size_t rd);
        int getResultado();
        size_t getRt();
        size_t getRd();
        void iniciarLineaControl(LineaControl &lineaControl);
        LineaControl &getLineaControl();
};

#endif
