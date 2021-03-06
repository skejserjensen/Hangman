module Hangman
(
    startGame
) where

import WordList
import Data.Char
import System.IO

startGame :: String -> IO ()
startGame wordListPath = do 
        randomWord <- getRandomWord wordListPath
        gameResult <- playGame randomWord (wordToUnderscore randomWord) "" 10
        if gameResult
            then putStrLn ("You gussed the word '" ++ randomWord ++ "' correctly")
            else putStrLn ("You did not guess '" ++ randomWord ++ "' correctly and are now hanged")

wordToUnderscore :: String -> String
wordToUnderscore randomWord = map (\char -> '_') randomWord 

playGame :: String -> String -> String -> Int -> IO Bool
playGame randomWord currentGuess usedLetters 0 = printStatus randomWord currentGuess usedLetters 0 >> return False
playGame randomWord currentGuess usedLetters guessesLeft = do
        printStatus randomWord currentGuess usedLetters guessesLeft
        guess <- getGuess
        -- Computes new lists for the letters used and the current guess
        let updatedCurrentGuess = updateGuess guess currentGuess randomWord
        let updatedUsedLetters = updateGuessed guess usedLetters 
        -- Checks if the player have guessed the word correctly
        if (updatedCurrentGuess == randomWord) then return True
            -- Checks if the player have used a guess or the random word contains the letter of if it is already tried
            else if ((elem guess randomWord) || (elem guess usedLetters))
                then playGame randomWord updatedCurrentGuess updatedUsedLetters guessesLeft
                else playGame randomWord updatedCurrentGuess updatedUsedLetters (guessesLeft-1)

-- We read an entire line and then extracts the last charecter, to prevent left over chars in the buffer
getGuess :: IO Char
getGuess = putStr "Please enter your next guess: " >> hFlush stdout >> getLine >>= 
    (\input -> if null input then getGuess else
        if isAlpha $ head input then return $ head input else getGuess)

updateGuess :: Char -> String -> String -> String
updateGuess _ _ [] = []
updateGuess guess (cg:cGuess) (rw:rWord)
    -- Both upper and lower case are checked as the word could be written with a combination
    | (rw == (toUpper guess)) = [rw] ++ (updateGuess guess cGuess rWord)
    | (rw == (toLower guess)) = [rw] ++ (updateGuess guess cGuess rWord)
    | otherwise = [cg] ++ (updateGuess guess cGuess rWord)

updateGuessed :: Char -> [Char] -> [Char]
updateGuessed guess usedLetters 
    | elem guess usedLetters = usedLetters 
    | otherwise = usedLetters ++ [' ', (toLower guess)]

printStatus :: String -> String -> String -> Int -> IO ()
printStatus randomWord currentGuess usedLetters guessesLeft = do
        putStrLn ("\nWord: " ++ currentGuess)
        putStrLn ("Tries Left: " ++ (show guessesLeft))
        putStrLn ("Guessed Letters: " ++ usedLetters)
        putStrLn "\nThe gallow\n\n"
        -- Draws a small ascii gallow based on the number of guesses the player has left
        case guessesLeft of 10 -> putStrLn "\n\n\n\n\n\n   \n"
                            9 -> putStrLn "\n\n\n\n\n   \n_______________\n\n"
                            8 -> putStrLn "\n\n\n  |\n  |\n  |\n________________\n\n"
                            7 -> putStrLn "  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"
                            6 -> putStrLn "  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"
                            5 -> putStrLn "  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"
                            4 -> putStrLn "  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"
                            3 -> putStrLn "  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n\n"
                            2 -> putStrLn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n\n"
                            1 -> putStrLn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n\n"
                            0 -> putStrLn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n\n"
        -- The program has a tendency to write to output at interesting times if we do not force it
        hFlush stdout                                  
