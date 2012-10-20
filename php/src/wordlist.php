<?php

/**
 * Encapsulates all methods for handling the word list, is mainly the class 
 * concerned with returning random words and insuring that handles get closed.
 */
class WordList
{

    /**
     * Return a random word selected from the word list 
     *
     * @return a random word
     */
    public function getRandomWord()
    {
        //Computes the index of the word to get at random
        $randomWordIndex = rand(0, $this->wordListLength);

        //Retrieves the word in the list corresponding to the above index
        $linecount = 0;
        rewind($this->wordListHandle);
        
        while($linecount < $randomWordIndex)
        {
            $randomWord = fgets($this->wordListHandle);
            $linecount++;
        }

        //Removes the new line character before returning the string
        return substr($randomWord, 0, -1);
    }


    /**
     * Calls the initialise methods.
     */
    public function __construct($wordListPath)
    {
        //Opens the word list and counts have many words it contains
        $this->openWordList($wordListPath);
        $this->countLinesInWordList();
    }

    /**
     * Ensures that the file handler for the word list is closed 
     */
    public function __destruct()
    {
        if(is_resource($this->wordListHandle))
            fclose($this->wordListHandle);
    }


    /**
     * Opens the word list if it exists and if not terminates
     */
    private function openWordList($filePath)
    {
        if(file_exists($filePath))
            $this->wordListHandle = fopen($filePath, "r");
        else
        {
            echo "ERROR: The wordlist does not exist\n";
            exit(-1);
        }
    }

    /**
     * Counts the number of words in the word list and saves it
     */
    private function countLinesInWordList()
    {
        $linecount = 0;

        //Reads the file line by line to prevent memory problems if the file is large
        while(!feof($this->wordListHandle))
        {
            fgets($this->wordListHandle);
            $linecount++;
        }

        $this->wordListLength = $linecount;
    }


    /**
     * Private member variables
     */
    private $wordListHandle;
    private $wordListLength;
}

?>
