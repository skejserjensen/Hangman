source('src/hangman.r')

# The TRUE argument suppresses non user defined args
command.line.argument <- commandArgs(TRUE)
number.of.arguments <- length(command.line.argument)

if (number.of.arguments == 0) {
    startGame('../data/wordlist')
} else if (number.of.arguments == 1) {
    startGame(command.line.argument[1])
} else {
    cat('usage: Rscript main.r [WordListPath]\n')
}
