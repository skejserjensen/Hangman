open Hangman 

[<EntryPoint>]
let main (args: string[]): int = 
    match args.Length with
    | 0 -> startGame "../data/wordlist"
    | 1 -> startGame args.[0]
    | _ -> printfn "%s" "usage: Hangman.exe [WordListPath]"
    0
