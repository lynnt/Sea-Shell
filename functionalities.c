/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
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

#define MAX_LEN 1024
#define LEFT 1
#define RIGHT 2

void errAndExit(const char* msg) {
    perror(msg);
    exit(-1);
}

void errMsg(const char* msg) {
    perror(msg);
}

void changePath(char* path) {
    if (chdir(path) == 0) {
        printf ("Changed the directory\n");
    }
    else {
        errAndExit("Can't change the directory. Check your path if it exists");
    }
}

void cd (char* path) {
    if (path == NULL) {
        errMsg("Currently not supported");
    }
    else {
        changePath(path);
    }
}

void pwd() {
    char* buffer = (char*) malloc(MAX_LEN+1);
    if (getcwd(buffer, sizeof(char) * (MAX_LEN+1)) == NULL){
        errMsg("Cant get the current directory");
    }

    puts(buffer);
}

void executingProgram(const char* command, char** const argv) {
    /* Executing other programs like ls/cd/etc.. */
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

/* TODO: Delete this */
int inputRedirection(char* argv[], int length) {
    /* Redirect the input/output when seeing the arrows */
    int i;
    for (i = 0; i < length-1; i++) {
        if (strcmp(argv[i], "<") == 0) {
            return i;
        }
    }
    return -1;
}

/* TODO: Delete this */
int outputRedirection(char* argv[], int length) {
    /* Redirect the input/output when seeing the arrows */
    int i;
    for (i = 0; i < length-1; i++) {
        if (strcmp(argv[i], ">") == 0) {
            return i;
        }
    }
    return -1;
}

void redirection(char* file, int direction, int length) {
    if (file) {
        errMsg("There is no file");
        return;
    }

    if (direction == LEFT) {
        int fileDescriptor = open(file, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        /* execute the command */
    }
    else if (direction == RIGHT) {
        int fileDescriptor = open(file, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

        if (fileDescriptor == -1) {
            errMsg("Can't open output file " + *file);
            return;
        }

        /* redirect the stream to the file. Value 1 in 2nd argument is new
         * file descriptor */
        if (dup2(fileDescriptor, 1) < 0) {
            errMsg("Can't redirect into file" + *file);
            return;
        }

        /* execute the command */
    }
}

/*
 * Run programs in the background with a '&' at the end of the command while the background command is being executed
 * */
void backgroundProcess() {
}

/* TODO */
void help() {}

/*
int main(int argc, char** argv) {
     * loop continously until read in a termination symbol
    char* cwd = malloc(sizeof(char));
    //int* numberOfArgs = malloc(sizeof(int));
    while(1){
        getCurrentWorkingDirectory();
        fgets(cwd, sizeof(cwd), stdin);
        //    parse(cwd, argv, argc, nargs);
    }
    //  char* args[] = {"ls", "-l", ">", "foo.txt"};
    //  redirection(args, 4);
    free(cwd);
    return 0;
}
*/
