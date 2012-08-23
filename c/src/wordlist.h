#ifndef WORDLIST_H
#define WORDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Public functions **/
int openWordList(const char *listPath);
char* getRandomWord();
int closeWordList();

/** Private functions **/
void static countLinesInWordList(unsigned int *longestLine, unsigned int *countedLines);

#endif /* end of include guard: WORDLIST_H */
