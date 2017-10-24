#ifndef _H_BUFFEREX_
#define _H_BUFFEREX_

#include <string>
using namespace std;
#include "LineaControl.hpp"

class BufferEx{
    private:
        string nombreOperacion;
        size_t rd, rt, rs;
        size_t pos;
        int resultado;
        LineaControl lineaControl;
    public:
        void opCode(string valor);
        void registros(size_t valor, size_t valor2);
        void calcularOperacion(int rs, int rt, int rd, int signExt);
        void setRsRdRt(size_t rs, size_t rt, size_t rd);
        string opCode();
        int getResultado();
	int saltar;
        size_t getRt();
        size_t getRd();
        size_t getRs();
        void iniciarLineaControl(LineaControl &lineaControl);
        LineaControl &getLineaControl();
};

#endif
