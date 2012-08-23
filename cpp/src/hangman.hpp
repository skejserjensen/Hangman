#ifndef HANGMAN_H 
#define HANGMAN_H 

#include <string>
#include <sstream>

#include "wordlist.hpp"

class Hangman {

    public:
        bool newGame();

        Hangman(std::string listPath);
        ~Hangman();

    private:
        bool playGame();
        void stringToUnderscores();    
        char getChar();
        bool isCharInWord(char letter);
        void printStatus(unsigned int tries); 

        unsigned short _maxTries; 
        std::string _currentWord;
        std::string _currentQuess;
        std::stringstream _guessedChars;

        WordList *_wordList;
};

#endif
