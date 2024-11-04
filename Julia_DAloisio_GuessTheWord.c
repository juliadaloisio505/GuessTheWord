#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Julia D'Aloisio                                                                                                                                                                                                                                                                                                                                                                                                        

char** loadWords(const char* filename, int* wordCount){
    FILE* file = fopen(filename, "r");

    if(file == NULL){
        printf("Error opening file\n");
        return NULL;
    }

    char** words = NULL;
    *wordCount = 0;
    char buffer[100];


    while(fscanf(file, "%s", buffer) == 1){
        words = realloc(words, (*wordCount + 1) * sizeof(char*));
        if (words == NULL){
            printf("Memory allocation failed\n");
            fclose(file);
            return NULL;
        }

        words[*wordCount] = malloc(strlen(buffer) + 1);
        if(words[*wordCount] == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            return NULL;
        }

        strcpy(words[*wordCount], buffer);
        (*wordCount)++;
    }

    fclose(file);
    return words;
}


void freeWords(char** words, int wordCount){
    for(int i = 0; i < wordCount; i++){
        free(words[i]);
    }
    free(words);
}


char* initializeGuessedLetters(){
    char* guessedLetters = malloc(sizeof(char));
    if (guessedLetters == NULL){
        return NULL;
    }
    guessedLetters[0] = '\0';
    return guessedLetters;
}


int isLetterGuessed(char letter, const char* guessedLetters) {
    return strchr(guessedLetters, letter) != NULL;
}


char* addGuessedLetter(char* guessedLetters, char letter) {
    int len = strlen(guessedLetters);
    char* newGuessed = realloc(guessedLetters, len + 2);
    //+2 bc new char & null terminator                                                                                                                                                                                                                                                                                                                                                                                   
    if(newGuessed == NULL){
        return guessedLetters;
    }
    newGuessed[len] = letter;
    newGuessed[len + 1] = '\0';
    return newGuessed;
}


void displayWord(const char* word, const char* guessedLetters) {
    for(int i = 0; word[i] != '\0'; i++){
        if(isLetterGuessed(word[i], guessedLetters)){
            printf("%c ", word[i]);
        }
        else{
            printf("_ ");
        }
    }
    printf("\n");
}

int main(){
    srand(time(NULL));


    int wordCount;
    char** words = loadWords("wordlist.txt", &wordCount);
    if(words == NULL){
        return 1;
    }


    int randomIndex = rand() % wordCount;
    char* wordToGuess = words[randomIndex];

    char* guessedLetters = initializeGuessedLetters();
    if(guessedLetters == NULL){
        freeWords(words, wordCount);
        return 1;
    }

    int remainingGuesses = 6;
    int wordLength = strlen(wordToGuess);
    int correctGuesses = 0;

    printf(">>>Welcome to Guess the Word!\n");


    while(remainingGuesses > 0 && correctGuesses < wordLength){
        printf("\n");
        displayWord(wordToGuess, guessedLetters);
        printf("%d guesses remaining.\n", remainingGuesses);

        char guess;
        printf(">>>Guess your letter:");
        printf("\n");
        scanf(" %c", &guess);
        guess = tolower(guess);


        if(isLetterGuessed(guess, guessedLetters)){
            printf("You already guessed that - try again.\n");
            continue;
        }

        guessedLetters = addGuessedLetter(guessedLetters, guess);


        int foundInWord = 0;
        for(int i = 0; wordToGuess[i] != '\0'; i++){
            if(tolower(wordToGuess[i]) == guess){
                foundInWord = 1;
                correctGuesses++;
            }
        }

        if(foundInWord){
            printf("'%c' is in the word.\n", guess);
        }
        else{
            printf("'%c' is not in the word.\n", guess);
            remainingGuesses--;
        }
    }


    printf("\nThe word was: %s\n", wordToGuess);
    printf("\n");
    if(correctGuesses == wordLength){
        printf("Yay! You guessed right, good job!\n");
        printf("\n");
    }
    else{
        printf("Sorry, you ran out of guesses. Thanks for playing!\n");
        printf("\n");

    }
    free(guessedLetters);
    freeWords(words, wordCount);
    return 0;
}
