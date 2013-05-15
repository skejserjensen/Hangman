import Hangman
import System.Environment

--main :: IO () 
main = getArgs >>= parseArguments >>= startGame

-- If the user only specifies one argument then they are properly  using their own word list,
-- otherwise we just use the internal word list. 
parseArguments :: [String] -> IO String
parseArguments [] = return "../data/wordlist"
parseArguments (arg:_) = return arg
