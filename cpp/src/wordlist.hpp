#ifndef WORDLIST_H 
#define WORDLIST_H 

#include <string>
#include <fstream>
#include <iostream>

#include <cstdlib>

//TODO: Should be a collection of using std:: statements
using namespace std;

//---------------------------------------------------------------------------
// File handler for the word list and methods to extract words from it
//---------------------------------------------------------------------------
class WordList {

    public:
        /** Public methods **/
        string getRandomWord();

        /** Constructor **/
        WordList(string listPath);

        /** Destructor **/
        ~WordList();

    private:
        /** Private methods **/
        bool openFile(string listPath);

        /** Instance variables **/
        ifstream _file;
        unsigned int _length;
};
#endif
