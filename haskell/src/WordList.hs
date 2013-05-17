module WordList
(
    getRandomWord
) where

import System.Random

getRandomWord :: String -> IO String
getRandomWord wordListPath = readWordList wordListPath >>= (\wordList -> getRandomIndex wordList >>= (\index -> return $ wordList !! index))

readWordList :: String -> IO [String]
readWordList wordListPath = readFile wordListPath >>= (\wordList -> return (words wordList))

getRandomIndex :: [a] -> IO Int
getRandomIndex wordList = randomRIO (0, length wordList)
