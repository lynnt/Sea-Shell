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
typedef struct commands {
    char str[MAX_LEN+1];
    int length;
} commands;

typedef struct cmdline {
    commands cmd;
} cmdline;

char* readLine(void) {
    char str[MAX_LEN + 1];
    int ch, i = 0;
    while ((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}

int isBuiltinCommand(commands cmd) {
    char* str = cmd.str;
    if (strcmp(str, "cd")) {
        return 1;
    }
    else if (strcmp(str, "pwd")) {
        return 1;
    }
    else {
        return 0;
    }
    return 0;
}

void parse(char* str, cmdline line) {
    char* curr = str;
    int index = 0;

    /*
     * Parse command
     */

    /* split by space */
    curr = strtok(str, " ");

    while (*curr) {
        if (index < MAX_LEN) {
            line.cmd.str[index] = *curr;
            printf("%c\n", line.cmd.str[index]);
            index += 1;
        }
        curr++;
    }
    line.cmd.str[index] = '\0';
    line.cmd.length = index;

    if (isBuiltinCommand(line.cmd) == 0) {
        // split by delimiters
    }
}

int main (int argc, char** argv) {
    /* Test cases:
     * Get current dir: pwd
     * Go to dir: cd
     */
    cmdline cmd;

    while (1) {
        char* line = readLine();

        if (line != NULL) {
            parse(line, cmd);
        }
    }
    return 0;
}
