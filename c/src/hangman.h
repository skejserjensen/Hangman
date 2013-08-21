#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "wordlist.h"

/** Public functions **/
int startGame(const char *wordList);

/** Private methods **/
int static playGame(char* randomWord, unsigned int triesLeft);
char static getCharFromUser();
int static isCharInWord(char guess, char *randomWord, char *wordInUnderscores, unsigned int wordLength);
int static addGuessedChars(char guess, char* guessedChars);
void static printStatus(unsigned int guessesLeft, char *currentGuess, char *guessedChars);

#endif /* end of include guard: HANGMAN_H */
