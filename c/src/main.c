#include <stdio.h>

#include "hangman.h"

int main(int argc, const char *argv[])
{
    //Starts a game of hangman for everyone to enjoy
    if(argc == 2)
        startGame(argv[1]);
    else
        startGame("../data/wordlist");

    return 0;
}
