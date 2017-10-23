%{
    #include "sintactico.tab.h"
    #include <string>
    #include <cstdio>
    #include <iostream>
    #include <vector>
    #include "lexico.h"
    #include "TipoInmediato.hpp"
    #include "Instruccion.hpp"
    #include "Label.hpp"
    #include "JFalso.hpp"
    #include "BeqFalso.hpp"
    #include "TipoR.hpp"
    #include "SwLw.hpp"
    using namespace std;
    void yyerror(char *s);
    extern int yylineno;
    vector<string> readed;
    vector<Instruccion*> instrucciones;
    void crearTipoInmediato();
    void crearLabel();
    void crearJ();
    void crearBeq();
    void crearTipoR();
    void crearSwLw();
    vector<Instruccion*> getInstrucciones();
     
%}



%token IDENTIFICADOR
%token NUMERO
%token REGISTRO
%token LABEL
%%

mips: linea mips 
    |
    ;

linea: IDENTIFICADOR REGISTRO ',' REGISTRO ',' NUMERO { crearTipoInmediato(); }
    | LABEL { crearLabel(); } 
    | IDENTIFICADOR IDENTIFICADOR { crearJ(); }
    | IDENTIFICADOR REGISTRO ',' REGISTRO ',' IDENTIFICADOR { crearBeq(); }
    | IDENTIFICADOR REGISTRO ',' REGISTRO ',' REGISTRO {crearTipoR(); }
    | IDENTIFICADOR REGISTRO ',' NUMERO '(' REGISTRO ')' { crearSwLw(); }
    ;


%%


void parse(const string &file){
    extern FILE *yyin;
    yyin=fopen(file.c_str(), "r");
    yyparse();
    fclose(yyin);
}


void yyerror(char *s) {
	printf("%s%i%s","Error sintactico en la linea: ", yylineno,".");
	exit(1);
}


void crearBeq(){
    Instruccion *inst = new BeqFalso(readed.at(3), readed.at(1), readed.at(2));
    instrucciones.push_back(inst);
    readed.clear();
}

void crearTipoInmediato(){
    Instruccion *inst = new TipoInmediato(readed.at(0), readed.at(1), readed.at(2), readed.at(3));
    instrucciones.push_back(inst);
    readed.clear();
}

void crearTipoR(){
    Instruccion *inst = new TipoR(readed.at(0), readed.at(1), readed.at(2), readed.at(3));
    instrucciones.push_back(inst);
    readed.clear();
}

void crearLabel(){
    string::iterator end = readed.at(0).end();
    end--;
    readed.at(0).erase(end);
    Instruccion *inst = new Label(readed.at(0));
    instrucciones.push_back(inst);
    readed.clear();
}

void crearJ(){
    Instruccion *inst = new JFalso(readed.at(1));
    instrucciones.push_back(inst);
    readed.clear();
}

void crearSwLw(){
    Instruccion *inst = new SwLw(readed.at(0), readed.at(1), readed.at(2), readed.at(3));
    instrucciones.push_back(inst);
    readed.clear();
}

vector<Instruccion*> getInstrucciones(){
    return instrucciones;
}
