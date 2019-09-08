PROGRAMNEVE = id3tag
COMPILER = g++
OBJ = main.o CID3Tag.o CID3Ablak.o 

$(PROGRAMNEVE) : $(OBJ) CID3Tag.hpp
	$(COMPILER) -g -o $(PROGRAMNEVE) $(OBJ) -lncurses

main.o : main.cpp 
	$(COMPILER) -g -c main.cpp

CID3Tag.o : CID3Tag.cpp CID3Tag_mufaj.hpp
	$(COMPILER) -g -c CID3Tag.cpp

CID3Ablak.o : CID3Ablak.cpp
	$(COMPILER) -g -c CID3Ablak.cpp
