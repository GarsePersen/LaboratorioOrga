#ifndef _H_ESTADO_
#define _H_ESTADO_

#include <string>
using namespace std;
#include "BufferIf.hpp"
#include "BufferId.hpp"
#include "BufferEx.hpp"
#include "BufferMem.hpp"
#include "LineaControl.hpp"
#include "Archivo.hpp"

#define NUMERO_REGISTROS 33

/* Clase Estado, almacena los estados de los 32 registros */
class Estado{
    private:
        int ciclos;
        BufferIf bufferIf;
        BufferId bufferId;
        BufferEx bufferEx;
        BufferMem bufferMem;
        int hazardDatos;
        int hazardControl;
	int forwarding;
	string hazardR1, hazardR2;
        int registros[NUMERO_REGISTROS];
        void verificarRegistro(size_t numero) const;
    public:
        Estado();
	string bufferWbOpCode;
        int obtenerCiclo();
        void modificarCiclo(int valor);
        void pipeline(string operacion, size_t rs, size_t rd, size_t rt, int signExt, LineaControl &lineaControl);
        int programCounter();
        void programCounter(int valor);
        void modificarRegistro(size_t numero, int valor);
        int obtenerValor(size_t numero) const;
	void comprobarHazard(BufferId &bufferId, BufferEx &bufferEx);
	void comprobarHazard(BufferId &bufferId, BufferMem &bufferMem);
        void comprobarForwarding(BufferIf &bufferIf, BufferId &bufferId);
	string regToStr(size_t reg);
        string nombreArchivoSalida;
        string nombreArchivoSalidaHazard;
	string toString() const;
};



#endif
