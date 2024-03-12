/*
used to parse a given dictionary file for each of its words
*/



#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int fd;

char* getword(){
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
int main(int argc, const char** argv){\
    
    if(argc < 2){
        fprintf(stderr,"./parser {dictionary file name}\n");
        return EXIT_FAILURE;
    }

    fd = open(argv[1],O_RDONLY);
    
    if(fd == -1){
        perror("unable to open file\n");
        return EXIT_FAILURE;
    }

    char* mystring = getword();
    int i = 0;

    while(mystring != NULL){
        printf("iteration %d: %s\n",i++,mystring);
        free(mystring);
        mystring = getword();
    }

    return EXIT_SUCCESS;
}