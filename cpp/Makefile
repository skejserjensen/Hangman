#Settings
.SILENT:

#Variables
CXX= g++
CFLAGS= -O3 -Wall 
OBJ= hangman.o wordlist.o

#Target
all: $(OBJ)
	$(CXX) src/main.cpp $(OBJ) -o hangman 

#Dependencies
hangman.o: wordlist.o
	$(CXX) -c src/hangman.hpp src/hangman.cpp

wordlist.o:
	$(CXX) -c src/wordlist.hpp src/wordlist.cpp

#Clean
clean:
	cd src/; rm -f *.gch
	rm -f hangman.o wordlist.o hangman
