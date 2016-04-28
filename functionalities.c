/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014-2016
 * Description: This is a shell program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* Get the linux commands */
#include <errno.h> /* Return errors */
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h> /* include PATH_MAX */
#include "common.h" /* Contains common structs */

void errAndExit(const char* msg) {
    perror(msg);
    exit(-1);
}

void errMsg(const char* msg) {
    perror(msg);
}

void pwd() {
    char* buffer = (char*) malloc(MAX_LEN+1);
    if (getcwd(buffer, sizeof(char) * (MAX_LEN+1)) == NULL){
        errMsg("Cant get the current directory");
        return;
    }

    puts(buffer);
}

void changePath(char* path) {
    if (chdir(path) == 0) {
        pwd();
    }
    else {
        errMsg("Can't change the directory. Check your path if it exists");
        return;
    }
}

void cd(char* path) {
    if (!*path) {
        errMsg("Currently not supported");
        return;
    }
    else {
        changePath(path);
    }
}

void executeProgram(char* command, char** argv) {
    pid_t childPID;
    int status;

    childPID = fork();
    if (childPID == 0) {
        if (execvp(command, argv) < 0) {
            errAndExit("Failed to execute the command");
        }
        else {
            puts("Executed the command");
        }
    }
    else if (childPID > 0) {
        waitpid(childPID, &status, WNOHANG);
    }
    else {
        errAndExit("Can't get to the child process");
    }
}

void execute(cmdline cmd) {
    /* Executing other programs like ls/cd/etc.. */
    if (redirect == 0) {
        // executeProgram();
    }
    else {
        // redirection(file, direction, argv);
    }
}

void redirection(char* file, Direction direction, char** argv) {
    if (!file) {
        errMsg("There is no file");
        return;
    }

    if (direction == LEFT) {
        int fileDescriptor = open(file, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

        if (fileDescriptor == -1) {
            errMsg("Can't open output file " + *file);
            return;
        }

        /* redirect the stream */
        if (dup2(fileDescriptor, STDIN_FILENO) < 0) {
            errMsg("Can't redirect into file" + *file);
            return;
        }

        /* execute the command */
        //executeProgram();

        close(fileDescriptor);
    }
    else if (direction == RIGHT) {
        int fileDescriptor = creat(file, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

        if (fileDescriptor == -1) {
            errMsg("Can't open output file " + *file);
            return;
        }

        /* redirect the stream */
        if (dup2(fileDescriptor, STDOUT_FILENO) < 0) {
            errMsg("Can't redirect into file" + *file);
            return;
        }

        /* execute the command */
        //executeProgram();

        close(fileDescriptor);
    }
}

/*
 * Run programs in the background with a '&' at the end of the command while the background command is being executed
 * */
void backgroundProcess() {
    /* TODO: waitpid(pid, status, options) */
}

/* TODO */
void help() {}
