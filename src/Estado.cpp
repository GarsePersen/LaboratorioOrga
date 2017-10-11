#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Estado.hpp"

using namespace std;

/* Constructor de la clase estado, inicializa los registros en cero */
Estado::Estado(){
    for(size_t i = 0; i < NUMERO_REGISTROS; i++){
        this->registros[i] = 0;
    }
    this->ciclos = 0;
}

/* Funcion que verifica si el registro se puede modificar, es decir, esta entre el registro cero y treinta y dos
 * Entrada: Size_t numero
 * Salida: Void */
void Estado::verificarRegistro(size_t numero) const{
    if(numero < 0 || numero > NUMERO_REGISTROS){
        throw logic_error("Error en el numero de registro");
    }
}

/* Funcion que modifica el estado de un registro
 * Entrada: Size_t numero, int valor
 * Salida: Void*/
void Estado::modificarRegistro(size_t numero, int valor){
    this->verificarRegistro(numero); 
    this->registros[numero] = valor;
}

/* Funcion que obtiene el valor de un registro
 * Entrada: Size_t numero
 * Salida: Int*/
int Estado::obtenerValor(size_t numero) const{
    return this->registros[numero];
}

/* Funcion que obtiene el valor del programCounter
 * Entrada: Vacio
 * Salida: Int*/
int Estado::programCounter(){
    return this->obtenerValor(32);
}

/* Funcion que modifica el programCounter
 * Entrada: Int valr
 * Salida: Void*/
void Estado::programCounter(int valor){
    return this->modificarRegistro(32, valor);
}

/* Funcion que pasa los registros a string, para uso propio
 * Entrada: Vacio
 * Salida: String*/
string Estado::toString() const{
    stringstream ss;
    
    for(size_t i = 0; i < NUMERO_REGISTROS; i++){
        //ss << i << "\t" << this->registros[i] << endl;
    }
    ss << " " << endl;
    return ss.str();
}

int Estado::obtenerCiclo(){
    return this->ciclos;
}

void Estado::modificarCiclo(int valor){
    this->ciclos = obtenerCiclo() + valor;
}


void Estado::pipeline(string operacion, size_t rs, size_t rt, size_t rd, int signExt, LineaControl &lineaControl){
    int hazard = 0;
    int forwarding = 0;
    if(this->ciclos > 3){
        if(bufferMem.getLineaControl().getLinea(9) == 1){
            bufferMem.regWrite();
            if(bufferMem.getValorRd() == -1){
                modificarRegistro(bufferMem.getRt(), bufferMem.getValorRt());
                cout << this->registros[bufferMem.getRt()] << endl;
            }else{
                modificarRegistro(bufferMem.getRd(), bufferMem.getValorRd());
            } 
        }
    }
    if(this->ciclos > 2){
        bufferMem.iniciarLineaControl(bufferEx.getLineaControl());
        bufferMem.setRdRt(bufferEx.getRd(), bufferEx.getRt());
        bufferMem.setResultado(bufferEx.getResultado());
    }
    
    if(this->ciclos > 1){
        bufferEx.opCode(bufferId.opCode());
        bufferEx.iniciarLineaControl(bufferId.getLineaControl());
        bufferEx.calcularOperacion(bufferId.getValorRs(), bufferId.getValorRt(), bufferId.getValorRd(), bufferId.getSignExt());	
        bufferEx.setRdRt(bufferId.getRd(), bufferId.getRt());
    }

    if(this->ciclos > 0){
        bufferId.decode(bufferIf.getOpCode(), this->registros[bufferIf.getRs()], this->registros[bufferIf.getRt()], this->registros[bufferIf.getRd()], bufferIf.getSignExt(), bufferIf.getLineaControl());
        bufferId.setRsRtRd(bufferIf.getRs(), bufferIf.getRt(), bufferIf.getRd());
        forwarding = comprobarForwarding(bufferIf, bufferId);
    }
    
    bufferIf.operacion(operacion, rs, rt, rd, signExt, lineaControl);
    
	
	
	hazard = comprobarHazard(bufferId, bufferEx);

	
    programCounter(programCounter() + 1);
    modificarCiclo(1);
	hazard = comprobarHazard(bufferId, bufferMem);
	
    if(hazard == 0){
        hazard = comprobarHazard(bufferId, bufferEx);
    
    }
    
    forwarding = comprobarForwarding(bufferIf, bufferId);
    
}




int Estado::comprobarHazard(BufferId &bufferId, BufferEx &bufferEx){
    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getLineaControl().getLinea(0) != 0) && (bufferEx.getLineaControl().getLinea(0) == bufferId.getLineaControl().getLinea(0))){
        return 1;
    }
    return 0;
}


int Estado::comprobarHazard(BufferId &bufferId, BufferMem &bufferMem){
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getLineaControl().getLinea(0) != 0) && (bufferMem.getLineaControl().getLinea(0) == bufferId.getLineaControl().getLinea(0))){
        return 1;
    }
    return 0;
}

int Estado::comprobarForwarding(BufferIf &bufferIf, BufferId &bufferId){
    if(bufferId.getRt() == bufferIf.getRs()){
        return 1;
    } 
    
    return 0;
}

























