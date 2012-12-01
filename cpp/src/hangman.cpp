#include "hangman.hpp"

/** Using namespaces **/
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

/** Public methods **/
bool Hangman::startGame() 
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
    int triesLeft = 10;
    char guess;

    //Gets a new word from the word list and convert it to underscores
    _currentWord = _wordList->getRandomWord();
    stringToUnderscores();
    printStatus(triesLeft);

    //Asks for at new guess as long as the word has not being guessed or the user have tried enough times 
    while (triesLeft > 0) 
    {
       guess = getChar(); 

       if(!isCharInWord(guess))
           triesLeft--;

       printStatus(triesLeft);
  
       if(_currentWord == _currentQuess)
           break;
    }

    //Return true if the word was guessed without using all the given guesses
    if(triesLeft > 0)
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

    //Just a couple of newlines for better formating of the output
    cout << endl << endl;
    return input[0];
}

bool Hangman::isCharInWord(char letter)
{
    bool answer = false;
    char input = tolower(letter);
    unsigned int index, stringLength;
        
    //Converts the string stream of guessed chars to a string to get its length
    string guessed = _guessedChars.str();

    //Checks if the given chars has already been already guessed 
    for(char& letter : guessed)
    {
        //The letter have been guessed before no need to check again
        if(letter == input)
            return true;
    }

    //We need the length of the string so we can map correct quesses from the real word to the underscored version
    stringLength = _currentWord.length();

    //Checks if the word contains instances of the guessed letter, uses a counted loop as index is needed
    for(index =0; index < stringLength; index++)
    {
        //The letter is allready converted to its lower case, so we more easily can check if it have been used
        if(_currentWord.at(index) == input || _currentWord.at(index) == toupper(input))
        {
            answer = true;
            _currentQuess.at(index) = _currentWord.at(index);
        }
    }

    //Adds the guessed character to the guessed characters string
    _guessedChars << input << " ";

    return answer;
}

void Hangman::printStatus(unsigned int triesLeft)
{
    cout << "Word: " << _currentQuess << endl;
    cout << "Tries Left: " << triesLeft << endl;
    cout << "Guessed Letters: " << _guessedChars.str() << endl << endl;

    cout << "The Gallow" << endl << endl;

    //Prints a man getting hanged depeding on how many faults the player have
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
