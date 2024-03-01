//Netids: Arun ajf227 , Kareem kkj47
//No idea what includes we'll need so im just including everything
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//Error handling for cases with directory
//Might include some for different file types
enum ERROR_CODES {
    NOT_DIRECTORY,
    NOT_FILE,
    DIRECTORY_EMPTY,
    FILE_EMPTY,
};

void PRINTERR(enum ERROR_CODES error, char *value, char *argv[]) {
    switch (error) {
        case NOT_DIRECTORY:
            printf("Error: %s is not a directory. Make sure your path is correct\n", value);
            break;
        case NOT_FILE:
            printf("Error: %s is not a file. Make sure your path is correct\n", value);
            break;
        case DIRECTORY_EMPTY:
            printf("Error: %s is an empty directory. Your directory must have at least 1 file in it.\n", value);
            break;
        case FILE_EMPTY:
            //technically this error can happen but still keep the program running
            printf("Error: %s is an empty file. An empty file has nothing to be read.\n", value);
            break;
    }
}


//function that checks if given value is a directory
void isDirectory(char *dir) {
    struct stat buffer;

    //first check if the directory exists
    int exist = stat(dir, &buffer);
    if (exist == 0) {
        // printf("The Directory exists\n");
        return;
    } else {
        PRINTERR(NOT_DIRECTORY, dir, NULL);
        exit(EXIT_FAILURE);
    }

}

//function that checks if given directory is empty
void isDirectoryEmpty(char *dir) {
    struct stat buffer;
        //check if the directory is empty
        if (buffer.st_size == 2) {
            PRINTERR(DIRECTORY_EMPTY, dir, NULL);
            exit(EXIT_FAILURE);
        }
        // printf("directory size is: %ld\n", buffer.st_size);
        // printf("The Directory is not empty\n");
}

//function that checks if given value is a file

void isFile(char *file) {
    struct stat buffer;
}


//do we have to check and make sure if they are anything other than directory or file? probably


int main(int argc, char *argv[]) {

    //if argc is less than 2, print error message and return 1
    if (argc < 2) {
        printf("Usage: spchk <Directory Path> or spchk <Directory Path> <File1 Path> <File2 Path> ... <FileN Path>\n");
        return 1;
    }
    //if argc is = 2, that means the passed in argument SHOULD be a directory
    //check if the file is a directory
    if (argc == 2) {
        //check if the given argument is a directory
        isDirectory(argv[1]);
        //check if the directory is empty
        isDirectoryEmpty(argv[1]);


        exit(EXIT_SUCCESS);
    }

    //if argc is > 2, that means the first argument is a directory
    //the following arguments are files
    if (argc > 2) {
        //check if the first argument is a directory
        isDirectory(argv[1]);
        //we COULD make it where if the first argument is proven to be a directory
        //we dont require the user to put the path to the next file, but just the name of the file instead.
        //I believe that would require some file appending skills though.

        struct stat s;
    }




    return 0;
}   

