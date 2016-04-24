/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014 - 2016
 * Description: This is a shell program
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.c"

int main (int argc, char** argv) {
    /* Test cases:
     * Get current dir: pwd
     * Go to dir: cd
     * Redirection:
     * ls -ls > foo.txx
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
