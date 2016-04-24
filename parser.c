/*
 * lynn tran
 * Copyright (c) Lynn Tran 2014-2016
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<ctype.h>
#include"functionalities.c"
#include"parser.h"

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
        cdStruct cdCmd;
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

void clearBuffer(char* word, int pos) {
    memset(word, 0, sizeof(word));
}

void insertNewArg(commands* cmd, char* word) {
    if (word) {
        cmd->str = word;
        cmd->length = strlen(word);
    }
}

void parseArg(char* str, cmdline *cmd) {
    char *curr = (char*) malloc(MAX_LEN+1);
    strcpy(curr, str);
    int index = 0;
    int found = 0;
    int pos = 0;
    char* word = (char*) malloc(MAX_LEN+1);

    while (*curr) {
        if (index > MAX_COMMANDS) {
            errAndExit("Exceed the max number of arguments");
        }

        /* skip white space */
        while (*curr && isspace(*curr)) {
            if (found == 0) {
                commands command;
                cmd->cmd[index] = command;
                cmd->length++;
                insertNewArg(&command, word);

                clearBuffer(word, pos);
                pos = 0;
            }
            found = 1;
            curr++;
        }
        found = 0;

        switch (*curr) {
            case '|':
            case '<':
            case '>':
                {
                    commands command;
                    cmd->cmd[index] = command;
                    cmd->length++;
                    insertNewArg(&command, word);
                    curr++;
                    clearBuffer(word, pos);
                    pos = 0;
                    break;
                }
            default:
                {
                    word[pos] = *curr;
                    pos++;
                    curr++;
                    break;
                }
        }
    }

    if (word)  {
        printf("%s\n", word);
        commands command;
        cmd->cmd[index] = command;
        cmd->length++;
        insertNewArg(&command, word);
    }
    free(word);
}

void parse(char* str) {
    cmdline cmd;
    parseArg(str, &cmd);

    int i;
    for (i = 0; i < cmd.length; i++) {
        printf("%s\n", cmd.cmd[i].str);
    }
}
