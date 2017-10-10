#ifndef _H_LINEACONTROL_
#define _H_LINEACONTROL_

#include <string>
using namespace std;

#define NUMERO_LINEAS_CONTROL 10

/* Clase LineaControl, contiene las lineas de control las cuales pueden ser modificadas */
class LineaControl{
    public:
        LineaControl();
        int linea[NUMERO_LINEAS_CONTROL];
        string toString() const;
        void modificarLinea(size_t numero, int valor);
        int getLinea(size_t pos);
};



#endif
