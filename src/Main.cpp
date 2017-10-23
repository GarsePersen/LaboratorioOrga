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
    //Archivo archivo;
    Estado estado;
    string nombreArchivoEntradaMips;
    string nombreArchivoSalida;
    string nombreArchivoEntradaLineas;
    //Se piden los archivos de entrada y salida al usuario
    cout << "Ingrese el nombre del archivo con las instrucciones mips: ";
    cin >> nombreArchivoEntradaMips;
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
    //Se transforman los labels del archivo de entrada
    transformarLabels(programa); 
    LineaControl lineaControl;
    //Se hace un try-catch para realizar un ciclo mientras el programa no termine y que no salte la excepcion
    try{
        bool end_program = false;
        while(!end_program){
            cout << estado.toString() << endl;
            //Variable que guarda el estado de la linea
            string estadoLinea = "Correcto";
            //Se obtiene el valor del programCounter
            int programCounterActual = estado.programCounter();
            //Se verifica que linea es la que se tiene que ejecutar
            auto i = programa.at(estado.programCounter());
            //Se ejecuta la linea
            i->run(estado, lineaControl);
        }
        //Catch del error, significa que termino el programa
    }catch(logic_error e){
        int aux = 0;
        while(aux < 4){
            estado.pipeline("",-1,-2,-3,-4, lineaControl);
            cout << estado.toString() << endl;
	    aux = aux+1;
        }
        cout << "El programa ha finalizado exitosamente" << endl;
    }
    //Se escribe archivo de salida
    //archivo.archivoSalida(lineaControlSalida, nombreArchivoSalida);
    return 0;

}



