#import "hangman.h"

@implementation Hangman 

    /** Instance variables **/
    WordList* wordList;
    NSString* currentWord;
    NSMutableString *currentGuess;
    NSMutableString *guessedChars;

    /** Constructor **/
    - (id)initWithWordListPath: (NSString*) listPath {
        self = [super init];
        wordList = [[WordList alloc] initWithWordListPath: listPath];
        currentWord = [wordList getRandomWord];
        return self;
    }

    /** Destructor **/
    - (void)dealloc {
        [super dealloc];
        [currentWord release];
        [currentGuess release];
        [guessedChars release];
    }

    /** Public methods **/
    - (bool)startGame  {
        bool result = [self playGame: 10];

        if(result) 
            printf("Congratulations, you guessed the word \"%s\" correctly.\n", [currentWord UTF8String]);
        else 
            printf("You did not guess \"%s\" correctly, and have been hanged.\n", [currentWord UTF8String]);

        return result;
    }

    /** Private methods **/
    - (bool)playGame: (int)triesLeft {
        currentGuess = [[NSMutableString alloc] initWithCharacter: '_' length: [currentWord length]];
        guessedChars = [[NSMutableString alloc] init];

        //We print the status for the user before the game begins so they can see how many chars the word contains
        [self printStatus: triesLeft guess: [currentGuess UTF8String] chars: [guessedChars UTF8String]];

        //The main game loop that takes guesses and decreaments tries if the user guesss wrong
        while(triesLeft > 0) {
            char guess = [self getGuess];
            //Checks if the char is in the word the user is guessing and updates guessed chars
            if(![self isCharInWord: guess])
                triesLeft--;

            //Objective-C prefers enums instead of integer as retun value so converting to an int might beconme a problem
            if([currentWord localizedCaseInsensitiveCompare: currentGuess] == NSOrderedSame)
                return true;

            [self printStatus: triesLeft guess: [currentGuess UTF8String] chars: [guessedChars UTF8String]];
        }
        return false;
    }

    - (char)getGuess {
        char tempInput = 0;
        char userInput = 0;

        while (!isalpha(userInput)) {
            printf("Enter your next guess: ");
            tempInput = getchar();
            userInput = tempInput;

            //Flushes the input buffer until a new line
            while(tempInput != '\n')
                tempInput = getchar();
        }
        return userInput;
    }

    - (bool)isCharInWord: (char) guess {
        bool correctGuess = false;
        char lowerGuess = tolower(guess);

        //Checks if the guessed char has already been tried by the user
        int guessedCharsLength = [guessedChars length];
        for(int index = 0; index < guessedCharsLength; index++)
            if([guessedChars characterAtIndex: index] == lowerGuess)
                return true;

        //The guess has not been done before, so we add it to the list
        [guessedChars appendFormat: @" %c", lowerGuess];

        //Checks if the word we are guessing contains instances of the guessed char
        int currentWordLength = [currentWord length];
        NSString* lowerGuessString = [[NSString alloc] initWithFormat: @"%c", lowerGuess];

        for(int index = 0; index < currentWordLength; index++) {
            if([currentWord characterAtIndex: index] == lowerGuess) {
                [currentGuess replaceCharactersInRange: NSMakeRange(index,1) withString: lowerGuessString];
                correctGuess = true;
            }
        }
        [lowerGuessString release];
        return correctGuess;
    }

    - (void)printStatus: (unsigned int) guessesLeft guess: (const char*) currentGuess chars: (const char*) guessedChars {
           printf("Word: %s\n", currentGuess);
           printf("Tries Left: %d\n", guessesLeft);
           printf("Guessed Letters: %s\n\n", guessedChars);

           printf("The Gallow\n\n");

           switch(guessesLeft) {
               case 10:
                   printf("\n\n\n\n\n\n\n");
                   break;
               case 9:
                   printf("\n\n\n\n\n   \n_______________\n\n");
                   break;
               case 8:
                   printf("\n\n\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 7:
                   printf("  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 6:
                   printf("  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 5:
                   printf("  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 4:
                   printf("  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 3:
                   printf("  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 2:
                   printf("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n\n");
                   break;
               case 1:
                   printf("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n\n");
                   break;
               case 0:
                   printf("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n\n");
                   break;
           }
    }
@end
