(require 'src.hangman)

(case (count *command-line-args*)
  0 (start-game "../data/wordlist")
  1 (start-game (first *command-line-args*))
  (println "usage: clojure main.clj [WordListPath]"))
