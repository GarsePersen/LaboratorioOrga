#include "Instruccion.hpp"
#include "InstruccionFalsa.hpp"
#include "Label.hpp"
#include <algorithm>
#include <locale>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <unordered_map>
#include <utility>
#include <sstream>
using namespace std;

/* Constructor de la clase instruccion, recibe el nombre de la instruccion */
Instruccion::Instruccion(NombreInstruccion nombre){
    this->nombre = nombre;
}

/* Constructor de la clase instruccion, recibe el nombre de la instruccion en string dependiendo, lo inicializa de
 * acuerdo a la instruccion
 * Entrada: String nombre */
Instruccion::Instruccion(string nombre){
    transform(nombre.begin(), nombre.end(), nombre.begin(), [](char c){ return tolower(c); });
    if(nombre == "addi"){
        this->nombre = NombreInstruccion::Addi;
    }else if(nombre == "subi"){
        this->nombre = NombreInstruccion::Subi;
    }else if(nombre == "label"){
        this->nombre = NombreInstruccion::Label;
    }else if(nombre == "j"){
        this->nombre = NombreInstruccion::J;
    }else if(nombre == "beq"){
        this->nombre = NombreInstruccion::Beq;
    }else if(nombre == "add"){
        this->nombre = NombreInstruccion::Add;
    }else if(nombre == "sub"){
	this->nombre = NombreInstruccion::Sub;
    }else if(nombre == "mul"){
        this->nombre = NombreInstruccion::Mul;
    }else if(nombre == "div"){
        this->nombre = NombreInstruccion::Div;
    }else if(nombre == "sw"){
        this->nombre = NombreInstruccion::Sw;
    }else if(nombre == "lw"){
        this->nombre = NombreInstruccion::Lw;
    }else{
        throw logic_error("Falta un caso en el constructor de string de Instruccion, verifique que anoto bien las instrucciones en el archivo de entrada.");
    }
}

/* Funcion que crea un string dependiendo del nombre de la instruccion 
 * Entrada: Vacio
 * Salida: String*/
string Instruccion::toString() const{
    switch(this->nombre){
        case NombreInstruccion::Add:
            return "Add";
        case NombreInstruccion::Sub:
            return "Sub";
        case NombreInstruccion::Addi:
            return "Addi";
        case NombreInstruccion::Subi:
            return "Subi";
        case NombreInstruccion::Label:
            return "Label";
        case NombreInstruccion::Beq:
            return "Beq";
        case NombreInstruccion::J:
            return "J";
        case NombreInstruccion::Mul:
            return "Mul";
        case NombreInstruccion::Div:
            return "Div";
        case NombreInstruccion::Lw:
            return "Lw";
        case NombreInstruccion::Sw:
            return "Sw";
        default:
            return "Falta un caso en __LINE__";
    }
}

/* Funcion que pasa de un string que representa a un registro, a un numero size_t
 * Entrada: String str
 * Salida: Size_t*/
size_t Instruccion::storeg(string str){
    if(str == "$zero"){
        return 0;
    }else if(str == "$at"){
        return 1;
    }else if(str == "$v0"){
        return 2;
    }else if(str == "$v1"){
        return 3;
    }else if(str == "$a0"){
        return 4;    
    }else if(str == "$a1"){
        return 5;
    }else if(str == "$a2"){
        return 6;
    }else if(str == "$a3"){
        return 7;
    }else if(str == "$t0"){
        return 8;
    }else if(str == "$t1"){
        return 9;
    }else if(str == "$t2"){
        return 10;
    }else if(str == "$t3"){
        return 11;
    }else if(str == "$t4"){
        return 12;
    }else if(str == "$t5"){
        return 13;
    }else if(str == "$t6"){
        return 14;
    }else if(str == "$t7"){
        return 15; 
    }else if(str == "$s0"){
        return 16;
    }else if(str == "$s1"){
        return 17;
    }else if(str == "$s2"){
        return 18;
    }else if(str == "$s3"){
        return 19;
    }else if(str == "$s4"){
        return 20;
    }else if(str == "$s5"){
        return 21;
    }else if(str == "$s6"){
        return 22;
    }else if(str == "$s7"){
        return 23;
    }else if(str == "$t8"){
        return 24;
    }else if(str == "$t9"){
        return 25;
    }else if(str == "$k0"){
        return 26;
    }else if(str == "$k1"){
        return 27;
    }else if(str == "$gp"){
        return 28;
    }else if(str == "$sp"){
        return 29;
    }else if(str == "$fp"){
        return 30;
    }else if(str == "$ra"){
        return 31;
    }else{
        throw logic_error("Falta un caso en storeg, verifique que anoto bien los registros en el archivo de entrada.");
    }
}

/* Funcion que transforma los labels de las instrucciones a posiciones que representan donde se debe saltar el codigo
 * Entrada: Vector<Instruccion*> &instrucciones 
 * Salida: Void*/
void transformarLabels(vector<Instruccion*> &instrucciones){
    //Se crea un unordered_map, el cual utiliza dos llaves
    unordered_map<string, size_t> labels;
    //Se crea lista enlazada que almacenara los labels eliminados
    forward_list<Label*> labelsElim;
    size_t posicion = 0;
    //Se recorren las instrucciones
    for(auto i: instrucciones){
	//Se crea un dynamic_cast para saber si corresponde a un label
        Label *lbl = dynamic_cast<Label*>(i);
	//Si corresponde a un label
        if(lbl){
	    //Se inserta el label junto con la posicion al mapa
            labels.insert(make_pair(lbl->getLabel(), posicion));
	    //Se inserta el label a los labels a eliminar
            labelsElim.push_front(lbl);
        }
        posicion++;
    }
    //Se recorren los labes eliminados
    for(auto l: labelsElim){
	//Se busca el label entre las instrucciones
        auto it = find(instrucciones.begin(), instrucciones.end(), l);
        //Si esta dentro de las instrucciones
	if(it != instrucciones.end()){
	    //Se elimina
            delete *it;
            instrucciones.erase(it);       
        }
    }
    //Se recorren las instrucciones
    for(auto it = instrucciones.begin(); it != instrucciones.end(); it++){
        //Se pregunta si hay una instruccion falsa, es decir un j o un beq aun sin modificarse
	InstruccionFalsa *inst = dynamic_cast<InstruccionFalsa*>(*it);
        //Si se encuentra
	if(inst){
            //Se obtiene el label
            auto found = labels.find(inst->getLabel());
            //Si se encuentra
	    if(found != labels.end()){
		//Se crea una nueva instruccion real, o sea un j o un beq modificado
                Instruccion *nueva = inst->getReal((*found).second);
                *it = nueva;
            //Si no se encuentra, se notifica
	    }else{
                stringstream ss;
                ss << "Label " << inst->getLabel() << " no encontrada";
                throw logic_error(ss.str());
            }
        }
    }
}
