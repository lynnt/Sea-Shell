/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include"functionalities.c"

#define MAX_LEN 1024
#define ARG_NUM 4

char delimiters[] = {'>', '<', '&', '|'};
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

typedef struct cdStruct {
    commands cmd;
} cdStruct;

cdStruct cdCmd;

char* readLine(char* str) {
    int ch;
    char* curr = str;
    while ((ch = getchar()) != '\n') {
        *curr++ = ch;
    }
    *curr = '\0';

    return str;
}

int isBuiltinCommand(const commands cmd) {
    /* Command cd */
    if (strcmp(cmd.str, list[0]) == 0) {
        cd(cdCmd.cmd.str);
        return 1;
    }
    /* Command help */
    else if (strcmp(cmd.str, list[1]) == 0) {
        help();
        return 1;
    }
    /* Command exit */
    else if (strcmp(cmd.str, list[2]) == 0) {
        exit(0);
    }
    /* Command pwd */
    else if (strcmp(cmd.str, list[3]) == 0) {
        pwd();
        return 1;
    }

    return 0;
}

void parseChar(char* str) {
    while (*str) {
        /*
        if (strcmp(*str, ' ') == 0) {
            // store string depending on command//
        }
    */
    }
}

void parse(const char* str, cmdline line) {
    char* curr = (char*) malloc(MAX_LEN+1);
    strcpy(curr, str);

    /*
     * Parse command
     */

    /* split words by space */
    line.cmd.str = (char*) malloc(MAX_LEN+1);
    curr = strtok(curr, " ");
    strcpy(line.cmd.str, curr);
    line.cmd.length = strlen(curr);

    /* update curr to start after the parsed word */
    curr = str+line.cmd.length+1;
    /* TODO split by delimiters */
    parseChar(curr);

    if (isBuiltinCommand(line.cmd) == 0) {
    }
}

int main (int argc, char** argv) {
    /* Test cases:
     * Get current dir: pwd
     * Go to dir: cd
     */
    cmdline cmd;

    while (1) {
        printf("~/SeaShell: ");
        char* line = (char*) malloc(MAX_LEN+1);
        line = readLine(line);

        if (line != NULL) {
            parse(line, cmd);
        }
    }
    return 0;
}
