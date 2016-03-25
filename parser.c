/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

#define MAX_LEN 1024
char delimiters[] = {' ', '/'};
typedef struct command {
    char* str;
    int length;
} command;

char* parseCommand(char str[], char* commands[]){
    char* curr = NULL;
    curr = strtok(str, delimiters);
    int index = 0;
    /* iterate over the string until you find the null terminated string */
    while(curr != NULL){
        printf("%s\n", curr);
        if(index < 1024){
            commands[index] = curr;
            index += strlen(curr);
            printf("%s\n", commands[index]);
            //printf("%d\n", index);
            /*
               if(strcmp(ptr, "<") == 0){
               printf("Found");
               return "redirect";
               }
               */
        }
        else{
            //TODO: Realloc the array size
            perror("Can't realloc");
        }
    }
    return NULL;
}

char* parseCmd(char* str) {
    char* curr = str;
    // split by space
    // split by delimiters
    // check out if it's a command exists
    while (*curr != NULL) {
        printf("%c\n", *curr);
        curr++;
    }
}

char* readLine(void) {
    char str[MAX_LEN + 1];
    int ch, i = 0;
    while ((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}

int main (int argc, char** argv) {
    char* line;
    while (1) {
        line = readLine();

        if (line != NULL) {
            parseCmd(line);
        }
    }
    return 0;
}
