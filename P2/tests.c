#include<string.h>
#include<stdio.h>
#include "tries.h"
int main(int argc, char const *argv[])
{
    put("I am a string");
    if(exists("I am a string")){
        printf("it exists :-D\n");
    }
    destroy();
    return 0;
}
