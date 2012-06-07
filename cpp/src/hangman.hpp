#ifndef HANGMAN_H 
#define HANGMAN_H 

#include <string>
#include <sstream>

#include "wordlist.hpp"

class Hangman 
{
    public:
        Hangman(string listPath);
        ~Hangman();

        /** Public methods **/
        bool newGame();

    private:
        bool playGame();
        void stringToUnderscores();    
        char getChar();
        bool isCharInWord(char letter);
        void printStatus(unsigned int tries); 

        /** Instance variabels **/
        unsigned short _maxTries; 
        string _currentWord;
        string _currentQuess;
        stringstream _guessedChars;

        WordList *_wordList;
};

#endif
