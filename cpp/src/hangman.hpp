#ifndef HANGMAN_H 
#define HANGMAN_H 

#include <string>
#include <sstream>

#include "wordlist.hpp"

class Hangman {

    public:
        bool startGame(int tries);

        Hangman(std::string listPath);
        ~Hangman();

    private:
        bool playGame(int triesLeft);
        char getGuess();
        bool isCharInWord(char letter);
        void printStatus(unsigned int triesLeft); 

        std::string _currentWord;
        std::string _currentGuess;
        std::stringstream _guessedChars;

        WordList *_wordList;
};

#endif
