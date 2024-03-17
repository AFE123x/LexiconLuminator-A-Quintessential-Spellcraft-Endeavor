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

//tracks if the first word of the row has been read
short firstWord = 0;
//just a variable to check if the VERY FIRST word in the file has been read
short veryfirst = 0;
//this is actively counting the rows with every \n
unsigned int row = 1;
//this actively counts the col with the chars (should have named charcount)
unsigned int colcount = 1;
//this is holds col value for the beginning of a word
unsigned int colwrds = 1;
//this is the row value stored for as soon as the row switches
unsigned int activerow = 1;

//*colwp actively updates the col value for the beginning of a word
//why not just print the active col number? because it would be wrong
//our print statement prints AFTER a word is read. meaning it would get the col value after the word is read as well
//so we have a pointer pointing to the value of the beginning of words
unsigned int *colwp = &colwrds;
unsigned int *rowp = &activerow;


//prints the string
void printstring(char* buffer, int size){
    for(int i = 0; i < size ; i++){
        printf("%c",buffer[i]);
    }
    printf("\n");
}


//gets the word SPECIFICALLY for the parsefile function
static char* getword() {
    int initsize = 8;
    char* mystring = (char*)malloc(sizeof(char) * initsize);
    char c[1]; 
    int reada = read(fd, c, 1);

    while ((c[0] == ' ' || c[0] == '\n') && reada != 0) {
        reada = read(fd, c, 1);
        colcount++;
        if (c[0] == ' ' || c[0] == '\n') {
            if (c[0] == '\n') {
                row++;
                colcount = -1; //this could bite me in the butt later...
            }
            *colwp = colcount+2;
            firstWord = 0;
        }

    }

    if (firstWord == 1) {
        //printf value of colcount
        *rowp = row;
        printf("col value: %d\n", colcount);
        *colwp = colcount+1;
    }

    int i = 0;
    // outside++;
    // printf("outside = wordcount: %d\n", outside);


    while (c[0] != '\n' && c[0] != ' ' && reada > 0) { 
        mystring[i++] = c[0];
        colcount++;
        if (veryfirst == 0) {
            *colwp = colcount-1;
            veryfirst = 1;
            *rowp = row;
        }
        printf("inside: %d\n", colcount);
        //printf("inside\n");
        
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
        if (firstWord == 4) {
            if (c[0] == ' ') {
                *colwp = colcount+2;
                //printf("col value after space: %d\n", *colwp);
            } else if (c[0] == '\n') {
                    //printf("new line inside\n");
                    colcount = 0;
                    firstWord = 0;
                    //*colwp = 0;
                    //print the column has been reset
                    //printf("col reset\n");
            }
        }
        // Check if the next character is a newline or space
        if (c[0] == '\n' || c[0] == ' ') {
            firstWord = 1;
            if (c[0] == '\n') {
                colcount = 0;
                row++;
            }

            // If it is, stop reading and break out of the loop
            break;
        }
    }

    //prints when we reach the end of a file
    if (i == 0) {
        printf("---File Read Complete---\n");
        free(mystring);
        return NULL;
    }
    

    //for the case that we run out of memory somehow
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

//function that gets the word size for parsedict specifically
//originally the parsedict and parsefile were using the same getword function
//it was changed for column and row counting to work
//DO NOT TOUCH
static char* getwordfordict() {
    int initsize = 8;
    char* mystring = (char*)malloc(sizeof(char) * initsize);
    char c[1]; 
    int reada = read(fd, c, 1);


    while ((c[0] == ' ' || c[0] == '\n') && reada != 0) {
    reada = read(fd, c, 1);
    }


    int i = 0;
    while (c[0] != '\n' && c[0] != ' ' && reada > 0) { 
        mystring[i++] = c[0];
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
        printf("---Dict Read Complete---\n");
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
    return mystring;
}


//parses a dictionary file and adds each word to the trie
void parsedict(char* filepath){
    fd = open(filepath,O_RDONLY);
     if(fd == -1){
        perror("unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char* mystring = getwordfordict();
    //int i = 0;

    while(mystring != NULL){
        put(mystring);
        free(mystring);
        mystring = getwordfordict();
    }
}

// parses a file and checks each word against the trie
void parsefile(char* filepath) {
    //we want to separate each word in the file
    //we will use the space as the delimiter
    //pass each word into the trie for comparison

    //column number gets reset
    row = 1;

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
            //printf("correct string: %s\n",get(mystring));
            if(!exists(mystring)){

                printf("%s (row: %d,col: %d): %s\n",filepath, *rowp, *colwp, mystring);
                //printf("row: %d col: %d\n", row, colcount);
            }
            free(mystring);   
        mystring = getword();
    }

}



