#!/bin/python

##External Imports
import sys

##Internal Imports
import hangman

#Checks if the user gave us an alternative word list
if len(sys.argv) < 1:
    wordListPath = sys.argv[1]
else:
    wordListPath = "../data/wordlist"

hangman_game = hangman.Hangman(wordListPath)
hangman_game.start_game()
