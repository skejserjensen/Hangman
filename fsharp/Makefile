SCALA = scalac
SCALAFLAGS = -d bin

all: compile	

compile:
	@fsharpc src/WordList.fs src/Hangman.fs src/Main.fs --out:Hangman.exe

run:
	@mono Hangman.exe

clean:
	@rm -rf Hangman.exe
