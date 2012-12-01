#!/bin/bash

# Just a small script to build the program using cabal, as it require more then one manual step
cabal configure
cabal build

# I copy I to ./ as the path to the word list is set to work from this directory as it seemed the most natural
cp dist/build/Hangman/Hangman ./Hangman

# The dist directory is deleted as I only needs the executable itself
rm -rf dist
