/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void parseCommand(char str[]){
  char* ptr = NULL;
  ptr = strtok(str, " ");
  while(ptr != NULL){
    printf("%s\n", ptr);
    ptr = strtok(NULL, " ");
  }
}

int main () {

  char* commandLine = NULL;
  int read;
  size_t len;
  read = getline(&commandLine, &len, stdin);

  if(read != -1){
    parseCommand(commandLine);
  }

  if (commandLine != NULL)  {
    if (strcmp(commandLine, "exit")) {
      exit(0);
    }
    free(commandLine);
  }
  return 0;
}
