CPP = g++
CPPFLAGS = -Wall -Werror -O3 -o
OBJ = wordlist.o hangman.o

all: $(OBJ)
	@$(CPP) src/main.cpp $(OBJ) $(CPPFLAGS) hangman

%.o: src/%.cpp src/%.hpp
	@$(CPP) $< -c $(CPPFLAGS) $@

run:
	@./hangman

clean:
	@cd src/; rm -f *.gch
	@rm -f *.o hangman
