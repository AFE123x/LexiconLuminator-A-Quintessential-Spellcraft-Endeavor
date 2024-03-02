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
    ARG_EMPTY,
};
static char* tolowercase(char* buffer){
    
}
void PRINTERR(enum ERROR_CODES error, char *value, char *argv[]) {
    switch (error) {
        case NOT_DIRECTORY:
            printf("Error: %s is not a directory. Make sure your path is correct\n", value);
            break;
        case NOT_FILE:
            printf("Error: %s is not a file. Make sure your path is correct\n", value);
            break;
        case ARG_EMPTY:
            printf("Error: The given argument(%s) is empty. You must provide an argument that is not empty\n", value);
            break;
    }
}

//call functions ahead of time
void DTE(char *arg);
void isEmpty(char *arg);



//function Does This Exist
//checks if the given file or directory exists
void DTE(char *arg) {
    struct stat buffer;
    int exist = stat(arg, &buffer);
    if (exist == 0) {
        printf("The file exists\n");
        isEmpty(arg);
    } else {
        printf("The file or directory %s does not exist\n", arg);
        exit(EXIT_FAILURE);
    }
}

//function that checks if given directory is empty
void isEmpty(char *arg) {
    struct stat buffer;
    stat(arg, &buffer);
        //check if the passed in argument is a file or a directory
        if (S_ISDIR(buffer.st_mode)) {
            if (buffer.st_size == 2) {
                PRINTERR(ARG_EMPTY, arg, NULL);
               //printf("the dir is empty\n");
                exit(EXIT_FAILURE);
            }
            //make some form of directory handeling here
            //probably pass into another function that will run through all the files in the directory

        }

        if (S_ISREG(buffer.st_mode)) {
            if (buffer.st_size == 0) {
                PRINTERR(ARG_EMPTY, arg, NULL);
                //printf("the file is empty\n");
                exit(EXIT_FAILURE);
            }
            //make some form of file handeling here
            //will pass to another function that reads the file and compares it with the dictionary



        }
        // printf("directory size is: %ld\n", buffer.st_size);
        // printf("The Directory is not empty\n");
}

//do we have to check and make sure if they are anything other than directory or file? probably


int main(int argc, char *argv[]) {

    //if argc is less than 2, print error message and return 1
    if (argc <= 2) {
        printf("Usage: spchk <Dictionary Path> <Directory1 or File1 Path> <Directory2 or File2 Path> ... <DirectoryN or FileN Path>\n");
        return 1;
    }
    //if argc is = 2, that means the passed in argument SHOULD be a directory
    //check if the file is a directory
    //this code is from when I did not fully understand the assignment I realize
    // I thought we were only checking for directories
    // if (argc == 2) {
    //     //check if the given argument is a directory
    //     isDirectory(argv[1]);
    //     //check if the directory is empty
    //     isEmpty(argv[1]);


    //     exit(EXIT_SUCCESS);
    // }



    //argv[0] is the name of the program
    //argv[1] is the dictionary
    //argv[2+] is a directory or file
    if (argc > 2) {

        //iterate through the arguments passed in
        for (int i = 0; i < argc-1; i++) {
            //check if the given arguments are valid directories or files AND if they are empty
            DTE(argv[i+1]);
        }
        //print how many files there are
        printf("There were %d files passed into the program\n", argc-1);

        //we COULD make it where if the first argument is proven to be a directory
        //we dont require the user to put the path to the next file, but just the name of the file instead.
        //I believe that would require some file appending skills though.

        struct stat s;
    }




    return 0;
}   

// ⢳⠀⠀⠀⡴⠀⠀⢀⠀⠀⣠⣴⣿⣿⣯⠄⠀⢀⠀⠀⠀⠀⡟⠻⠿⠟⠛⠢⡜⠓⠠⢤⠞⠻⣶⣤⡀⠀⢒⢶⠀⢠⠂⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⣰⠁⣴⠞⢿⠹⠏⠡⠞⣿⣿⣿⠟⠉⠉⠑⠦⠤⠊⠁⠀⠀⠀⠀⠀⠱⡄⠀⢨⣄⠀⢈⣿⣝⢷⣄⡸⢀⡝⠁⠀⠀⠀⠀⠀⠀⠤
// ⠀⠀⠠⠃⠀⣧⠖⠋⠑⡶⣤⡞⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠘⠒⠉⠉⠳⣾⣿⣿⠷⣽⢃⡞⠁⠀⠀⠀⠀⠀⠀⠀⠐
// ⠀⢀⠆⠀⢸⡧⢄⡠⠔⠁⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣦⠀⠀⠀⠀⠀⠀⢢⡀⠀⠈⢻⡅⢠⣿⠟⢻⠶⣄⠘⡷⠀⠀⠀⠀⠀
// ⠶⠛⠋⣰⡿⠀⢀⡟⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣟⢷⡄⠀⠀⠀⠀⠀⠱⡄⠀⠀⣹⣿⢺⠀⢀⣄⣾⡈⠁⢠⣄⡀⠀⠀
// ⡀⠀⢠⣿⣿⣷⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣠⡹⣦⣤⣤⣤⣤⣶⣿⡟⠚⠁⠘⣄⣹⣧⣄⠈⣷⠀⠃⠈⠂⠀⠀
// ⠀⠀⣼⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⣁⡀⢹⣿⡟⠋⠉⠙⠻⡏⠀⠀⠘⣿⣿⡿⠿⣿⣧⡀⠀⠀⠈⠒
// ⡄⠀⣟⢀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣯⠙⠛⠛⠛⠓⢶⡦⠽⣄⣳⠀⠀⠠⣿⣿⣧⡀⣿⣯⣿⣄⠉⠉⠉
// ⡶⠛⣉⡻⠀⠀⠀⠀⠐⠁⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠙⢦⡈⢻⡇⠀⠀⢿⣿⢿⣷⣿⡟⣻⣿⣆⠀⣄
// ⠳⣎⠁⡇⠀⠀⠀⠀⢰⠀⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀⠀⠀⠀⠀⠀⣾⠀⠀⡠⠀⣀⣀⣀⣀⣈⣓⣷⠀⠀⠈⢿⣦⣿⣿⣿⣿⣿⡜⣆⠃
// ⠉⠛⢻⡀⠀⠀⠀⠀⢸⠀⠀⠀⣇⠀⠀⠀⠀⠘⣧⠀⠀⠀⠀⠀⠀⢹⡇⢴⣿⣿⣛⣿⣿⣿⣿⣿⣿⡇⡀⠀⢸⣽⣿⣿⣿⣮⣿⣿⣹⣶
// ⠀⠀⡾⠀⠀⠀⠀⠀⠀⡇⠀⠀⢹⡀⠀⠀⠀⠀⢿⡄⡀⠀⠀⠀⠀⣸⡇⠉⠙⠁⠀⠀⠉⠁⠁⠀⠈⡇⡇⠀⠘⣿⢿⣿⣿⠟⠛⢿⣿⣿
// ⠀⠀⡇⠀⠀⠀⠀⠀⠀⡇⠀⠀⠈⣧⠀⠀⠀⠀⢼⠻⣷⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡇⠀⣼⡇⣀⣽⢿⣆⠀⢸⠀⡿
// ⠂⠀⢸⠀⠀⡆⠀⠀⠀⢹⠀⠀⠀⢹⣆⠀⠀⠀⢸⣇⢻⣷⡀⣠⠞⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠇⠀⣿⡷⠛⡿⢸⠈⠑⣶⣄⠀
// ⠀⠀⢸⡀⠀⣧⠀⠀⠀⢘⣇⠀⠀⠀⢟⢦⢦⠀⠀⢻⡄⠹⡄⠙⠗⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⢰⡯⠤⠚⢁⡿⢳⠀⠈⣿⣷
// ⠀⠀⠀⡇⠀⢸⡀⡆⠀⠘⣿⢦⡄⠀⠘⡄⠙⢷⡤⠤⠽⣦⠃⠀⠀⠀⣀⣀⣄⡀⠀⠀⠀⠀⠀⠀⣼⡏⢠⢿⠁⢀⠞⠁⠀⢸⠀⢀⠈⠋
// ⡀⠀⠀⢹⡀⢸⣧⣰⡀⠀⠹⣆⠙⢦⣀⠙⣄⠀⠉⠀⠀⠀⢀⣤⣾⣽⣾⣿⣿⡏⣷⡄⠀⠀⠀⢰⢛⡷⠃⣼⡟⢹⠀⠀⠀⢸⡆⢨⣤⡴
// ⠈⠁⠀⢸⢳⠀⣿⡷⣷⣄⠀⠙⣄⠀⠉⠉⠉⠒⠀⠀⠀⠀⣾⣿⠿⠛⠉⠉⠉⠃⠙⢿⠀⠀⠀⢃⡜⠁⣰⣿⣇⡎⠀⠀⢣⣿⢀⠟⠉⠀
// ⠀⠀⠀⢸⢀⣧⢹⡇⠈⢻⣷⠤⣈⢦⡀⠀⠀⠀⠀⠀⠀⠀⢻⡏⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠘⠁⠀⣰⣿⣿⣾⣷⠒⢦⣿⠟⠁⠀⠀⠀
// ⠠⢤⣤⣼⢸⣀⡙⢳⡄⠀⠹⡇⠀⠙⣿⠦⠀⠀⠀⠀⠀⠀⠘⣧⡀⠀⠀⠀⠀⠀⣠⠇⠀⠀⠀⢀⣾⣿⣿⣿⣿⣾⠀⣀⢳⣤⠊⠀⠀⠠
// ⠀⠀⠀⠉⢿⢛⣿⣿⣿⣧⣀⢻⣤⠀⢹⣦⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠉⠀⠀⢀⡴⢛⣿⣿⣿⣻⡿⠙⡆⡼⠀⠙⣄⠀⠀⠀
// ⠀⠀⠀⠀⡸⠋⢱⠀⠙⢿⡏⠳⢿⣷⣄⠻⣿⣦⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠾⠋⢀⣾⡄⠠⠈⡇⡇⠀⢹⠁⠀⠀⠈⠣⢄⠀
// ⠀⠀⢀⠜⠁⠀⣼⡇⠀⢀⠟⢆⠀⠹⡟⠛⢾⣛⠉⠹⡙⠛⠛⠿⣶⣲⠶⢦⡤⠴⣿⠋⠀⠀⣿⠗⢺⡀⢧⡇⠣⣀⣈⣹⣾⡄⠀⠀⠀⠑
// ⠀⠀⠀⠀⠀⢀⠟⢳⠀⠪⣀⡤⣱⣄⣽⡄⠀⠈⠙⠒⠒⠲⣶⣄⡀⠈⠛⢾⣷⣼⢃⣀⣴⠾⠋⠓⠢⢷⣈⡟⢲⡈⠉⠀⠘⡇⠀⠀⠀⠀
// ⠀⠀⠀⠀⢠⠊⠀⡯⠀⠀⠀⡇⠀⠀⠹⣰⠀⠀⠀⠀⠀⠀⢀⣹⣿⠿⠿⢿⣿⣿⡏⠛⢿⣦⡀⠀⠀⠀⠉⠳⣄⡱⡄⠀⠀⠳⡀⠀⠀⠀