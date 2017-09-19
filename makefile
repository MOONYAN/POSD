INC_DIR = HelloShape

all: hw1

hw1: Source.o Sort.o Shapes.o Media.o

ifeq (${OS}, Windows_NT)
	g++ -o hw1 Source.o Sort.o Shapes.o Media.o -lgtest
else
	g++ -o hw1 Source.o Sort.o Shapes.o Media.o -lgtest -lpthread
endif

Source.o: $(INC_DIR)/Source.cpp $(INC_DIR)/utSort.h
	g++ -std=gnu++0x -c $(INC_DIR)/Source.cpp
Sort.o: $(INC_DIR)/Sort.cpp $(INC_DIR)/Sort.h
	g++ -std=gnu++0x -c $(INC_DIR)/Sort.cpp
Shapes.o: $(INC_DIR)/Shapes.cpp $(INC_DIR)/Shapes.h
	g++ -std=gnu++0x -c $(INC_DIR)/Shapes.cpp
Media.o: $(INC_DIR)/Media.cpp $(INC_DIR)/Media.h
	g++ -std=gnu++0x -c $(INC_DIR)/Media.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif