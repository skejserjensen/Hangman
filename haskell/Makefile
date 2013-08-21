all:
	@cabal configure
	@cabal build
	@cp dist/build/Hangman/Hangman ./hangman
	@rm -rf dist

run:
	@./hangman

clean:
	@rm -rf hangman
