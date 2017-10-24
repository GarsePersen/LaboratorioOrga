#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <cstring>
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
    string nombreArchivoSalidaHazard;
    string nombreArchivoEntradaRegistros;
    //Se piden los archivos de entrada y salida al usuario
    cout << "Ingrese el nombre del archivo con las instrucciones mips: ";
    cin >> nombreArchivoEntradaMips;
    cout << "Ingrese el nombre del archivo con los valores iniciales de los registros: ";
    cin >> nombreArchivoEntradaRegistros;
    cout << "Ingrese el nombre del archivo de salida de la traza: ";
    cin >> nombreArchivoSalida; 
    cout << "Ingrese el nombre del archivo de salida de hazard: ";
    cin >> nombreArchivoSalidaHazard; 
    //Se llama a funcion que parsea el archivo de entrada
    ifstream myFile (nombreArchivoEntradaMips);
    if(myFile.good()){
        parse(nombreArchivoEntradaMips);
    }else{
        cout << "El archivo de entrada de las instrucciones mips no existe.\n";
    	return -1;
    }
    
    vector<string> registrosIniciales = archivo.archivoEntrada(nombreArchivoEntradaRegistros);

    //Se establecen los valores de los registros iniciales
    int i = 0;
    for(auto it = registrosIniciales.begin(); it != registrosIniciales.end(); it++){
        cout << registrosIniciales[i] << endl;
        if(i%2 == 0){
            //estado.modificarRegistro(i/2, atoi(registrosIniciales[i+1].c_str())); 
        }
        i=i+1;
    }

    cout << estado.toString() << endl;
    //Se crea vector que contiene las instrucciones del programa
    vector<Instruccion*> programa = getInstrucciones();
    //Se transforman los labels del archivo de entrada
    transformarLabels(programa); 
    LineaControl lineaControl;
    estado.nombreArchivoSalida = nombreArchivoSalida;
    estado.nombreArchivoSalidaHazard = nombreArchivoSalidaHazard;
    archivo.escribirArchivoSalidaPipeline(",IF,ID,EX,MEM,WB\n", nombreArchivoSalida);
    archivo.escribirArchivoSalidaPipeline(",Control,Datos\n", nombreArchivoSalidaHazard);
    //Se hace un try-catch para realizar un ciclo mientras el programa no termine y que no salte la excepcion
    try{
        bool end_program = false;
        while(!end_program){
            //Se obtiene el valor del programCounter
            int programCounterActual = estado.programCounter();
            //Se verifica que linea es la que se tiene que ejecutar
            auto i = programa.at(estado.programCounter());
            //Se ejecuta la linea
            i->run(estado, lineaControl);
            //cout << estado.toString() << endl;
        }
        //Catch del error, significa que termino el programa
    }catch(logic_error e){
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
        while((estado.bufferWbOpCode != "")||(estado.obtenerCiclo()<6)){
	    
            estado.pipeline("",-1,-2,-3,-4, lineaControl);
            //cout << estado.toString() << endl;
        }
        cout << "El programa ha finalizado exitosamente" << endl;
    }
    //Se escribe archivo de salida
    //archivo.archivoSalida(lineaControlSalida, nombreArchivoSalida);
    return 0;

}



