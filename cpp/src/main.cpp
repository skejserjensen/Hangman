#include <iostream>
#include <string>

#include "hangman.hpp"

//---------------------------------------------------------------------------
// Checks if any command line parameters have been given, starts the game
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    //Placement of the default word list
    string wordlist = "../data/wordlist";
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
