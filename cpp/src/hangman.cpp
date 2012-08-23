#include "hangman.hpp"

/** Using namespaces **/
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

/** Public methods **/
bool Hangman::newGame() 
{
    bool result = playGame();

    if(result) 
    {
        cout << "Congratulations, you guessed the word correctly." <<  endl;
        return true;
    }
    else 
    {
        cout << "You did not guess \"" << _currentWord << "\" correctly, and have been hanged." << endl;
        return false;
    }
}

/** Constructor **/
Hangman::Hangman(string listPath)
{
    _maxTries = 10;
    _wordList = new WordList(listPath);
}

/** Destructor **/
Hangman::~Hangman()
{
    delete _wordList;
}

/** Private methods **/
bool Hangman::playGame() 
{
    int tries = 0;
    char guess;

    //Gets a new word from the word list and convert it to underscores
    _currentWord = _wordList->getRandomWord();
    stringToUnderscores();
    printStatus(tries);

    //Asks for at new guess as long as the word has not being guessed or the user have tried enough times 
    while (tries < _maxTries) 
    {
       guess = getChar(); 

       if(!isCharInWord(guess))
           tries++;

       printStatus(tries);
  
       if(_currentWord == _currentQuess)
           break;
    }

    //Return true if the word was guessed without using all the given guesses
    if(tries < _maxTries)
        return true;
    else
        return false;
}

void Hangman::stringToUnderscores()
{
    int i;
    int stringLength = _currentWord.length();
    stringstream buffer;

    for(i=0; i < stringLength; i++)
        buffer << '_';

    _currentQuess = buffer.str();
}

char Hangman::getChar() {
    string input;

    cout << "Enter your next guess: ";
    cin >> input;

    return input[0];
}

bool Hangman::isCharInWord(char letter)
{
    bool answer = false;
    int i, guessedlength;
    char input = tolower(letter);
    unsigned int stringLength = _currentWord.length();

    //Converts the string stream of guessed chars to a string to get its length
    string guessed = _guessedChars.str();
    guessedlength = guessed.length();

    //Checks if the given chars has already been already guessed 
    for(i=0; i < guessedlength; i++)
    {
        if(guessed.at(i) == input)
            return true;
    }

    //Checks if the word contains instances of the guessed letter
    for(i=0; i < stringLength; i++)
    {
        if(_currentWord.at(i) == input || _currentWord.at(i) == toupper(input))
        {
            answer = true;
            _currentQuess.at(i) = _currentWord.at(i);
        }
    }

    //Adds the guessed character to the guessed characters string
    _guessedChars << input << " ";

    return answer;
}

void Hangman::printStatus(unsigned int tries)
{
    cout << "Word: " << _currentQuess << endl;
    cout << "Guessed: " << _guessedChars.str() << endl << endl;

    cout << "The Gallow" << endl << endl;

    switch(tries) {
        case 0:
            cout << "\n\n\n\n\n\n   " << endl;
            break;
        case 1:
            cout << "\n\n\n\n\n   " << endl;
            cout << "_______________\n" << endl;
            break;
        case 2:
            cout << "\n\n\n  |\n  |\n  |" << endl;
            cout << "________________\n" << endl;
            break;
        case 3:
            cout << "  |\n  |\n  |\n  |\n  |\n  |" << endl;
            cout << "________________\n" << endl;
            break;
        case 4:
            cout << "  |--         "  << endl;
            cout << "  |\n  |\n  |\n  |\n  |\n  |" << endl;
            cout << "________________\n" << endl;
            break;
        case 5:
            cout << "  |------         " << endl;
            cout << "  |\n  |\n  |\n  |\n  |\n  |" << endl;
            cout << "________________\n" << endl;
            break;
        case 6:
            cout << "  |------         " << endl;
            cout << "  |     |\n  |\n  |\n  |\n  |\n  |" << endl;    
            cout << "________________\n" << endl;
            break;
        case 7:
            cout << "  |------         " << endl;
            cout << "  |     |\n  |     0\n  |\n  |\n  |\n  |" << endl;    
            cout << "________________\n" << endl;
            break;
        case 8:
            cout << "  |------         " << endl;                    
            cout << "  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |" << endl;
            cout << "________________\n" << endl;                
            break;
        case 9:
            cout << "  |------         " << endl;                    
            cout << "  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |" << endl;
            cout << "________________\n" << endl;                
            break;
        case 10:
            cout << "  |------         " << endl;                    
            cout << "  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |" << endl;
            cout << "________________\n" << endl;                
            break;
    }
}
