#include <iostream>
#include <string>
#include <vector>

#include "hangman.hpp"

int main(int argc, char* argv[]) 
{
    //Placement of the default word list
    std::string wordlist = "../data/wordlist";
   
    //Uses the word given as a command line argument
    if(argc == 2)
        wordlist = argv[1];

    //Starts the game with the given wordlist
    Hangman hangman(wordlist);
    hangman.startGame();
        
    return 0;
}
