#include <stdio.h>

#include "hangman.h"

int main(int argc, const char *argv[])
{
    //Starts a game of hangman for everyone to enjoy 
    int tries = 10;
    if(argc == 2)
        startGame(argv[1], tries);
    else
        startGame("../data/wordlist", tries);

    return 0;
}
