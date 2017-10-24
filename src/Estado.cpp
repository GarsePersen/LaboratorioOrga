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
    this->hazardControl = "-";
    this->ciclos = 1;
    this->hazardR1 = "-";
    this->hazardR2 = "-";
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

string Estado::regToStr(size_t reg){
    if(reg == 0){
        return "$zero";
    }else if(reg == 1){
        return "$at";
    }else if(reg == 2){
        return "$v0";
    }else if(reg == 3){
        return "$v1";
    }else if(reg == 4){
        return "$a0";    
    }else if(reg == 5){
        return "$a1";
    }else if(reg == 6){
        return "$a2";
    }else if(reg == 7){
        return "$a3";
    }else if(reg == 8){
        return "$t0";
    }else if(reg == 9){
        return "$t1";
    }else if(reg == 10){
        return "$t2";
    }else if(reg == 11){
        return "$t3";
    }else if(reg == 12){
        return "$t4";
    }else if(reg == 13){
        return "$t5";
    }else if(reg == 14){
        return "$t6";
    }else if(reg == 15){
        return "$t7"; 
    }else if(reg == 16){
        return "$s0";
    }else if(reg == 17){
        return "$s1";
    }else if(reg == 18){
        return "$s2";
    }else if(reg == 19){
        return "$s3";
    }else if(reg == 20){
        return "$s4";
    }else if(reg == 21){
        return "$s5";
    }else if(reg == 22){
        return "$s6";
    }else if(reg == 23){
        return "$s7";
    }else if(reg == 24){
        return "$t8";
    }else if(reg == 25){
        return "$t9";
    }else if(reg == 26){
        return "$k0";
    }else if(reg == 27){
        return "$k1";
    }else if(reg == 28){
        return "$gp";
    }else if(reg == 29){
        return "$sp";
    }else if(reg == 30){
        return "$fp";
    }else if(reg == 31){
        return "$ra";
    }
}

void Estado::pipeline(string operacion, size_t rs, size_t rd, size_t rt, int signExt, LineaControl &lineaControl){
    Archivo archivo;
    stringstream ss;
    stringstream ssHazard;
    comprobarForwarding(bufferIf, bufferId);
    //Si forwarding es 1, se aumenta un ciclo las instrucciones que seguian, y antes del lw se agrega un nop
    if(this->forwarding == 1){
        this->bufferWbOpCode=bufferMem.opCode();
        if(bufferMem.getLineaControl().getLinea(9) == 1){
            bufferMem.regWrite();
            modificarRegistro(bufferMem.getRd(), bufferMem.getValorRd());
        }
        bufferMem.iniciarLineaControl(bufferEx.getLineaControl());
        bufferMem.setRsRdRt(bufferEx.getRs(), bufferEx.getRd(), bufferEx.getRt());
        bufferMem.setResultado(bufferEx.getResultado());
        bufferMem.opCode(bufferEx.opCode());
        bufferEx.saltar = 0; 
        bufferEx.opCode(bufferId.opCode());
        bufferEx.iniciarLineaControl(bufferId.getLineaControl());
        bufferEx.calcularOperacion(bufferId.getValorRs(), bufferEx.getResultado(), bufferId.getValorRd(), bufferId.getSignExt());	
        bufferEx.setRsRdRt(bufferId.getRs(), bufferId.getRd(), bufferId.getRt());
        lineaControl.modificarLinea(0, 0); 
        lineaControl.modificarLinea(1, 0);
        lineaControl.modificarLinea(2, 0);
        lineaControl.modificarLinea(3, 0);
        lineaControl.modificarLinea(4, 0);
        lineaControl.modificarLinea(5, 0);
        lineaControl.modificarLinea(6, 0);
        lineaControl.modificarLinea(7, 0);
        lineaControl.modificarLinea(8, 0);
        lineaControl.modificarLinea(9, 0);
        bufferId.decode("NOP", -1, -2, -3, -4, lineaControl);
        bufferId.setRsRtRd(0, 1, 2);
        modificarCiclo(1);
        return;
    }

    comprobarHazard(bufferId, bufferMem);

    if(this->hazardDatos == 0){
        comprobarHazard(bufferId, bufferEx);
    }



    //Esta parte es de la etapa WB, la cual no tiene buffer
    if(this->ciclos > 4){
        //Si escribe en memoria
        if(bufferMem.getLineaControl().getLinea(7) == 1){
            bufferMem.memWrite();
            modificarRegistro(bufferMem.getRd(), bufferMem.getValorRd());
        }
        //Si escribe en registro
        if(bufferMem.getLineaControl().getLinea(9) == 1){
            bufferMem.regWrite();
            modificarRegistro(bufferMem.getRd(), bufferMem.getValorRd());
        }
        this->bufferWbOpCode=bufferMem.opCode();
    }
    if(this->ciclos > 3){
        if(this->hazardDatos == 4){
            bufferMem.setResultado(bufferMem.getValorRd());

        } else {
            bufferMem.setResultado(bufferEx.getResultado());

        }
        bufferMem.iniciarLineaControl(bufferEx.getLineaControl());
        bufferMem.setRsRdRt(bufferEx.getRs(), bufferEx.getRd(), bufferEx.getRt());
        bufferMem.opCode(bufferEx.opCode());
    }

    if(this->ciclos > 2){

        bufferEx.opCode(bufferId.opCode());
        bufferEx.iniciarLineaControl(bufferId.getLineaControl());
        if(this->hazardDatos == 1){
            bufferEx.calcularOperacion(bufferEx.getResultado(), bufferId.getValorRt(), bufferId.getValorRt(), bufferId.getSignExt());
        } else if(this->hazardDatos == 2) {
            bufferEx.calcularOperacion(bufferId.getValorRs(), bufferEx.getResultado(), bufferId.getValorRd(), bufferId.getSignExt());	
        } else if(this->hazardDatos == 3){
            bufferEx.calcularOperacion(bufferEx.getResultado(), bufferEx.getResultado(), bufferId.getValorRd(), bufferId.getSignExt());	
        } else {
            bufferEx.calcularOperacion(bufferId.getValorRs(), bufferId.getValorRt(), bufferId.getValorRd(), bufferId.getSignExt());	
        }
        bufferEx.setRsRdRt(bufferId.getRs(), bufferId.getRd(), bufferId.getRt());
    }

    if(this->ciclos > 1){
        bufferId.decode(bufferIf.getOpCode(), this->registros[bufferIf.getRs()], this->registros[bufferIf.getRt()], this->registros[bufferIf.getRd()], bufferIf.getSignExt(), bufferIf.getLineaControl());
        bufferId.setRsRtRd(bufferIf.getRs(), bufferIf.getRt(), bufferIf.getRd());
    }
    bufferIf.operacion(operacion, rs, rt, rd, signExt, lineaControl);
    ss << "Ciclo: " << this->ciclos << ",";
    ss << bufferIf.getOpCode() <<",";
    ss << bufferId.opCode()<<",";
    ss << bufferEx.opCode() << ",";
    ss << bufferMem.opCode() << ",";
    ss << this->bufferWbOpCode << "\n";
    archivo.escribirArchivoSalidaPipeline(ss.str(), this->nombreArchivoSalida);
    ssHazard << "Ciclo: " << this->ciclos << ",";
    ssHazard << this->hazardControl <<","<<this->hazardR1 <<" " <<this->hazardR2<<"\n";
    archivo.escribirArchivoSalidaHazard(ssHazard.str(), this->nombreArchivoSalidaHazard);
    //Si el beq salta
    if(bufferEx.saltar == 1){
        this->hazardControl = "X";
        programCounter(bufferEx.getRd());
        bufferEx.saltar = 0;
        lineaControl.modificarLinea(0, 0); 
        lineaControl.modificarLinea(1, 0);
        lineaControl.modificarLinea(2, 0);
        lineaControl.modificarLinea(3, 0);
        lineaControl.modificarLinea(4, 0);
        lineaControl.modificarLinea(5, 0);
        lineaControl.modificarLinea(6, 0);
        lineaControl.modificarLinea(7, 0);
        lineaControl.modificarLinea(8, 0);
        lineaControl.modificarLinea(9, 0);
        bufferEx.opCode("FLUSH");
        bufferId.decode("FLUSH", 0, 0, 0, 0, lineaControl);
        bufferIf.operacion("FLUSH",0,0,0,0,lineaControl); 


        modificarCiclo(1);
        return;
    } else {
        this->hazardControl = "-";
    }
    programCounter(programCounter() + 1);
    modificarCiclo(1);
}


void Estado::comprobarHazard(BufferId &bufferId, BufferEx &bufferEx){
    //Si suceden ambas posibilidades
    this->hazardR1 = "-";
    this->hazardR2 = "-";
    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getRd() == bufferId.getRs() && (bufferEx.getRd() == bufferId.getRt()))){
        this->hazardDatos = 3;
	this->hazardR1 = this->regToStr(bufferId.getRs());
	this->hazardR2 = this->regToStr(bufferId.getRt());
        return;
    }
    
    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getRd() == bufferId.getRs())){
        this->hazardDatos = 1;
	this->hazardR1 = this->regToStr(bufferId.getRs());
        return;
    }

    if((bufferEx.getLineaControl().getLinea(9) == 1) && (bufferEx.getRd() == bufferId.getRt())){
        this->hazardDatos = 2;
	this->hazardR2 = this->regToStr(bufferId.getRt());
        return;
    }
    this->hazardDatos = 0;
    return;
}


void Estado::comprobarHazard(BufferId &bufferId, BufferMem &bufferMem){
    //Si suceden ambas posibilidades 
    this->hazardR1 = "-";
    this->hazardR2 = "-";
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getRd() == bufferId.getRs()) && (bufferMem.getRd() == bufferId.getRt())){
        this->hazardDatos = 4;
	this->hazardR1 = this->regToStr(bufferId.getRs());
	this->hazardR2 = this->regToStr(bufferId.getRt());
        return;
    }
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getRd() == bufferId.getRs())){
        this->hazardDatos = 4;
	this->hazardR1 = this->regToStr(bufferId.getRs());
	this->hazardR1 = this->regToStr(bufferId.getRs());
        return;
    }
    if((bufferMem.getLineaControl().getLinea(9) == 1) && (bufferMem.getRd() == bufferId.getRt())){
        this->hazardDatos = 4;
	this->hazardR2 = this->regToStr(bufferId.getRt());
	this->hazardR2 = this->regToStr(bufferId.getRt());
        return;
    }
    this->hazardDatos = 0;
}

void Estado::comprobarForwarding(BufferIf &bufferIf, BufferId &bufferId){
    if(bufferId.getLineaControl().getLinea(3) == 1){
        if((bufferId.getRd() == bufferIf.getRs()) ||(bufferId.getRt() == bufferIf.getRt())){
            this->forwarding = 1;
            return;
        }
    } 
    this->forwarding = 0;
}

























