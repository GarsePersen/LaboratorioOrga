#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
using namespace std;

#include "Instruccion.hpp"
#include "LineaControl.hpp"
#include "Estado.hpp"
#include "TipoInmediato.hpp"
#include "parser/sintactico.tab.h"
#include "Archivo.hpp"

extern void parse(const string &file);
extern vector<Instruccion*> getInstrucciones();
void transformarLabels(vector<Instruccion*> &instrucciones);
int myMain();

int main(int argc, char **argv){
    try{
        return myMain();
    }catch(logic_error error){
        cerr << error.what() << endl;
    }catch(...){
        cerr << "Error" << endl;
    }
}

/* Funcion que compara las lineas de control de los archivos de entrada
 * Entrada: String nombreArchivoEntrada, String nombreArchivoSalida
 * Salida: Int
 * */

int myMain(){
    Archivo archivo;
    Estado estado;
    string nombreArchivoEntradaMips;
    string nombreArchivoSalida;
    string nombreArchivoEntradaLineas;
    //Se piden los archivos de entrada y salida al usuario
    cout << "Ingrese el nombre del archivo con las instrucciones mips: ";
    cin >> nombreArchivoEntradaMips;
    cout << "Ingrese el nombre del archivo con las lineas de control: ";
    cin >> nombreArchivoEntradaLineas;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> nombreArchivoSalida; 
    //Se llama a funcion que parsea el archivo de entrada
    ifstream myFile (nombreArchivoEntradaMips);
    if(myFile.good()){
        parse(nombreArchivoEntradaMips);
    }else{
        cout << "El archivo de entrada de las instrucciones mips no existe.\n";
    	return -1;
    }
    //Se crea vector que contiene las instrucciones del programa
    vector<Instruccion*> programa = getInstrucciones();
    //Se crea vector con las lineas de control de la entrada
    vector<int> lineaControlEntrada;
    try{
	lineaControlEntrada = archivo.archivoEntrada(nombreArchivoEntradaLineas);
    }catch(logic_error e){
        cerr << "Error: " << e.what() << endl;
	return -1;
    }
    //Se crea vector que contendra las lineas de control de la salida
    vector<string> lineaControlSalida;
    //Se transforman los labels del archivo de entrada
    transformarLabels(programa); 
    LineaControl lineaControl;
    //Se hace un try-catch para realizar un ciclo mientras el programa no termine y que no salte la excepcion
    try{
        bool end_program = false;
        while(!end_program){
            //Variable que guarda el estado de la linea
	    string estadoLinea = "Correcto";
            //Se obtiene el valor del programCounter
	    int programCounterActual = estado.programCounter();
	    //Se verifica que linea es la que se tiene que ejecutar
	    auto i = programa.at(estado.programCounter());
	    //Se ejecuta la linea
            i->run(estado, lineaControl);
            //Se crean variables que ayudan a comparar las lineas de control
	    int iAux = 0;
	    int linea = 0;
	    //Se recorren las lineas de control de la entrada
	    for(size_t i = 0; i < lineaControlEntrada.size(); i++){
		    //Se vericia si se debe pasar a otra linea
		    if((i%10 == 0) && (i != 0)){
			    iAux = 0;
			    linea = linea + 1;
		    }
		    //Se verifica que la linea y el programCounter sean iguales, ademas de que iAux no sea seis, lo que
		    //corresponde al segundo numero del ALUOp 
		    if((linea == programCounterActual) && (iAux!=6)){
			    //Se verifica si es el primer numero del ALUOp
			    if((i%5 == 0) && (i != 0) && (i%10 != 0)){
				//Se verifica si las lineas de control del ALUOp son iguales
                                if((lineaControl.linea[iAux] == lineaControlEntrada[i]) and (lineaControl.linea[iAux+1] == lineaControlEntrada[i+1])){
                                    lineaControlSalida.push_back("-");
				}else{
				    estadoLinea = "Error  ";
				    lineaControlSalida.push_back("A");
				    lineaControlSalida.push_back(to_string(lineaControlEntrada[i]));
				    lineaControlSalida.push_back(to_string(lineaControlEntrada[i+1]));
				}
		            //Si no es el ALUOp
			    }else{
			        if(lineaControl.linea[iAux] == -1){
                                    lineaControlSalida.push_back("-");
			        }else if(lineaControlEntrada[i] == lineaControl.linea[iAux]){
                                    lineaControlSalida.push_back("-");
			        }else{
			            estadoLinea = "Error  ";
				    lineaControlSalida.push_back(to_string(lineaControlEntrada[i]));
			        }
			    }
		    }
		    iAux++;
	    }
	    //Se agrega el estado de la linea y un separador que ayuda a escribir en el archivo despues
	    lineaControlSalida.push_back(estadoLinea);
	    lineaControlSalida.push_back("|");
	}
    //Catch del error, significa que termino el programa
    }catch(logic_error e){
        cout << "El programa ha finalizado exitosamente" << endl;
    }
    //Se escribe archivo de salida
    archivo.archivoSalida(lineaControlSalida, nombreArchivoSalida);
    return 0;

}



