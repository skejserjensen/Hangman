CC= gcc
CFLAGS= -O3 -Wall -Wno-unused-function -c -o
OBJ= wordlist.o hangman.o

all: $(OBJ)
	@$(CC) src/main.c $(OBJ) -O3 -Wall -Wno-unused-function -g -o hangman 

%.o : src/%.c src/%.h
	@$(CC) $< $(CFLAGS) $@

run:
	@./hangman

clean:
	@cd src/; rm -f *.gch
	@rm -f *.o hangman
