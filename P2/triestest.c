#include "tries.h"
#include<stdio.h>

int main(int argc, char** argv){
    put("String one");
    put("String two");
    if(exists("String one")){
        printf("String one exists\n");
    }
    if(exists("String two")){
        printf("String two also exists\n");
    }
    if(!exists("String")){
        printf("string doesn't exist\n");
    }
    put("String");
    if(exists("String")){
        printf("string now exists\n");
    }
    if(!exists("Str")){
        printf("this shouldn't exist\n");
    }
}