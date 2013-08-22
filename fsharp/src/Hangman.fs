module Hangman
    open System
    open WordList
    
    let printStatus currentGuess guessedChars triesLeft: unit = 
        printfn "Word: %s" currentGuess
        printfn "Tries Left: %i" triesLeft
        printfn "Guessed Letters:  %s\n" guessedChars 

        printfn "The Gallow\n\n"

        match triesLeft with
        | 10 -> printfn "\n\n\n\n\n\n"
        | 9 -> printfn "\n\n\n\n\n   \n_______________\n"
        | 8 -> printfn "\n\n\n  |\n  |\n  |\n________________\n"
        | 7 -> printfn "  |\n  |\n  |\n  |\n  |\n  |\n________________\n"
        | 6 -> printfn "  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n"
        | 5 -> printfn "  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n"
        | 4 -> printfn "  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n"
        | 3 -> printfn "  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n"
        | 2 -> printfn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n"
        | 1 -> printfn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n"
        | 0 -> printfn "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n"
        | _ -> eprintfn "ERROR: internal error, invalid number of tries left."

    //A string conversion to list, needed as strings cannot be zipped in this version of fsharp
    let stringToList theString: char list = [for c in theString -> c]

    //Created my own version of String.Contains as fsharp's version did not seem to accept chars as input
    let stringContains theChar theString: bool = String.exists (fun c -> c = theChar) theString

    let rec buildUpdatedCurrentGuess guess (wordState: (char*char) list): string =
        match wordState with
        | [] -> ""
        | head :: tail -> 
            if (fst head) = guess
            then Char.ToString (fst head) + buildUpdatedCurrentGuess guess tail
            else Char.ToString (snd head) + buildUpdatedCurrentGuess guess tail

    let buildUpdatedGuessedChars guess guessedChars: string =
        if String.exists (fun c -> c = guess) guessedChars
        then guessedChars
        else guessedChars + Char.ToString guess + " "

    let rec playGame randomWord currentGuess guessedChars triesLeft: bool =
        match triesLeft with
        | 0 -> 
            printStatus currentGuess guessedChars triesLeft
            false
        | _ ->
            if currentGuess = randomWord
            then true
            else
                printStatus currentGuess guessedChars triesLeft

                //Gets a guess from user, and prints a newline for formatting
                //A mutable variable is used, as a function containing ReadLine() runs endlessly on mono or becuase I made a mistake
                let mutable guess = '0'
                while not (Char.IsLetter guess) do
                    printf "Enter your next guess: "
                    let guessString = Console.ReadLine()
                    if guessString.Length = 0
                    then guess <- '0'
                    else guess <- Char.ToLower guessString.[0]
                printfn ""
                               
                //Check if the guess is in the random word, or if the user have already tried it
                if stringContains guess randomWord
                then 
                    let newCurrentGuess = buildUpdatedCurrentGuess guess (List.zip (stringToList randomWord) (stringToList currentGuess))
                    let newGuessedChars = buildUpdatedGuessedChars guess guessedChars
                    playGame randomWord newCurrentGuess newGuessedChars triesLeft
                elif stringContains guess guessedChars 
                then
                    playGame randomWord currentGuess guessedChars triesLeft
                else
                    playGame randomWord currentGuess (buildUpdatedGuessedChars guess guessedChars) (triesLeft-1)

    let startGame wordListPath: unit = 
        let randomWord = getRandomWord wordListPath
        let currentGuess = String.replicate (String.length randomWord) "_"

        if playGame randomWord currentGuess "" 10
        then printfn "Congratulations, you guessed the word \"%s\" correctly." randomWord
        else printfn "You did not guess \"%s\" correctly, and have been hanged." randomWord

