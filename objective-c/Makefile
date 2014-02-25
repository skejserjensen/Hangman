COBJC= clang
LIBS= `gnustep-config --base-libs` -lbsd
FLAGS= `gnustep-config --objc-flags` -Werror -O3
OBJ= hangman.o wordlist.o nsstringadditions.o

all: $(OBJ)
	$(COBJC) src/main.m $(LIBS) $(FLAGS) $(OBJ) -o hangman

%.o: src/%.m src/%.h
	$(COBJC) $(FLAGS) $< -c -o $@

run:
	@LD_LIBRARY_PATH="/usr/share/GNUstep/lib" ./hangman

clean:
	@rm -f *.o *.d hangman
