//Netids: Arun ajf227 , Kareem kkj47
//No idea what includes we'll need so im just including everything
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//function that checks if given value is a directory

//function that checks if given value is a file

//do we have to check and make sure if they are anything other than directory or file? probably


int main(int argc, char *argv[]) {

    //if argc is less than 2, print error message and return 1
    if (argc < 2) {
        printf("Usage: spchk <Directory>\n or spchk <Directory> <File1> <File2> ... <FileN>\n");
        return 1;
    }
    //if argc is = 2, that means the passed in argument SHOULD be a directory
    //check if the file is a directory
    if (argc == 2) {
        //check if the given argument is a directory
        return 0;
    }

    //if argc is > 2, that means the first argument is a directory
    //the following arguments are files
    if (argc > 2) {
        //check if the first argument is a directory
        struct stat s;
    }



    return 0;
}   

