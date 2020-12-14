CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14
JSON = json.hpp

.PHONY: all
all: BSTSanityCheck CreateData AVLCommands

CreateData: CreateData.cxx json.hpp
	$(CC) $(OPT) CreateData.cxx -o CreateData.exe

BSTSanityCheck: BSTSanityCheck.cxx BST.o
	$(CC) $(DEV) BSTSanityCheck.cxx BST.o -o BSTSanityCheck.exe

BST.o: BST.cpp BST.h $(JSON)
	$(CC) $(DEV) -c BST.cpp

AVL.o: AVL.cpp AVL.h $(JSON)
	$(CC) $(DEV) -c AVL.cpp

AVLCommands: AVLCommands.cxx BST.o AVL.o $(JSON)
	$(CC) $(DEV) AVLCommands.cxx BST.o AVL.o -o AVLCommands.exe

# Build
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -rf *dSYM

.PHONY: update
update:
	make clean
	make all
