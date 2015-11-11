COBJC = clang
OBJCFLAGS = -Wall -fobjc-arc -Werror -O3 -o
OBJ = wordlist.o hangman.o nsstringadditions.o

all: $(OBJ)
	@$(COBJC) src/main.m $(OBJ) $(OBJCFLAGS) hangman

%.o: src/%.m src/%.h
	@$(COBJC) $< -c $(OBJCFLAGS) $@

run:
	@./hangman

clean:
	@rm -f *.o *.d hangman
