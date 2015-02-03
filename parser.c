/*
 * Lynn Tran
 * Copyright (c) Lynn Tran 2014
 * Description: Parser for shell program
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

char* parseCommand(char str[], char* commands[]){
  char* ptr = NULL;
  ptr = strtok(str, " ");
  int index = 0;
  while(ptr != NULL){
    printf("%s\n", ptr);
    if(index < 1024){
      commands[index] = ptr;
      printf("%s\n", commands[index]);
    }
    else{
      //TODO: Realloc the array size
      perror("Can't realloc");
    }
    ptr = strtok(NULL, " ");
      printf("%d\n", index);
    if(strcmp(ptr, "<") == 0){
      printf("Found");
      return "redirect";
    }
  }
  return NULL;
}

int main () {

  char* commandLine = NULL;
  char* commands[1024];
  int read;
  size_t len;
  read = getline(&commandLine, &len, stdin);

  if(read != -1){
    printf("%s\n", commandLine);
    return 0;
    parseCommand(commandLine, commands);
  }

  if (commandLine != NULL)  {
    if (strcmp(commandLine, "exit")) {
      exit(0);
    }
    free(commandLine);
  }
  return 0;
}
