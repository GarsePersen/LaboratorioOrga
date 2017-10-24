#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Archivo.hpp"
using namespace std;

void Archivo::escribirArchivoSalidaHazard(string salida, string nombreArchivoSalidaHazard){
    ofstream myfile;
    myfile.open (nombreArchivoSalidaHazard+".csv", ios_base::app);
    myfile << salida;
    myfile.close();
}

void Archivo::escribirArchivoSalidaPipeline(string salida, string nombreArchivoSalida){
    ofstream myfile;
    myfile.open (nombreArchivoSalida+".csv", ios_base::app);
    myfile << salida;
    myfile.close();
}


/* Funcion que escribe en el archivo de salida
 * Entrada: Vector<string> lineaControlSalida, string nombre
 * Salida: Void
 * */
void Archivo::archivoSalida(vector<string> lineaControlSalida, string nombre){
    ofstream archivo (nombre);
    if(archivo.is_open()){
        archivo << "   RegDest  Jump  Branch  MemRead  MemToReg ALUOp MemWrite ALUSrc RegWrite    Estado\n";
        for(size_t i = 0; i < lineaControlSalida.size(); i++){
            if(lineaControlSalida[i].compare("|") == 0){
	        archivo << "\n";
	    }else if(lineaControlSalida[i].compare("A") == 0){
		archivo << "      " << lineaControlSalida[i+1] << lineaControlSalida[i+2];
		i = i+2;
	    }else{
	        archivo << "      " << lineaControlSalida[i] << " ";
	    }
        }	    
    }else{
	cout << "No se pudo abrir archivo de salida";
    }
}

/* Funcion que obtiene un vector de enteros desde el archivo de entrada
 * Entrada: String nombre
 * Salida: vector<int>
 * */
vector<int> Archivo::archivoEntrada(string nombre){
    string linea;
    int aux = 0;
    string::iterator it;
    vector<int> lineaControl;
    ifstream myfile (nombre);
    if(!myfile.good()){
	throw logic_error("El archivo de entrada de las lineas de control no existe.\n");
	return lineaControl;
    }
    if (myfile.is_open()){
        while ( getline (myfile,linea) )
        {
            if(aux>0){
                for ( it = linea.begin() ; it < linea.end(); it++)
                {
                    if(*it != 32){
                        lineaControl.push_back(*it-48);
                    }
                }
            }
            aux++;
        }
        myfile.close();
    }else{
        throw logic_error("Error, el arhcivo de entrada no existe.");
    }
    return lineaControl;
}
