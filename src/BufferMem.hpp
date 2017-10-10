#ifndef _H_BUFFERMEM_
#define _H_BUFFERMEM_

#include <string>
using namespace std;
#include "LineaControl.hpp"


class BufferMem{
    private:
        string nombreOperacion;
        size_t rd, rt;
        int resultado;
        LineaControl lineaControl;
    public:
        void operacion(string valor);
        void registros(size_t valor, size_t valor2);
        void regWrite(size_t rt, size_t rd, int resultado);
        void opCode(string valor);
        void iniciarLineaControl(LineaControl &lineaControl);
        LineaControl &getLineaControl();
};



#endif
