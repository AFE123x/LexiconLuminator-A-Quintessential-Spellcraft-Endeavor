/*
Contains the functions used to parse a file or parse a dictionary

|parsedict| - parses a dictionary file and adds each word to the trie
|parsefile| - parses a file and checks each word against the trie
*/



#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include "./tries.h"
static int fd;
void printstring(char* buffer, int size){
    for(int i = 0; i < size ; i++){
        printf("%c",buffer[i]);
    }
    printf("\n");
}

static char* getword() {
    int initsize = 8;
    char* mystring = (char*)malloc(sizeof(char) * initsize);
    char c[1]; 
    int reada = read(fd, c, 1);

    while ((c[0] == ' ' || c[0] == '\n') && reada != 0) {
    reada = read(fd, c, 1);
    }

    int i = 0;
    
    unsigned int row = 1;
    unsigned int col = 0;

    while (c[0] != '\n' && c[0] != ' ' && reada > 0) { 
        mystring[i++] = c[0];

        col++;

        //realloc the string if it is half full
        if (i >= (initsize / 2)) {
            char* newstring = realloc(mystring, initsize * 2);
            initsize *= 2;
            //free mystring if realloc fails
            if (newstring == NULL) {
                fprintf(stderr, "realloc failed\n");
                free(mystring);
                exit(EXIT_FAILURE);
            }

            //give mystring the newstring's allocation
            mystring = newstring;
        }

        // printstring(mystring,i);
        // Read the next character
        reada = read(fd, c, 1);
        
        // Check if the next character is a newline or space
        if (c[0] == '\n' || c[0] == ' ') {
            // If it is, stop reading and break out of the loop
            break;
        }
    }

    if (i == 0) {
        printf("---File Read Complete---\n");
        free(mystring);
        return NULL;
    }
    
    mystring[i++] = '\0';
    char* newstring = realloc(mystring, i);
    if (newstring == NULL) {
        fprintf(stderr, "unable to realloc string\n");
        free(mystring);
        exit(EXIT_FAILURE);
    }
    mystring = newstring;
    //printf("row: %d col: %d\n", row, col);
    return mystring;
}


//parses a dictionary file and adds each word to the trie
void parsedict(char* filepath){
    fd = open(filepath,O_RDONLY);
     if(fd == -1){
        perror("unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char* mystring = getword();
    //int i = 0;

    while(mystring != NULL){
        //printf("iteration %d: %s\n",i++,mystring);
        put(mystring);

        free(mystring);
        mystring = getword();
    }

}

// parses a file and checks each word against the trie
void parsefile(char* filepath) {
    //we want to separate each word in the file
    //we will use the space as the delimiter
    //pass each word into the trie for comparison

    //open the file
    fd = open(filepath,O_RDONLY);

    //print error message and exit if the file is not found
    //this shouldn't even happen in the first place
    if(fd == -1){
        perror("unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char* mystring = getword();
    //while we are not at the end of the file (0 is provided when the file ends)
    while(mystring != NULL){
            if(!exists(mystring)){
                printf("%s (row?,col?): %s\n",filepath, mystring);
            }
            free(mystring);
        mystring = getword();
    }

}



