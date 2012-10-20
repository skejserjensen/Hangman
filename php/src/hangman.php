<?php

/** Includes and require **/
require_once 'wordlist.php';

/**
 * Methods for playing a game of hangman, uses the word list class 
 * to retrieve words from the word list
 */
class Hangman
{
    /**
     * Starts the game, and informas the player how he/she did when the game is finnished
     **/
    public function startGame()
    {
        $gameResult = $this->playGame(); 

        if($gameResult) 
            echo "Congratulations, you guessed the word correctly.\n";
        else 
            echo "You did not guess \"{$this->currentWord}\" correctly, and have been hanged.\n";
    }


    /**
     * Initialise member constant member variables 
     */
    function __construct($wordListPath)
    {
        //Sets the maximum number of times the player can guess wrong
        $this->maxFaults = 10;

        //Creates a word list class, for a handle to the word list
        $this->wordList = new WordList($wordListPath);
    }


    /**
     * Gets a new random word and asks the player for a guess until they runs out of tries
     **/
    private function playGame()
    {
        $faults = 0;

        //Gets a new word from the word list
        $this->currentWord = $this->wordList->getRandomWord();

        //Creates a string of underscores at equivalent length to the word from the word list
        $wordLength = strlen($this->currentWord);
        for($counter = 0; $counter < $wordLength; $counter++)
            $this->currentGuess .= '_';

        //Prints the length of the word to be guessed and a threathing gallow
        $this->printStatus($faults);

        //Asks for at new guess as long as the word has not being guessed or the user have tried enough times 
        while ($faults < $this->maxFaults) 
        {
            $guess = $this->getChar(); 

            if(!$this->isCharInWord($guess))
                $faults++;

            $this->printStatus($faults);

            if($this->currentWord === $this->currentGuess)
                break;
        }

        //Return true if the word was guessed without using all the given guesses
        if($faults < $this->maxFaults)
            return true;
        else
            return false;


        return false;
    }

    /**
     * Asks the player for a guess and gets one char from the commandline  
     **/
    private function getChar()
    {
        echo "Enter your next guess: ";

        //A string is read as reading a single char does not flush the input buffer of \n from the enter key
        $input = trim(fgets(STDIN));

        //A couple of newline creates some space between the result of each guess
        echo "\n\n";
        return $input[0];
    }

    /**
     * Checks if the guessed char exist in the word being guessed 
     **/
    private function isCharInWord($letter)
    {
        $answer = false;
        $letter = strtolower($letter);
        $guessedCharsLength = strlen($this->guessedChars);

        //Checks if the given chars has already been already guessed 
        for($index = 0; $index < $guessedCharsLength; $index++)
        {
            //The letter have been guessed before no need to check again
            if($this->guessedChars[$index] === $letter)
                return true;
        }

        //We need the length of the string so we can map correct guesses from the real word to the underscored version
        $stringLength = strlen($this->currentWord);

        //Checks if the word contains instances of the guessed letter, uses a counted loop as index is needed
        for($index = 0; $index < $stringLength; $index++)
        {
            //The letter is allready converted to its lower case, so we more easily can check if it have been used
            if(($this->currentWord[$index] === $letter) || ($this->currentWord[$index] === strtoupper($letter)))
            {
                $answer = true;
                $this->currentGuess[$index] = $this->currentWord[$index];
            }
        }

        //Adds the guessed character to the guessed characters string
        $this->guessedChars .= $letter .= " ";

        return $answer;
    }

    /**
     * Prints the users current status in the game to the screen 
     **/
    private function printStatus($faults)
    {
        echo "Word: {$this->currentGuess}\n";
        echo "Tries: " . ($this->maxFaults-$faults) . "\n";
        echo "Guessed: {$this->guessedChars}\n\n";

        echo "The Gallow\n\n";

        //Prints a man/women getting hanged depeding on how many faults the player have
        switch($faults) {
        case 0:
            echo "\n\n\n\n\n\n   \n";
            break;
        case 1:
            echo "\n\n\n\n\n   \n";
            echo "_______________\n\n";
            break;
        case 2:
            echo "\n\n\n  |\n  |\n  |\n";
            echo "________________\n\n"; 
            break;
        case 3:
            echo "  |\n  |\n  |\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 4:
            echo "  |--         \n";
            echo "  |\n  |\n  |\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 5:
            echo "  |------         \n";
            echo "  |\n  |\n  |\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 6:
            echo "  |------         \n";
            echo "  |     |\n  |\n  |\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 7:
            echo "  |------         \n";
            echo "  |     |\n  |     0\n  |\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 8:
            echo "  |------         \n";
            echo "  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n";
            echo "________________\n\n";
            break;
        case 9:
            echo "  |------         \n";
            echo "  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n";
            echo "________________\n\n"; 
            break;
        case 10:
            echo  "  |------         \n";
            echo  "  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n";
            echo  "________________\n\n";
            break;
        }
    }


    /**
     * Private member variables
     */
    private $maxFaults;
    private $currentWord;
    private $currentGuess;
    private $guessedChars;

    private $wordList;
}

?>
