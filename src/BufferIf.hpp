#ifndef _H_BUFFERIF_
#define _H_BUFFERIF_

#include <string>
using namespace std;


class BufferIf{
    private:
        string nombreOperacion;

    public:
        string operacion();
        void operacion(string valor);
};



#endif
