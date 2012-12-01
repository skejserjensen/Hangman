module WordList
(
    getRandomWord
) where

import Control.Monad.Random

getRandomWord :: String -> IO String
getRandomWord wordListPath = do 
                wordList <- readWordList wordListPath
                index <- getRandomIndex wordList
                return (wordList!!index)

readWordList :: String -> IO [String]
readWordList wordListPath = readFile wordListPath >>= (\wordList -> return (words wordList))

getRandomIndex :: [a] -> IO Int
getRandomIndex wordList = getRandomR (0, length wordList)
