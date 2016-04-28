/*
 * lynn tran
 * Copyright (c) Lynn Tran 2014-2016
 * Description: Parser for shell program
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<errno.h>
#include<ctype.h>
#include"functionalities.c"
#include"parser.h"

/*
 * Read an input line of command
 */
char* readLine(char* str) {
    int ch;
    char* curr = str;
    while ((ch = getchar()) != '\n') {
        *curr++ = ch;
    }
    *curr = '\0';

    return str;
}

int isBuiltinCommand(const cmdline cmd) {
    NonTerminatedString firstArg = cmd.cmd[0];
    /* Command cd */
    if (strcmp(firstArg.str, list[0]) == 0) {
        assert(*cmd.cmd[1].str);

        cd(cmd.cmd[1].str);

        return 1;
    }
    /* Command help */
    else if (strcmp(firstArg.str, list[1]) == 0) {
        help();
        return 1;
    }
    /* Command exit */
    else if (strcmp(firstArg.str, list[2]) == 0) {
        exit(0);
    }
    /* Command pwd */
    else if (strcmp(firstArg.str, list[3]) == 0) {
        pwd();
        return 1;
    }

    return 0;
}

/*
 * Clear out the word buffer when seeing a delimiter
 */
void clearWordBuffer(char* word, int pos) {
    memset(word, 0, sizeof(char) * (pos-1));
}

/*
 * Add a new argument into the list of args
 */
void insertNewArg(NonTerminatedString* cmd, char* word, int pos) {
    assert(*word);
    cmd->str = (char*) malloc(pos+1);
    memcpy(cmd->str, word, pos);
    cmd->length = pos;
}

/*
 * Parse an argument from a line of commands.
 */
void parseArg(char* str, cmdline *cmd) {
    assert(*str);

    char *curr = (char*) malloc(MAX_LEN+1);
    strcpy(curr, str);
    unsigned int index = 0;
    unsigned int found = 0;
    unsigned int pos = 0;
    char* word = (char*) malloc(MAX_LEN+1);

    while (*curr) {
        if (index > MAX_COMMANDS) {
            errAndExit("Exceed the max number of arguments");
        }

        /* skip white space */
        while (*curr && isspace(*curr)) {
            if (found == 0 && word) {
                NonTerminatedString command;
                insertNewArg(&command, word, pos);

                cmd->cmd[index] = command;
                cmd->length++;
                index++;

                clearWordBuffer(word, pos);
                pos = 0;
                found = 1;
            }
            curr++;
        }
        found = 0;

        /* If it's delimiter, clear up word buffer and add to list of args,
         * else continue to read in character to form a word
         */
        switch (*curr) {
            case '|':
            case '<':
            case '>':
                {
                    NonTerminatedString command;
                    insertNewArg(&command, word, pos);
                    cmd->cmd[index] = command;
                    cmd->length++;

                    curr++;
                    index++;
                    clearWordBuffer(word, pos);
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

    if (*word)  {
        NonTerminatedString command;
        insertNewArg(&command, word, pos);

        cmd->cmd[index] = command;
        cmd->length++;
        index++;
    }

    free(word);
}

/*
 * Initialize parser
 */
void parse(char* str) {
    cmdline cmd;
    parseArg(str, &cmd);

    if (isBuiltinCommand(cmd) == 0) {
        execute(cmd);
    }
}
