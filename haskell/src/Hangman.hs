module Hangman
(
    startGame
) where

import WordList
import Data.Char
import System.IO

data GData = GData  { randomWord :: String
                    , currentGuess :: String
                    , usedLetters :: [Char] 
                    , guessesLeft :: Int
                    } deriving (Show)

startGame :: String -> IO ()
startGame wordListPath = do 
        word <- getRandomWord wordListPath
        gameResult <- playGame (GData word (wordToUnderscore word) "" 10)
        if (guessesLeft gameResult) > 0
            then putStrLn ("You gussed the word '" ++ word ++ "' correctly")
            else putStrLn ("You did not guess '" ++ word ++ "' correctly and are now hanged")

wordToUnderscore :: String -> String
wordToUnderscore word = map (\char -> '_') word 

playGame :: GData -> IO GData
playGame (GData randomWord currentGuess usedLetters 0) = printStatus gameResult >> return gameResult
     where gameResult = (GData randomWord currentGuess usedLetters 0)
playGame (GData randomWord currentGuess usedLetters guessesLeft) = do
        printStatus (GData randomWord currentGuess usedLetters guessesLeft)
        guess <- getGuess
        -- Computes new lists for the letters used and the current guess
        let updatedCurrentGuess = updateGuess guess currentGuess randomWord
        let updatedUsedLetters = updateGuessed guess usedLetters 
        -- Checks if the player have guessed the word correctly
        if (updatedCurrentGuess == randomWord) 
            then return (GData randomWord currentGuess usedLetters guessesLeft)
            -- Checks if the player have used a guess or the random word contains the letter of if it is already tried
            else if ((elem guess randomWord) || (elem guess usedLetters))
                then playGame (GData randomWord updatedCurrentGuess updatedUsedLetters guessesLeft)
                else playGame (GData randomWord updatedCurrentGuess updatedUsedLetters (guessesLeft-1))

-- We read an entire line and then extracts the last charecter, to prevent left over chars in the buffer
getGuess :: IO Char
getGuess = putStr "Please enter your next guess: " >> hFlush stdout >> (getLine >>= (\input -> return (head input)))

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

printStatus :: GData -> IO ()
printStatus (GData randomWord currentGuess usedLetters guessesLeft) = do
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
