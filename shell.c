/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: This is a shell program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //Get the linux commands
#include <errno.h> //Return errors
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h> //include PATH_MAX
#include "parser.c"

void cd (char* path) {
  //Change directory using chdir
  //get current dir
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    if (path != cwd) {
      printf ("Attempting to change directory\n");
      if (chdir(path) == 0) {
        printf ("Changed the directory\n");
      }
      else {
        perror ("Can't change the directory. Check your path if it exits");
      }
    }
  }
  else {
    perror ("Can't get the current directory");
  }
}

void getCurrentWorkingDirectory() {
  char buffer[PATH_MAX + 1];
  if (getcwd(buffer, sizeof(buffer)) == NULL){
    perror("Can't get the current directory");
    return -1;
  }
  printf("%s ", buffer);
  exit(0);
}

void executingProgram(const char* command, char* const argv[]) {
  //Executing other programs like ls/cd/etc..
  pid_t childPID;
  int* status = NULL;

  childPID = fork();
  if (childPID == 0) {
    if (execvp(command, argv) < 0) {
      perror ("Failed to execute the command");
    }
    else {
      printf ("Executed the command");
    }
  }
  else if (childPID > 0) {
    waitpid(childPID, status, WNOHANG);
  }
  else {
    perror ("Can't get to the child process");
    exit(0);
  }
}

int inputRedirection(char* argv[], int length) {
  //Redirect the input/output when seeing the arrows
  int i;
  for (i = 0; i < length-1; i++) {
    if (strcmp(argv[i], "<")) {
      return i;
    }
  }
  return -1;
}

int outputRedirection(char* argv[], int length) {
  //Redirect the input/output when seeing the arrows
  int i;
  for (i = 0; i < length-1; i++) {
    if (strcmp(argv[i], ">") == 0) {
      return i;
    }
  }
  return -1;
}

void redirection(char* argv[], int length) {
  int i, j;
  int output = outputRedirection(argv, length);
  int input = inputRedirection(argv, length);
  int newLength = 0;
  char* args[256];

  if (output != -1) {
    int fileDescriptor = open(argv[length-1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (fileDescriptor < 0) {
      perror(argv[length-1]);
      exit(0);
    }

    //char* command = argv[0];
    i = 0;
    //remove the args from the args array
    while (strcmp(argv[i], ">") && i < length-1) {
      args[i] = malloc(sizeof(char) * strlen(argv[i]));
      strcpy(args[i], argv[i]);
      newLength++;
      j++;
      i++;
    }

    args[newLength] = NULL;

    //redirect the stream & run the command
    dup2(fileDescriptor, 1);
    if (execvp(*args, args) < 0) {
      for (i = 0; i < newLength; i++){
        free(args[i]);
      }
      perror("Failed to execute the program");
      exit(0);
    }
  }
  else if (input != -1) {
    //file = freopen(argv[output+1], "w+", stdin);
  }
  for (i = 0; i < newLength; i++){
    free(args[i]);
  }
}

void backgroundProcess() {
  //Run programs in the background with a '&' at the end of the command while the
  //background command is being executed
}

int main(int argc, char** argv) {
  /*
   * loop continously until read in a termination symbol
   */
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
