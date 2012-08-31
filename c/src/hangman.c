#include "hangman.h"

/** Public functions **/
int startGame()
{
    //Creates a filepointer to the wordlist an checks if it can be opened
    openWordList("../data/wordlist"); 

    //Gets a random word from the wordlist
    char* randomWord = getRandomWord();

    //Starts the game and prints a message based on the result
    if(playGame(randomWord, 10) == 0)
        printf("Congratulations, you guessed the word correctly.\n");
    else
        printf("You did not guess \"%s\" correctly, and have been hanged.\n", randomWord);


    //Closes pointers and deletes used memory
    closeWordList();
    free(randomWord);

    return 0;
}

/** Private methods **/
int playGame(char* randomWord, unsigned int tries)
{
    unsigned int counter;
    unsigned int stringLength = strlen(randomWord);

    //An array for all the characters that have been guessed
    char *guessedChars = calloc(25, sizeof(char)); 

    //Make a new string of underscores to hold the half guessed word
    char wordInUnderscores[stringLength];

    for(counter = 0; counter < stringLength; counter++)
        wordInUnderscores[counter] = '_';

    //Sets the last index of the new string to the null terminator
    wordInUnderscores[counter] = '\0';

    //Prints the status in the beginning of the game, where the counter is 0
    printStatus(0, wordInUnderscores, guessedChars);

    //Asks the user for guesses and checks if the letters are in the string
    char guess;
    for(counter = 0; counter <= tries; counter++)
    {
        //Ensures that all guesses are starting as lower case letters
        guess = tolower( getCharFromUser() );
        
        isCharInWord(guess, randomWord, wordInUnderscores, stringLength);
        addGuessedChars(guess, guessedChars);

        if(strncmp(randomWord, wordInUnderscores, stringLength) == 0)
        {
            free(guessedChars);
            return 0;
        }

        printStatus(counter, wordInUnderscores, guessedChars);
    }

    free(guessedChars);
    return 1;
}

char static getCharFromUser()
{
    printf("Please enter your next guess: ");
    char guess = getchar();

    //Flushes the input buffer, so left over chars are not read on repeated calls
    while(getchar() != '\n');
    return guess;
}

int static isCharInWord(char guess, char* randomWord, char* wordInUnderscores, unsigned int wordLength)
{
    unsigned int counter;
    unsigned int wasInWord = 0;

    for(counter = 0; counter < wordLength; counter++)
    {
        //Guess is written as lower case to the user as most letters in the word is lowercase but checks both
        if((randomWord[counter] == guess) || (randomWord[counter] == toupper(guess)))
        {
            wasInWord = 1;
            wordInUnderscores[counter] = guess;
        }
    }

    return wasInWord;
}

void static addGuessedChars(char guess, char* guessedChars)
{
    static unsigned guessedCharsLength = 25;
    static unsigned guessedCharsUsed = 0;

    //Realloc guessedChars if it has been filled; 
    if(guessedCharsUsed > (guessedCharsLength-3))
    {
        guessedCharsLength *= 1.5;
        guessedChars = realloc(guessedChars, (guessedCharsLength * sizeof(char)));
    }
    printf("Guessed: %s\n\n", guessedChars);

    //Save the given guess and adds a space so it will be printed nicely
    guessedChars[guessedCharsUsed] = guess;
    guessedChars[guessedCharsUsed+1] = ' ';
    guessedChars[guessedCharsUsed+2] = '\0';
    guessedCharsUsed += 2;
}

void static printStatus(unsigned int guesses, char* currentGuess, char* guessedChars)
{
    printf("Word: %s\n", currentGuess);
    printf("Guessed: %s\n\n", guessedChars);

    printf("The Gallow\n\n");

    switch(guesses) {
        case 0:
            printf("\n\n\n\n\n\n\n");
            break;
        case 1:
            printf("\n\n\n\n\n\n");
            printf("_______________\n\n");
            break;
        case 2:
            printf("\n\n\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 3:
            printf("  |\n  |\n  |\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 4:
            printf("  |--         \n");
            printf("  |\n  |\n  |\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 5:
            printf("  |------         \n");
            printf("  |\n  |\n  |\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 6:
            printf("  |------         \n");
            printf("  |     |\n  |\n  |\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 7:
            printf("  |------         \n");
            printf("  |     |\n  |     0\n  |\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 8:
            printf("  |------         \n");
            printf("  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 9:
            printf("  |------         \n");
            printf("  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n");
            printf("________________\n\n");
            break;
        case 10:
            printf("  |------         \n");
            printf("  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n");
            printf("________________\n\n");
            break;
    }
}

