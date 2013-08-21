CXX= g++
CPPFLAGS= -O3 -std=c++11 -Wall -c -o
OBJ= hangman.o wordlist.o

all: $(OBJ)
	@$(CXX) src/main.cpp $(OBJ) -O3 -Wall -o hangman 

%.o: src/%.cpp src/%.hpp
	@$(CXX) $< $(CPPFLAGS) $@

run:
	@./hangman

clean:
	@cd src/; rm -f *.gch
	@rm -f *.o hangman
