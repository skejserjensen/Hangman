CPP = g++
CPPFLAGS = -std=c++11 -Wall -Werror -O3 -c -o
OBJ = hangman.o wordlist.o

all: $(OBJ)
	@$(CPP) src/main.cpp $(OBJ) -O3 -Wall -Werror -o hangman

%.o: src/%.cpp src/%.hpp
	@$(CPP) $< $(CPPFLAGS) $@

run:
	@./hangman

clean:
	@cd src/; rm -f *.gch
	@rm -f *.o hangman
