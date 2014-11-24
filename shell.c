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

void parse(char* buffer, char** args, int argsSize, int *nargs) {
  //Parse args
  char* bufArgs[argsSize];
  char** cp;
  char* wbuf;
  int i, j;

  wbuf = buffer;
  bufArgs[0] = buffer;
  args[0] = buffer;

  for (cp = bufArgs; (*cp = strsep(&wbuf,"\n\t")) != NULL;) {
    if ((*cp != '\0') && (++cp >= &bufArgs[argsSize])) {
      break;
    }
  }

  for (j = i = 0; bufArgs[i] != NULL; i++) {
    if (strlen(bufArgs[i]) > 0) {
      args[j++] = bufArgs[i];
    }
  }

  //Add the NULL as the end argument because we need that later
  *nargs = j;
  args[j] = NULL;
}

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

void Exit() {
  //Exit the shell
  exit(0);
}

void executingProgram(const char* command, char* const argv[]) {
  //Executing other programs like ls/cd/etc..
  pid_t childPID;
  int* status;

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
  FILE* file;
  int output = outputRedirection(argv, length);
  int input = inputRedirection(argv, length);

  if (output != -1) {
    file = freopen(argv[output+1], "w+", stdout);
  }
  else if (input != -1) {
    file = freopen(argv[output+1], "w+", stdin);
  }

  fclose (file);
}

void backgroundProcess() {
  //Run programs in the background with a '&' at the end of the command while the
  //background command is being executed
}

int main() {
  char* cwd = "/home/lynnt";
  char* args[] = {"ls", "-l", ">", "foo.txt"};
  redirection(args, 4);
  return 0;
}
