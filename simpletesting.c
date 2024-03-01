#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

//print out the size of a file with stat
    struct stat buffer;
    int exist = stat(argv[1], &buffer);
    if (exist == 0) {
        printf("The file exists\n");
        printf("The size of the file is: %ld\n", buffer.st_size);
    } else {
        printf("The file does not exist\n");
    }
    return 0;
}