#ifndef WORDLIST_H 
#define WORDLIST_H 

#include <string>
#include <fstream>
#include <iostream>

#include <cstdlib>

class WordList {

    public:
        std::string getRandomWord();

        WordList(std::string listPath);
        ~WordList();

    private:
        bool openFile(std::string listPath);

        std::ifstream _file;
        unsigned int _length;
};
#endif
