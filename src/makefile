FLAGS=-Wall -g -std=c++11

all: BufferMem.o BufferEx.o BufferId.o BufferIf.o InstruccionFalsa.o BeqFalso.o BEQ.o JFalso.o J.o Label.o SwLw.o TipoR.o TipoInmediato.o LineaControl.o Estado.o Instruccion.o Archivo.o Main.cpp 
	make -C parser
	g++ $(FLAGS) BufferMem.o BufferEx.o BufferId.o BufferIf.o Main.cpp parser/lexer.o parser/parser.o Instruccion.o Archivo.o LineaControl.o Estado.o TipoInmediato.o SwLw.o TipoR.o Label.o BeqFalso.o JFalso.o BEQ.o J.o InstruccionFalsa.o -o lab1

Archivo.o: Archivo.cpp Archivo.hpp
	g++ $(FLAGS) -c Archivo.cpp -o Archivo.o

Instruccion.o: Instruccion.cpp Instruccion.hpp
	g++ $(FLAGS) -c Instruccion.cpp -o Instruccion.o
	
estado.o: estado.cpp estado.hpp
	g++ $(flags) -c estado.cpp -o estado.o

BufferMem.o: BufferMem.cpp BufferMem.hpp
	g++ $(flags) -c BufferMem.cpp -o BufferMem.o

BufferEx.o: BufferEx.cpp BufferEx.hpp
	g++ $(flags) -c BufferEx.cpp -o BufferEx.o

BufferIf.o: BufferIf.cpp BufferIf.hpp
	g++ $(flags) -c BufferIf.cpp -o BufferIf.o

BufferId.o: BufferId.cpp BufferId.hpp
	g++ $(flags) -c BufferId.cpp -o BufferId.o

LineaControl.o: LineaControl.cpp LineaControl.hpp
	g++ $(flags) -c LineaControl.cpp -o LineaControl.o

TipoInmediato.o: TipoInmediato.cpp TipoInmediato.hpp
	g++ $(FLAGS) -c TipoInmediato.cpp -o TipoInmediato.o

SwLw.o: SwLw.cpp SwLw.hpp
	g++ $(FLAGS) -c SwLw.cpp -o SwLw.o

TipoR.o: TipoR.cpp TipoR.hpp
	g++ $(FLAGS) -c TipoR.cpp -o TipoR.o

Label.o: Label.cpp Label.hpp
	g++ $(FLAGS) -c Label.cpp -o Label.o

BeqFalso.o: BeqFalso.cpp BeqFalso.hpp
	g++ $(FLAGS) -c BeqFalso.cpp -o BeqFalso.o

JFalso.o: JFalso.cpp JFalso.hpp
	g++ $(FLAGS) -c JFalso.cpp -o JFalso.o

InstruccionFalsa.o: InstruccionFalsa.cpp InstruccionFalsa.hpp
	g++ $(FLAGS) -c InstruccionFalsa.cpp -o InstruccionFalsa.o

BEQ.o: BEQ.cpp BEQ.hpp
	g++ $(FLAGS) -c BEQ.cpp -o BEQ.o

J.o: J.cpp J.hpp
	g++ $(FLAGS) -c J.cpp -o J.o

clear:
	rm *.o  
 
