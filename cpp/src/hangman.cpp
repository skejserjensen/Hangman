#include "hangman.hpp"

/** Using namespaces **/
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::stringstream;

/** Public methods **/
bool Hangman::startGame()
{
    bool result = playGame(10);

    if(result) 
    {
        cout << "Congratulations, you guessed the word \"" << _currentWord << "\" correctly." <<  endl;
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
    _wordList = new WordList(listPath);
}

/** Destructor **/
Hangman::~Hangman()
{
    delete _wordList;
}

/** Private methods **/
bool Hangman::playGame(int triesLeft) 
{
    //Gets a new word from the word list and convert it to underscores
    _currentWord = _wordList->getRandomWord();
    _currentGuess = string(_currentWord.length(), '_');
    printStatus(triesLeft);

    //Asks for at new guess as long as the word has not being guessed or the user have tried enough times
    while (triesLeft > 0) 
    {
       char guess = getGuess();

       if(!isCharInWord(guess))
           triesLeft--;

       printStatus(triesLeft);
  
       if(_currentWord == _currentGuess)
           return true;
    }
    return false;
}

char Hangman::getGuess() 
{
    string input;
    
    do
    {
        cout << "Enter your next guess: " << flush;
        getline(cin, input);
    }
    while (!isalpha(input[0]));

    //Just a couple of newlines for better formating of the output
    cout << endl << endl;
    return input[0];
}

bool Hangman::isCharInWord(char guess)
{
    bool answer = false;
    char input = tolower(guess);
    unsigned int index, stringLength;
        
    //Checks if the given chars has already been already guessed 
    if(!string::npos == _guessedChars.str().find(guess))
        return true;

    //We need the length of the word so we can map correct guesses from the real word to the underscored version
    stringLength = _currentWord.length();

    //Checks if the word contains instances of the guessed guess, uses a counted loop as index is needed
    for(index =0; index < stringLength; index++)
    {
        //The guess is already converted to its lower case, so we more easily can check if it have been used
        if(_currentWord.at(index) == input || _currentWord.at(index) == toupper(input))
        {
            answer = true;
            _currentGuess.at(index) = _currentWord.at(index);
        }
    }

    //Adds the guessed character to the guessed characters string
    _guessedChars << input << " ";

    return answer;
}

void Hangman::printStatus(unsigned int triesLeft)
{
    cout << "Word: " << _currentGuess << endl;
    cout << "Tries Left: " << triesLeft << endl;
    cout << "Guessed Letters: " << _guessedChars.str() << endl << endl;

    cout << "The Gallow" << endl << endl;

    //Prints a man getting hanged depending on how many faults the player have
    switch(triesLeft) {
        case 10:
            cout << "\n\n\n\n\n\n   " << endl;
            break;
        case 9:
            cout << "\n\n\n\n\n   \n_______________\n" << endl;
            break;
        case 8:
            cout << "\n\n\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 7:
            cout << "  |\n  |\n  |\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 6:
            cout << "  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n"  << endl;
            break;
        case 5:
            cout << "  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 4:
            cout << "  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 3:
            cout << "  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 2:
            cout << "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n" << endl;
            break;
        case 1:
            cout << "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n" << endl;
            break;
        case 0:
            cout << "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n" << endl;
            break;
    }
}
