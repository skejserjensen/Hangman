#!/bin/python

##Local Import
import wordlist


class Hangman:
    """
    Methods for playing a game of hangman, uses the word list class to
    retrieve words from the word list
    """

    ##Public Methods
    def start_game(self, tries):
        if self.__play_game(tries):
            print("Congratulations, you guessed the word \"" + self.__random_word + "\" correctly.")
        else:
            print("You did not guess \"" + self.__random_word + "\" correctly, and have been hanged.")

    ##Constructor
    def __init__(self, word_List_Path):
        """Creates a word list so random words can be requested"""

        ##Instance Variables
        self.__random_word = ""
        self.__guessed_chars = ""
        self.__word_list = wordlist.WordList(word_List_Path)

    ##Private Methods
    def __play_game(self, tries):
        """Method for comparing the users guess and counts tries down"""
        self.__tries_left = tries
        self.__random_word = self.__word_list.get_random_word()
        self.__current_guess = list('_' * len(self.__random_word))

        #Prints the beginning status of the game
        self.__print_status()

        #Asks the user for a guess and checks it against the word until no more tries are left
        while (self.__tries_left > 0):
            guess = self.__get_char()

            if not (self.__is_char_in_word(guess)):
                self.__tries_left -= 1

            self.__print_status()

            if self.__random_word == "".join(self.__current_guess):
                return True

        return False

    def __get_char(self):
        """Gets one char from the user as a guess"""
        user_input = input("Enter your next guess: ").strip()

        #A couple of newline creates some space between the result of each guess
        print("\n")
        return user_input[0]

    def __is_char_in_word(self, guess):
        """Checks if the guess is a letter in the word, or have been guessed before"""
        result = False
        guess_in_lower = guess.lower()

        #We check if the letter have been guessed before
        if(guess_in_lower in self.__guessed_chars):
            return True

        #We need the length of the string so we can map correct guesses from the real word to the underscored version
        string_length = len(self.__random_word)

        #Checks if the word contains instances of the guessed letter, uses a counted loop as index is needed
        for index in range(0, string_length):

            #The letter is allready converted to its lower case, so we more easily can check if it have been used
            if self.__random_word[index] == guess_in_lower or self.__random_word[index] == guess_in_lower.upper():
                result = True
                self.__current_guess[index] = self.__random_word[index]

        #Adds the guessed character to the guessed characters string
        self.__guessed_chars = self.__guessed_chars + guess_in_lower + " "

        return result

    def __print_status(self):
        """Prints a fancy gallow to scare the user when he guesses wrong"""
        print("Word: " + ''.join(self.__current_guess))
        print("Tries Left: " + str(self.__tries_left))
        print("Guessed Letters: " + self.__guessed_chars + "\n")

        print("The Gallow\n")

        #Prints a man/women getting hanged depeding on how many tries the player have left
        if(self.__tries_left == 10):
            print("\n\n\n\n\n\n   ")
        elif(self.__tries_left == 9):
            print("\n\n\n\n\n   \n_______________\n")
        elif(self.__tries_left == 8):
            print("\n\n\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 7):
            print("  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 6):
            print("  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 5):
            print("  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 4):
            print("  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 3):
            print("  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 2):
            print("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 1):
            print("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n")
        elif(self.__tries_left == 0):
            print("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n")
