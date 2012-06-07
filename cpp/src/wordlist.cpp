#include "wordlist.hpp"

WordList::WordList(string listPath)
{
    //Seeds the random number generator for random word fetching
    srand((unsigned)time(0));

    //TODO: Make error handling when wordlist is missing a bit more graceful
    if(!openFile(listPath))
    {
        cout << "ERROR: wordlist mssing, terminating" << endl;
        exit;
    }
}

WordList::~WordList()
{
}

//Methods
bool WordList::openFile(string listPath)
{
    //TODO: Exeption handling for when the file does not exist
    _file.open(listPath.c_str());

    if(_file.fail())
        return false;

    //TODO: Find another counting method that does not use save input
    string shouldNotBeUsed;

        unsigned int counter = 0;
        while(getline(_file, shouldNotBeUsed))
            counter++;

        _length = counter;

    return true;
}

string WordList::getRandomWord()
{
    unsigned int counter;
    unsigned int randomNumber = rand() % _length;

    string randomWord;

    //Resets the file by claring the flags, and resets the buffer
    _file.clear();
    _file.seekg(0, ios::beg);

    //TODO: Should be able to iterate thorugh file with reading
    for(counter=0; counter < randomNumber; counter++)
        getline(_file, randomWord);

    //Reads the actual word we want
        getline(_file, randomWord);

    return randomWord; 
}
