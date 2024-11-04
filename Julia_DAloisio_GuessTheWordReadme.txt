Julia D'Aloisio

You can compile this program with the command "gcc Julia_DAloisio_GuessTheWord.c -o Julia_DAloisio_GuessTheWord"
Then, you run the executable with the command "./Julia_DAloisio_GuessTheWord". wordlist.txt must be in the same directory as the file for the program to work. 

I implemented the game with a main function and multiple supporting functions that achieve the tasks that this assignment requires. I first begin by loading in words from the file and selecting a word randomly. Then, I prepare for the start of the game by calling my initializeGuessedLetters() function. This function will malloc space for a char pointer that I realloc during the game. I then initialize 3 variables, remainingGuesses, wordLength, and correctGuesses. Now I am ready to being the game.

As suggested in the assignment, I used a big while loop for the game. The conditions of the while loop are if the user has remaining guesses and if they still have less correct guesses than the length of the word (which indicates that they need to keep guessing). I first call my displayWord function, which prints either blank lines for the length of the word or the some blank lines with some of the correctly guessed letters, depending on what point you are at in the game. Then I read in a char and make sure to convert it to lower case. After this point, I need to check if the letter is already guessed correctly. I have a function for this which uses the strchr function to check if the character is in the char pointer that I passed into the function. If the function returns true the user will be notified that they already guessed the letter and will be prompted to try again. If the letter has not already been guessed, I add the letter to my guessedLetters char pointer with the addGuessedLetter function. This function reallocs the guessedLetters variable and returns a variable called newGuessed which contains the previous and new guesses. At this point, I need to check if the guess is correct. I achieve this through looping through each index of the word the game randomly chose to be selected and checking if any of the chars match the guess. If the guess matches, the user is notified; if its not a match, the user to also notified and the amount of guesses they have left decreases by 1. 

This while loop continues until either the user runs out of guesses or has correctly guessed the word. After existing the loop, the user to notified of the word and is either congratulated for correctly guessing the word or consoled for incorrectly guessing the word.


To play the game you need to compile and run the program with the wordslist.txt file in the same directory. Then start entering single characters in attempts to guess the word based on the amount of blank spaces there are. Continue this until you either run out of guesses and or successfully guess the word. 

I believe that all aspects of the program are working correctly. But there could have been something I missed.  
