/*
used to parse a given dictionary file for each of its words
*/



#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include "./tries.h"
static int fd;

static char* getword(){
    int initsize = 8;
    char* mystring = (char*)malloc(sizeof(char) * initsize);
    char c[1]; 
    int reada = read(fd,c,1);
    int i = 0;

    while(c[0] != '\n' && reada > 0){ 
        mystring[i++] = c[0];
        if(i >= (initsize / 2)){
            char* newstring = realloc(mystring,initsize * 2);
            initsize *= 2;
            if(newstring == NULL){
                fprintf(stderr,"realloc failed\n");
                free(mystring);
                exit(EXIT_FAILURE);
            }
            mystring = newstring;

        }
        reada = read(fd,c,1);
    }
    if(i == 0){
        printf("no string read\n");
        free(mystring);
        return NULL;
    }
    mystring[i++] = '\0';
    char* newstring = realloc(mystring,i);
    if(newstring == NULL){
        fprintf(stderr,"unable to realloc string\n");
        free(mystring);
        exit(EXIT_FAILURE);
    }
    mystring = newstring;
    return mystring;
}
void parsedict(char* filepath){
    fd = open(filepath,O_RDONLY);
     if(fd == -1){
        perror("unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char* mystring = getword();
    int i = 0;

    while(mystring != NULL){
        printf("iteration %d: %s\n",i++,mystring);
        put(mystring);

        free(mystring);
        mystring = getword();
    }

}

void parsefile(char* filepath) {
    //we want to seperate each word in the file
    //we will use the space as the delimiter
    //pass each word into the trie for comparison

    //open the file
    fd = open(filepath,O_RDONLY);

    //print error message and exit if the file is not found
    //this shouldnt even happen in the first place
    if(fd == -1){
        perror("unable to open file\n");
        exit(EXIT_FAILURE);
    }
    
    //read each word in the file
    //using a 2D array to store each word
    char word[1000][100];

}

