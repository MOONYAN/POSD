INC_DIR = PrologInterpreter
Target = hw7

all: copyFirst compiler

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

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(Target)
endif