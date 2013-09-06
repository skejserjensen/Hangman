(module main racket 
        (require "hangman.rkt")

        (match (vector-length (current-command-line-arguments))
               [0 (start-game "../data/wordlist")]
               [1 (start-game (vector-ref (current-command-line-arguments) 0))]
               [else (display "usage: racket main.rkt [WordListPath]\n")]))
