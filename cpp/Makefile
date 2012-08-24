#Variables
CXX= g++
CPPFLAGS= -O3 -std=c++11 -Wall -c -o
OBJ= hangman.o wordlist.o

#Target
all: $(OBJ)
	$(CXX) src/main.cpp $(OBJ) -O3 -Wall -o hangman 

#Dependencies
%.o: src/%.cpp src/%.hpp
	$(CXX) $< $(CPPFLAGS) $@

#Clean
clean:
	cd src/; rm -f *.gch
	rm -f *.o hangman
