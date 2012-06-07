#ifndef WORDLIST_H 
#define WORDLIST_H 

#include <string>
#include <fstream>
#include <iostream>

#include <cstdlib>

//TODO: Use namespace insteaad of use
using namespace std;

class WordList 
{
public:
    //Constructor and destructor
    WordList(string listPath);
    ~WordList();

    //Methods
    string getRandomWord();

private:
    ifstream _file;
    unsigned int _length;

    //Methods
    bool openFile(string listPath);
};
#endif
