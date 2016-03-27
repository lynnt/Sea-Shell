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
#define ARG_NUM 4

char delimiters[] = {'>', '<', '&'};
char* list[] = {"cd", "help", "exit", "pwd"};

typedef struct commands {
    char* str;
    int length;
} commands;

typedef struct cmdline {
    commands cmd;
} cmdline;

typedef struct redirectCmd {
    int dir; /* > or < */
    commands cmd;
    char* file;
} redirectCmd;

char* readLine(void) {
    char str[MAX_LEN + 1];
    int ch, i = 0;
    while ((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}

int isBuiltinCommand(const commands cmd) {
    int i;
    for (i = 0; i < ARG_NUM; ++i) {
        if (strcmp(cmd.str, list[i])) {
            return 1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

void parse(const char* str, cmdline line) {
    //char* curr = str;
    char* curr = (char*) malloc(MAX_LEN+1);
    strcpy(curr, str);
    int index = 0;

    /*
     * Parse command
     */

    /* split words by space */
    line.cmd.str = (char*) malloc(MAX_LEN+1);
    curr = strtok(curr, " ");
    strcpy(line.cmd.str, curr);
    line.cmd.length = strlen(curr);

    puts(str);
    if (isBuiltinCommand(line.cmd) == 0) {
        /* TODO split by delimiters */
        curr = str+line.cmd.length+1;
    }
}

int main (int argc, char** argv) {
    /* Test cases:
     * Get current dir: pwd
     * Go to dir: cd
     */
    cmdline cmd;

    while (1) {
        //TODO: Write a prompt like an actual shell
        char* line = readLine();

        if (line != NULL) {
            parse(line, cmd);
        }
    }
    return 0;
}
