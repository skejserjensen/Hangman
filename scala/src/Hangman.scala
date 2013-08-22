class Hangman(wordListPath: String) {
 
  /* Package Methods */
  def startGame(): Unit = {
    //Grabs a new word from the word list and convert it to underscores
    val randomWord = this.wordList.getRandomWord
    val currentGuess = "_" * randomWord.size
   
    //It is much easiere to compare the result if everything is lowercase inside the game
    if(playGame(randomWord.toLowerCase, currentGuess, "", 10))
        println("Congratulations, you guessed the word \"" + randomWord + "\" correctly.")
    else
        println("You did not guess \"" + randomWord + "\" correctly, and have been hanged.")
  }

  /* Private Methods */
  private def playGame(randomWord: String, currentGuess: String, guessedChars: String, tries: Int): Boolean = tries match {
    case 0 => 
      printStatus(currentGuess, guessedChars, tries)
      false
    case _ => {
      if(randomWord == currentGuess)
        return true

      //Prints the status of the game and ask the user for a guess, the println is just for formating of output
      printStatus(currentGuess, guessedChars, tries)
      val guess: Char = getGuess
      println

      //Checks if the used guessed correctly, have tried the letter before, or guessed on a letter not in the word
      if(randomWord.contains(guess)) {
        val newCurrentGuess = buildUpdatedCurrentGuess(guess, randomWord.toList.zip(currentGuess.toList))
        val newGuessedChars = buildUpdatedGuessedChars(guess, guessedChars)
        playGame(randomWord, newCurrentGuess, newGuessedChars, tries)
      }
      else if(guessedChars.contains(guess))
        playGame(randomWord, currentGuess, guessedChars, tries)
      else
        playGame(randomWord, currentGuess, buildUpdatedGuessedChars(guess, guessedChars), tries-1)
      }
  }

  private def getGuess(): Char = {
    try {
        var guess = '0'
        do {
            print("Enter your next guess: ")
            guess = readChar.toLower
        } while (!guess.isLetter)
        guess         
    }
    catch {
      case ex: java.lang.StringIndexOutOfBoundsException => getGuess
    }
  }

  private def buildUpdatedCurrentGuess(guess: Char, wordState: List[(Char, Char)]): String = wordState match {
    case List() => ""
    case x :: xs => if (x._1 == guess) x._1 +: buildUpdatedCurrentGuess(guess, wordState.tail) 
                    else x._2 +: buildUpdatedCurrentGuess(guess, wordState.tail) 
  }

  private def buildUpdatedGuessedChars(guess: Char, guessedChars: String): String = {
    if (guessedChars.contains(guess)) guessedChars
    else guessedChars + " " + guess
  }

  private def printStatus(currentGuess: String, guessedChars: String, tries: Int)
  {
      println("Word: " + currentGuess)
      println("Tries Left: " +tries)
      println("Guessed Letters: "+ guessedChars + "\n")

      println("The Gallow\n\n")

      tries match {
        case 10 => println("\n\n\n\n\n\n")
        case 9 => println("\n\n\n\n\n   \n_______________\n")
        case 8 => println("\n\n\n  |\n  |\n  |\n________________\n")
        case 7 => println("  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        case 6 => println("  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        case 5 => println("  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        case 4 => println("  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        case 3 => println("  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n")
        case 2 => println("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n")
        case 1 => println("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n")
        case 0 => println("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n")
      }
  }

  /* Instance variables */
  private val wordList: WordList = new WordList(wordListPath)
}
