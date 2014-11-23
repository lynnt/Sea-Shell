/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: This is a shell program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Get the linux commands
#include <errno.h> //Return errors

void parse(char* buffer, char** args, int argsSize, int *nargs) {
  //Parse args
  /*
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
  */
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

void executingProgram() {
  //Executing other programs like ls/cd/etc..
}

void inputRedirection() {
  //Redirect the input/output when seeing the arrows
}

void outputRedirection() {
  //Redirect the input/output when seeing the arrows
}

void backgroundProcess() {
  //Run programs in the background with a '&' at the end of the command while the
  //background command is being executed
}

int main() {
  char* cwd = "/home/lynnt";
  cd (cwd);
  return 0;
}
