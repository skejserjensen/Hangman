#ifndef HANGMAN_H 
#define HANGMAN_H 

#include <string>
#include <sstream>

#include "wordlist.hpp"

//---------------------------------------------------------------------------
// Controls the actual game and uses the word list classes 
//---------------------------------------------------------------------------
class Hangman {

    public:
        /** Public methods **/
        bool newGame();

        /** Constructor **/
        Hangman(string listPath);

        /** Destructor **/
        ~Hangman();

    private:
        /** Private methods **/
        bool playGame();
        void stringToUnderscores();    
        char getChar();
        bool isCharInWord(char letter);
        void printStatus(unsigned int tries); 

        /** Instance variables **/
        unsigned short _maxTries; 
        string _currentWord;
        string _currentQuess;
        stringstream _guessedChars;

        WordList *_wordList;
};

#endif
