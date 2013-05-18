#!/bin/python

##External Imports
import random


class WordList:
    """
    Encapsulates all methods for handling the word list, is mainly the class
    concerned with returning random words and insuring that handles get closed.
    """

    ##Public Methods
    def get_random_word(self):
        """Return a random word from the word list provided"""
        randomWordIndex = random.randint(0, self.__wordListLength)
        with open(self.__wordListPath) as wordListHandle:
            for _ in range(0, randomWordIndex):
                randomWord = wordListHandle.readline()
            return randomWord.rstrip()

    ##Constructor
    def __init__(self, wordListPath):
        """Opens a handle to the wordlist so word can be extracted"""

        ##Instance Variables
        self.__wordListPath = wordListPath
        self.__wordListLength = self.__get_file_length(wordListPath)

    ##Private Methods
    def __get_file_length(self, wordListPath):
        """Read the number of lines from the file in the handle"""
        with open(wordListPath) as wordListHandle:
            return len(wordListHandle.readlines())
