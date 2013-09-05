(module main racket 
        (require "hangman.rkt")

        (let ([args (vector-length (current-command-line-arguments))])
            (cond
                [(equal? 0 args)(start-game "../data/wordlist")]
                [(equal? 1 args)(start-game (vector-ref (current-command-line-arguments) 0))]
                [else (display "usage: racket main.rkt [WordListPath]\n")])))
