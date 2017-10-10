#ifndef _H_ESTADO_
#define _H_ESTADO_

#include <string>
using namespace std;
#include "BufferIf.hpp"
#include "BufferId.hpp"
#include "BufferEx.hpp"
#include "BufferMem.hpp"
#include "LineaControl.hpp"

#define NUMERO_REGISTROS 33

/* Clase Estado, almacena los estados de los 32 registros */
class Estado{
    private:
        int ciclos;
        BufferIf bufferIf;
        BufferId bufferId;
        BufferEx bufferEx;
        BufferEx bufferMem;
        int registros[NUMERO_REGISTROS];
        void verificarRegistro(size_t numero) const;
    public:
        Estado();
        int obtenerCiclo();
        void modificarCiclo(int valor);
        void pipeline(string operacion, size_t rs, size_t rt, size_t rd, int signExt, LineaControl &lineaControl);
        int programCounter();
        void programCounter(int valor);
        void modificarRegistro(size_t numero, int valor);
        int obtenerValor(size_t numero) const;
	    int comprobarHazard(BufferId &bufferId, BufferEx &bufferEx);
	    int comprobarHazard(BufferId &bufferId, BufferMem &bufferMem);
        int comprobarForwarding(BufferIf &bufferIf, BufferId &bufferId);
        string toString() const;
};



#endif
