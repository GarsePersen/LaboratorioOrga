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
        ss << i << "\t" << this->registros[i] << endl;
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


void Estado::pipeline(string operacion, size_t rs, size_t rd, size_t rt, int signExt, LineaControl &lineaControl){
    
	
    comprobarHazard(bufferId, bufferMem);
	
    if(this->hazard == 0){
        comprobarHazard(bufferId, bufferEx);
    }

    int forwarding = 0;
    //stringstream ss;
    
    cout <<"Hazard: "<< this->hazard<<"Ciclo: "<<this->ciclos<<endl;
    

    if(this->ciclos > 3){
        
      //  ss << bufferMem.opCode() << " ";

        for(int aux = 3; aux < this->ciclos; aux++){
          //  ss << "    ";

        }
        //ss <<"IF  ID  EX  MEM WB" << endl;
        //cout << ss.str();
        if(bufferMem.getLineaControl().getLinea(9) == 1){
            bufferMem.regWrite();
            if(bufferMem.opCode() == "addi"){
                modificarRegistro(bufferMem.getRd(), bufferMem.getValorRd());
            }else if(bufferMem.opCode() == "add"){
                cout << bufferMem.getRs() << endl;
                modificarRegistro(bufferMem.getRs(), bufferMem.getValorRs());
            } else {

            }
        }
    }
    if(this->ciclos > 2){
        bufferMem.iniciarLineaControl(bufferEx.getLineaControl());
        bufferMem.setRsRdRt(bufferEx.getRs(), bufferEx.getRd(), bufferEx.getRt());
        bufferMem.setResultado(bufferEx.getResultado());
        bufferMem.opCode(bufferEx.opCode());
    }

    if(this->ciclos > 1){
        
        bufferEx.opCode(bufferId.opCode());
        bufferEx.iniciarLineaControl(bufferId.getLineaControl());
        if(this->hazard == 1){
            bufferEx.calcularOperacion(bufferId.getValorRs(), bufferId.getValorRt(), bufferEx.getResultado(), bufferId.getSignExt());
        } else {
        
            bufferEx.calcularOperacion(bufferId.getValorRs(), bufferId.getValorRt(), bufferId.getValorRd(), bufferId.getSignExt());	
        }
        bufferEx.setRsRdRt(bufferId.getRs(), bufferId.getRd(), bufferId.getRt());
        //cout << bufferId.opCode() <<" "<< bufferId.getRs() <<" "<< bufferId.getRt() <<" "<< bufferId.getRd() <<" "<< bufferId.getSignExt() << endl;
    }

    if(this->ciclos > 0){
        bufferId.decode(bufferIf.getOpCode(), this->registros[bufferIf.getRs()], this->registros[bufferIf.getRt()], this->registros[bufferIf.getRd()], bufferIf.getSignExt(), bufferIf.getLineaControl());
        bufferId.setRsRtRd(bufferIf.getRs(), bufferIf.getRt(), bufferIf.getRd());
    }
    
    bufferIf.operacion(operacion, rs, rt, rd, signExt, lineaControl);
    
    programCounter(programCounter() + 1);
    modificarCiclo(1);
    
    forwarding = comprobarForwarding(bufferIf, bufferId);
}


void Estado::comprobarHazard(BufferId &bufferId, BufferEx &bufferEx){
    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getRd() == bufferId.getRs())){
        this->hazard = 1;
	return;
    }
    
    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getRd() == bufferId.getRt())){
        this->hazard = 1;
	return;
    }
    this->hazard = 0;
    return;
}


void Estado::comprobarHazard(BufferId &bufferId, BufferMem &bufferMem){
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getRd() == bufferId.getRs())){
        this->hazard = 1;
	return;
    }
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getRd() == bufferId.getRt())){
        this->hazard = 1;
	return;
    }
    this->hazard = 0;
}

int Estado::comprobarForwarding(BufferIf &bufferIf, BufferId &bufferId){
    if(bufferId.getRt() == bufferIf.getRs()){
        return 1;
    } 
    
    return 0;
}

























