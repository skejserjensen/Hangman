#include "wordlist.hpp"

//---------------------------------------------------------------------------
// Reads a random word from the word list and returns it to the caller
//---------------------------------------------------------------------------
string WordList::getRandomWord() {
    //Ensures that we do no read past the end of the file
    unsigned int counter;
    unsigned int randomNumber = rand() % _length;

    string randomWord;

    //Resets the file by clearing the flags, and resets the buffer
    _file.clear();
    _file.seekg(0, ios::beg);

    //Reads through the word list until randomNumber is reached
    for(counter=0; counter < randomNumber; counter++)
        getline(_file, randomWord);

    //Reads the actual word we want
    getline(_file, randomWord);

    return randomWord; 
}

//---------------------------------------------------------------------------
// Opens the word list and counts the number of lines it contains
//---------------------------------------------------------------------------
bool WordList::openFile(string listPath) { 
    //Opens the file which named is saved in listPath
    _file.open(listPath.c_str());

    //Stops the program if the file could no be opened
    if(_file.fail())
        return false;

    //String the holds the string received from getline, no used 
    string shouldNotBeUsed;

    //Counts the number of lines contained in the word list
    unsigned int counter = 0;
    while(getline(_file, shouldNotBeUsed))
        counter++;

    _length = counter;

    return true;
}

//---------------------------------------------------------------------------
// Seeds the random number generator and open the word list
//---------------------------------------------------------------------------
WordList::WordList(string listPath) {
    //Seeds the random number generator for random word fetching
    srand((unsigned)time(0));

    //Terminates the program if the word list cannot be opend
    if(!openFile(listPath)) {
        cout << "ERROR: wordlist mssing, terminating" << endl;
        exit;
    }
}

//---------------------------------------------------------------------------
// Closes the file stream 
//---------------------------------------------------------------------------
WordList::~WordList() {
    _file.close();
}
