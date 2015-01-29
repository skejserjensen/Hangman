(module hangman racket
        (provide start-game)
        (require "wordlist.rkt")

        (define (start-game word-list-path)
          (let ([random-word (read-random-word word-list-path)])
            (if (play-game (string-downcase random-word) (make-string (string-length random-word) #\_) "" 10)
              (printf "Congratulations, you guessed the word \"~a\" correctly.\n" random-word)
              (printf "You did not guess \"~a\" correctly, and have been hanged.\n" random-word))))

        (define (play-game random-word current-guess guessed-chars tries-left)
          (match tries-left
                 [0 (print-status current-guess guessed-chars tries-left) #f]
                 [else (print-status current-guess guessed-chars tries-left)
                       (if (equal? current-guess random-word)
                         #t
                         (let ([user-guess (guess)])
                           (display "\n") ; Just formatting the output a bit
                           (cond
                             [(string-contains? user-guess guessed-chars)
                              (play-game random-word current-guess guessed-chars tries-left)]
                             [(string-contains? user-guess random-word)
                              (play-game random-word
                                         (update-current-guess user-guess (zip-strings random-word current-guess))
                                         (update-guessed-chars user-guess guessed-chars) tries-left)]
                             [else (play-game random-word current-guess
                                              (update-guessed-chars user-guess guessed-chars)
                                              (- tries-left 1))])))]))


        (define (guess)
          (display "Enter your next guess: ")
          ; Read-line is used, as read-char seems to leave a newline from return in the input buffer
          (let ([user-guess-string (read-line)])
            (if (< 0 (string-length user-guess-string))
              (let ([user-guess (string-ref user-guess-string 0)])
                (if (char-alphabetic? user-guess)
                  (char-downcase user-guess)
                  (guess)))
              (guess))))

        (define (string-contains? chr str)
          ; Member returns a pair if the list contained the element, so if we get a pair then list contained our element
          (pair? (member chr (string->list str))))

        (define (zip-strings str-one str-two)
          (map list (string->list str-one) (string->list str-two)))

        (define (update-current-guess user-guess zipped-word-current-guess)
          (list->string (foldl (lambda (elem acc)
                                 (if (equal? user-guess (car elem))
                                   (append acc (list (first elem)))
                                   (append acc (list (second elem)))))
                               empty zipped-word-current-guess)))

        (define (update-guessed-chars user-guess guessed-chars)
            (string-append guessed-chars (string user-guess) " "))

        (define (print-status current-guess guessed-chars tries-left)
          (printf "Word: ~a\n" current-guess)
          (printf "Tries Left: ~a\n" tries-left)
          (printf "Guessed Letters: ~a\n\n" guessed-chars)
          (printf "The Gallow\n\n\n")
          (match tries-left
                 [10 (display "\n\n\n\n\n\n\n")]
                 [9 (display "\n\n\n\n\n   \n_______________\n\n")]
                 [8 (display "\n\n\n  |\n  |\n  |\n________________\n\n")]
                 [7 (display "  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n")]
                 [6 (display "  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n")]
                 [5 (display "  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n")]
                 [4 (display "  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n\n")]
                 [3 (display "  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n\n")]
                 [2 (display "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n\n")]
                 [1 (display "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n\n")]
                 [0 (display "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n\n")])))
