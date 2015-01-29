(defn read-random-word [word-list-path]
  (rand-nth (clojure.string/split-lines (slurp word-list-path))))
