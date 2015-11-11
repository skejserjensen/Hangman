COBJC = clang
FLAGS = -fobjc-arc -Wall -Werror -O3
OBJ = hangman.o wordlist.o nsstringadditions.o

all: $(OBJ)
	$(COBJC) src/main.m $(FLAGS) $(OBJ) -o hangman

%.o: src/%.m src/%.h
	$(COBJC) $(FLAGS) $< -c -o $@

run:
	./hangman

clean:
	@rm -f *.o *.d hangman
