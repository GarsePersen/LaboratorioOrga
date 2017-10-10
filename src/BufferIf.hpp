#ifndef _H_BUFFERIF_
#define _H_BUFFERIF_

#include <string>
using namespace std;
#include "LineaControl.hpp"

class BufferIf{
    private:
        string nombreOperacion;
        size_t rs, rt, rd;
	int signExt;
	LineaControl lineaControl;
    public:
        string getOpCode();
        size_t getRs();
	size_t getRt();
        size_t getRd();
	int getSignExt();
        void operacion(string valor, size_t rs, size_t rt, size_t rd, int signExt, LineaControl &lineaControl);
        LineaControl &getLineaControl();
};



#endif
