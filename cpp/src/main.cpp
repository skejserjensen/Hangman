#include <iostream>
#include <string>

#include "hangman.hpp"

int main(int argc, char* argv[]) 
{
    //Placement of the default word list
    std::string wordlist = "../data/wordlist";
    Hangman *hm; 
   
    //Uses the word given as a command line argument
    if(argc == 2)
        wordlist = argv[1];

    //Start the game
    hm = new Hangman(wordlist);
    hm->newGame();
        
    //Deletion of hangman object 
    delete hm;
    
    return 0;
}
