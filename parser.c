/*
 * lynn tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<ctype.h>
#include"functionalities.c"

#define MAX_LEN 1024
#define ARG_NUM 4
#define LEFT 1
#define RIGHT 2

char delimiters[] = {'>', '<', '&', '|'};
const char* list[] = {"cd", "help", "exit", "pwd"};

typedef struct commands {
    char* str;
    int length;
} commands;

typedef struct cmdline {
    commands cmd;
} cmdline;

typedef struct redirectCmd {
    int dir;
    commands cmd;
    char* file;
} redirectCmd;

typedef struct cdStruct {
    commands cmd;
} cdStruct;

typedef struct execStruct {
    commands cmd;
    char** argv;
} execStruct;

cdStruct cdCmd;
redirectCmd redirect;
execStruct execCmd;

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

void parseCommand(char* str) {
    char* curr = str;
    int index = 0;

    while (*curr) {
        while (*curr && isspace(*curr)) {
            curr++;
        }

        if (index > 0) {
            char* word = (char*) malloc(sizeof(char) * index);
        }

        /* Right redirection*/
        if (*curr == delimiters[0]) {
            redirect.dir = RIGHT;
            index = 0;
        }
        /* Left redirection*/
        else if (*curr == delimiters[1]) {
            redirect.dir = LEFT;
            index = 0;
        }
        /* Background jobs */
        else if (*curr == delimiters[2]) {
        }
        /* Pipes */
        else if (*curr == delimiters[3]) {
        }
        /* accumulate command */
        else {
        }

        /*
        int index = 0;
        while (*curr && strchr(curr, ' ')) {
            curr++;
            index++;

            printf("==%s\n", curr);
            char* result = (char*) malloc(sizeof(char) * index);
            printf("-=-%s    %d\n", str, index);
            strncpy(result, str, index);
            printf("---%s\n", result);
            printf("%s\n", curr);
        }
        */
        curr++;
    }
}

/*
 * Parse token based on delimiters. If delimiter is seen, the text will
 * be stored in struct appropriately
 */
void parse(char* str, cmdline line) {
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
    curr = str+line.cmd.length;
    /* TODO split by delimiters */
    parseCommand(curr);

    if (isBuiltinCommand(line.cmd) == 0) {
    }
}
