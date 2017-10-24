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


/* Funcion que obtiene un vector de enteros desde el archivo de entrada
 * Entrada: String nombre
 * Salida: vector<int>
 * */
vector<string> Archivo::archivoEntrada(string nombre){
    string linea;
    string::iterator it;
    vector<string> registros;
    string valor;
    string registro;
    ifstream file(nombre);


    while (getline(file, linea, ' ')){
        registros.push_back(linea); 
    }
    
    
    return registros;
}
