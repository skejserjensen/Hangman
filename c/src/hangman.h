#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "wordlist.h"

/** Public functions **/
int startGame();

/** Private methods **/
int static playGame(char* randomWord, unsigned int tries);
char static getCharFromUser();
int static isCharInWord(char guess, char *randomWord, char *wordInUnderscores, unsigned int wordLength);
void static addGuessedChars(char guess, char* guessedChars);
void static printStatus(unsigned int guesses, char *currentGuess, char *guessedChars);

#endif /* end of include guard: HANGMAN_H */
