# Public Functions
getRandomWord <- function(word.list.path) {
    if( ! file.exists(word.list.path)) {
        cat('ERROR: The file containing the wordlist does not exist\n')
        quit("no", -1)
    }
    word.list <- readLines(word.list.path)
    return(sample(word.list, 1))
}
