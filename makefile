INC_DIR = PrologInterpreter
Target = hw8
INC_DIR_Shell = PrologShell
TargetShell= shell

all: copyFirst compiler compilerShell

copyFirst:
ifeq (${OS}, Windows_NT)
	copy *.h ${INC_DIR} || : /y
else
	cp *.h ${INC_DIR} || :
endif

compiler:
	g++ -std=gnu++0x -c ${INC_DIR}/*.cpp
ifeq (${OS}, Windows_NT)
	g++ -o $(Target) *.o -lgtest
else
	g++ -o $(Target) *.o -lgtest -lpthread
endif

compilerShell:
	g++ -std=gnu++0x -c ${INC_DIR_Shell}/Shell.cpp
ifeq (${OS}, Windows_NT)
	del Source.o
	g++ -o $(TargetShell) *.o -lgtest
else
	rm -f Source.o
	g++ -o $(TargetShell) *.o -lgtest -lpthread
endif

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(Target) $(TargetShell)
endif