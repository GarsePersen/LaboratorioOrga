#ifndef _H_BUFFERMEM_
#define _H_BUFFERMEM_

#include <string>
using namespace std;
#include "LineaControl.hpp"


class BufferMem{
    private:
        string nombreOperacion;
        size_t rd, rt;
        int resultado, valorRt, valorRd;
        LineaControl lineaControl;
    public:
        void operacion(string valor);
        void registros(size_t valor, size_t valor2);
        void regWrite();
        void setRdRt(size_t rt, size_t rd);
        size_t getRt();
        size_t getRd();
        int getValorRt();
        int getValorRd();
        void setResultado(int resultado);
        void opCode(string valor);
        void iniciarLineaControl(LineaControl &lineaControl);
        LineaControl &getLineaControl();
};



#endif
