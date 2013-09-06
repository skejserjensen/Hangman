(module wordlist racket 
    (provide read-random-word)

    (define (read-random-word word-list-path)
      (random-element (file->lines word-list-path)))

    (define (random-element word-list)
      (list-ref word-list (random (length word-list)))))
