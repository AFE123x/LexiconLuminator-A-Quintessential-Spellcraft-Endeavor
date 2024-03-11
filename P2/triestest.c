#include "tries.h"
#include<stdio.h>
#include<stdlib.h>
#define WORDLENGTH 17
/**
 * This is a testclient to test the functionality of the tries
 * implementation. tests for sanitition faults, segmentation,
 * and program runs as intended.
 *
 * @author Arun Felix, Kareem Jackson
*/
char** randomwords;
char* randomword(){
    char* word = (char*)malloc(sizeof(char) * WORDLENGTH);
    for(int i = 0; i < WORDLENGTH - 1; i++){

        word[i] = (rand() % 26) + 97;
        // printf("our random character%c\n",word[i]);
    }
    word[WORDLENGTH - 1] = '\0';
    printf("our random word is: %s\n",word);
    return word;
}
int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr,"./triesttest {number of variables}\n");
        return EXIT_FAILURE;
    }
    int arraysize = atoi(argv[1]);
    randomwords = malloc(sizeof(char*) * arraysize);
    for(int i = 0; i < arraysize; i++){
        randomwords[i] = randomword();
        put(randomwords[i]);
    }
    // print();
    for(int i = 0; i < arraysize; i++){
        if(!exists(randomwords[i])){
            printf("incorrect: expected: %s\n",randomwords[i]);
        }
    }
    for(int i = 0; i < arraysize; i++){
        free(randomwords[i]);
    }
    free(randomwords);


    destroy();
}