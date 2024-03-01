#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

int number = *argv[1];


    if (number == 49) {
        printf("this is just a 1???");
    } else{
        printf("WOAH THATS NOT A 1!");
        printf("number: %d", number);
        return EXIT_FAILURE;
    }

    printf("we didnt even go in the if statement...");

    return 0;
}