(require 'src.wordlist)

(defn- print-status [current-guess guessed-chars tries-left]
  (println "Word:" current-guess)
  (println "Tries Left:" tries-left)
  (println "Guessed Letters:" guessed-chars "\n")
  (println "The Gallow\n\n")
  (case tries-left
   10 (println "\n\n\n\n\n\n")
    9 (println "\n\n\n\n\n   \n_______________\n")
    8 (println "\n\n\n  |\n  |\n  |\n________________\n")
    7 (println "  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
    6 (println "  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
    5 (println "  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
    4 (println "  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n")
    3 (println "  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n")
    2 (println "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n")
    1 (println "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n")
    0 (println "  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n")))

(defn- guess []
  (print "Enter your next guess: ")
  (flush) ; Needed to ensure a print without a new line is shown
  (let [user-guess-string (read-line)]
    (if (< 0 (count user-guess-string))
      (let [user-guess (first (clojure.string/lower-case user-guess-string))]
        (if (Character/isLetter user-guess)
          user-guess
          (guess)))
      (guess))))

(defn- update-guessed-chars [user-guess guessed-chars]
  (str guessed-chars user-guess " "))

(defn- update-current-guess [user-guess zipped-word-current-guess]
  (reduce (fn [acc elem]
            (if (= user-guess (first elem))
              (str acc (first elem))
              (str acc (second elem)))) "" zipped-word-current-guess))

(defn- string-contains? [chr string]
  (.contains string (str chr)))

(defn- play-game [random-word current-guess guessed-chars tries-left]
  (case tries-left
    0 (print-status current-guess guessed-chars tries-left) false
    :else (do
            (print-status current-guess guessed-chars tries-left)
            (if (= current-guess random-word)
              true
              (let [user-guess (guess)]
                (println) ; Just formatting the output a bit
                (cond
                  (string-contains? user-guess guessed-chars)
                    (play-game random-word current-guess guessed-chars tries-left)
                  (string-contains? user-guess random-word)
                    (play-game random-word
                               (update-current-guess user-guess (map vector random-word current-guess))
                               (update-guessed-chars user-guess guessed-chars) tries-left)
                  :else (play-game random-word current-guess
                                   (update-guessed-chars user-guess guessed-chars) (- tries-left 1))))))))

(defn start-game [word-list-path]
  (let [random-word (read-random-word word-list-path)]
    (if (play-game (clojure.string/lower-case random-word)
                   (apply str (repeat (count random-word) "_")) "" 10)
      (println (str "Congratulations, you guessed the word \"" random-word "\" correctly."))
      (println (str "You did not guess \"" random-word "\" correctly, and have been hanged.")))))
