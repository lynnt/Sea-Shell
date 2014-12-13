/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>

void parserCommand(){

}

int main () {

  char* commandLine;
  commandLine = readline("enter a string:  ");
  if (commandLine != NULL)  {
    if (strcmp(commandLine, "exit")) {
      exit(0);
    }
    free(commandLine);
  }
  return 0;
}
