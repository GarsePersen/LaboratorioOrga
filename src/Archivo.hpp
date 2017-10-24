#ifndef _H_ARCHIVO_
#define _H_ARCHIVO_

#include <string>
#include <vector>
using namespace std;

/* Clase Archivo, se encarga de leer y escribir los archivos necesarios */
class Archivo{
    public:
    vector<string> archivoEntrada(string nombre);
	void escribirArchivoSalidaPipeline(string salida, string nombreArchivoSalida);
	void escribirArchivoSalidaHazard(string salida, string nombreArchivoSalidaHazard);
};

#endif
