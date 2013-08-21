module WordList
    open System.IO
    open System.Linq

    let readWordList wordListPath = 
        try
            File.ReadLines wordListPath 
        with
            | _ -> printfn "%s" "ERROR: could not open the specified wordlist"; exit(-1)

    let getWordListSize wordListPath = Enumerable.Count (readWordList wordListPath)

    let computeRandomIndex wordListSize = (new System.Random()).Next(0, wordListSize)

    let getRandomWord wordListPath = 
        let randomIndex = computeRandomIndex (getWordListSize wordListPath)
        Enumerable.ElementAt (readWordList wordListPath, randomIndex)
