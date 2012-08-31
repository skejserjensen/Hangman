#include "wordlist.h"

/** Static variables **/
static FILE* wordList = NULL;

/** Public functions **/
int openWordList(const char *listPath)
{
    wordList = fopen(listPath, "r");

    if(!(wordList == NULL))
        return 0;
    else
        return 1;
}

char* getRandomWord()
{
    unsigned int longestLine = 0;
    unsigned int countedLines = 0;
    unsigned int randomLineNumber = 0;

    //Ensures that the random number generator is only seeded once
    unsigned static int init = 0;
    if(init == 0)
    {
        init = 1;
        srand(time(NULL));
    }

    //A buffer the size of the longest line plus one can contain all words
    //and the null terminator.
    countLinesInWordList(&longestLine, &countedLines);
    char* randomWord = calloc(longestLine, sizeof(char));

    //A random number which corresponds to a random word in the document
    randomLineNumber = (rand() % countedLines)+1;

    //Read the line corresponds to randomLineNumber and return a pointer to it
    unsigned int lineCounter = 0;
    while(fgets(randomWord, longestLine, wordList) != NULL)
    {
        if(lineCounter == randomLineNumber)
            break;

        lineCounter++;
    }

    //Removes the newline character
    randomWord[strlen(randomWord)-1] = '\0';

    return randomWord;
}

int closeWordList()
{
    if(wordList != NULL)
        return fclose(wordList);
    else
        return 1;
}

/** Private methods **/
void static countLinesInWordList(unsigned int *longestLine, unsigned int *countedLines)
{
    //Set to zero as we don't know what they contain and we need them for comparison.
    *countedLines = 0;
    *longestLine = 0;

    int ch = 0;
    unsigned int charsInLine = 0;

    while((ch = getc(wordList)) != EOF)
    {
        charsInLine++;

        if(ch == '\n')
        {
            //The length of the longest line in the wordlist is saved, as it will 
            //be the length of the buffer used for the word to be guessed.
            if(*longestLine < charsInLine)
                *longestLine = charsInLine;
         
            //The number of lines are counted as we need to now the boundaries of the 
            //document when we pick a random word to guess.
            (*countedLines)++;
            charsInLine = 0;
        }
    }

    //Resets the position of the file indicator to the beginning of the file, so it can be read again
    rewind(wordList);
}
