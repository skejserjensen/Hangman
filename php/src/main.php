<?php

//Imports the wordlist
require_once("hangman.php");

//Checks if an alternative wordlist path have been provided
if(sizeof($argv) == 2)
    $hangman = new Hangman($argv[1]);
else
    $hangman = new Hangman("../data/wordlist");

//Starts the game
$hangman->startGame();

?>
