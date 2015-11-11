CC = gcc
CFLAGS = -Wall -Wno-unused-function -Werror -O3 -o
OBJ = wordlist.o hangman.o

all: $(OBJ)
	@$(CC) src/main.c $(OBJ) $(CFLAGS) hangman

%.o: src/%.c src/%.h
	@$(CC) $< -c $(CFLAGS) $@

run:
	@./hangman

clean:
	@cd src/; rm -f *.gch
	@rm -f *.o hangman
