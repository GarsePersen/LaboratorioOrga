#ifndef _H_BUFFERID_
#define _H_BUFFERID_

#include <string>
using namespace std;


class BufferId{
    private:
        string nombreOperacion;
        size_t registro, registro2;
        size_t pos;
    public:
        void operacion(string valor);
        void registros(size_t valor, size_t valor2);
};



#endif
