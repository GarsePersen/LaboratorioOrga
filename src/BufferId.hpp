#ifndef _H_BUFFERID_
#define _H_BUFFERID_

#include <string>
using namespace std;
#include "LineaControl.hpp"

class BufferId{
    private:
        string nombreOperacion;
        size_t rs, rt, rd;
        int valorRs, valorRt, valorRd;
	    int signExt;
	    LineaControl lineaControl;
    public:
	    string opCode();
        size_t getRs();
	    size_t getRt();
        size_t getRd();
        int getValorRs();
	    int getValorRt();
        int getValorRd();
	    int getSignExt();
        void decode(string valor, int rs, int rt, int rd, int signExt, LineaControl &lineaControl);
        void setRsRtRd(size_t rs, size_t rt, size_t rd);
        LineaControl &getLineaControl();
};

#endif
