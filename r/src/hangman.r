source('src/wordlist.r')

## Public Functions
startGame <- function(word.list.path) {
    random.word <- getRandomWord(word.list.path)
    if (playGame(random.word)) {
      cat('Congratulations, you guessed the word ', random.word, ' correctly.\n', sep='"')
    } else {
      cat('You did not guess ', random.word, ' correctly, and have been hanged.\n', sep='"')
    }
}

## Privat Functions
playGame <- function(random.word) {

    # Setup
    tries.left <- 10
    guessed.chars <- ''
    current.guess <- paste(replicate(nchar(random.word), '_'), collapse=' ')
    printStatus(current.guess, guessed.chars, tries.left)

    # Game Loop
    while(tries.left != 0) {
        user.guess <- getGuess()
        updated.guessed.chars <- updateGuessedChars(user.guess, guessed.chars)
        updated.current.guess <- updateCurrentGuess(user.guess, current.guess, random.word)

        if ( ! grepl('_', updated.current.guess)) {
            return(TRUE)
        } else if(current.guess == updated.current.guess &&
                  guessed.chars != updated.guessed.chars) {
            tries.left <- tries.left - 1
        }
        current.guess <- updated.current.guess
        guessed.chars <- updated.guessed.chars
        printStatus(current.guess, guessed.chars, tries.left)
    }
    return(FALSE)
}

getGuess <- function() {
  cat('Enter your next guess: ')

  # HACK: allows reading stdin input in batch mode
  con <- if (interactive()) stdin() else file('stdin')
  guess <- scan(file=con, what='character', nmax=1, quiet=TRUE, flush=TRUE)
  close(con)

  return(substr(guess, 1, 1))
}

updateCurrentGuess <- function(user.guess, current.guess, random.word) {
    updated.current.guess <- unlist(strsplit(current.guess, split=' '))

    for (index in 1:nchar(random.word)) {
        char <- substr(random.word, index, index)
        if (char == user.guess) {
            updated.current.guess[index] <- char
        }
    }
    return(paste(updated.current.guess, collapse=' '))
}

updateGuessedChars <- function(user.guess, guessed.chars) {

    # User already guessed that
    if (grepl(user.guess, guessed.chars)) {
        return(guessed.chars)
    }
    return(paste(guessed.chars, user.guess))
}

printStatus <- function(current.guess, guessed.chars, tries.left) {
    cat('Word: ', current.guess, '\n')
    cat('Tries Left:', tries.left, '\n')
    cat('Guessed Letters:', guessed.chars, '\n\n')
    cat('The Gallow\n\n\n')

    if (tries.left == 10) {
        cat('\n\n\n\n\n\n\n')
    } else if (tries.left == 9) {
        cat('\n\n\n\n\n   \n_______________\n\n')
    } else if (tries.left == 8) {
        cat('\n\n\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 7) {
        cat('  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 6) {
        cat('  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 5) {
        cat('  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 4) {
        cat('  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 3) {
        cat('  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 2) {
        cat('  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 1) {
        cat('  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n\n')
    } else if (tries.left == 0) {
        cat('  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n\n')
    }
}
