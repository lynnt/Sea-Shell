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
  char delimiters[] = " ";
  ptr = strtok(str, delimiters);
  int index = 0;
  //iterate over the string until you find the null terminated string
  while(ptr != NULL){
    printf("%s\n", ptr);
    if(index < 1024){
      commands[index] = ptr;
      index += strlen(ptr);
      printf("%s\n", commands[index]);
      //printf("%d\n", index);
      /*
      if(strcmp(ptr, "<") == 0){
        printf("Found");
        return "redirect";
      }
      */
    }
    else{
      //TODO: Realloc the array size
      perror("Can't realloc");
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
    parseCommand(commandLine, commands);
    //printf("%s\n", commandLine);
    return 0;
  }

  if(commandLine != NULL)  {
    if(strcmp(commandLine, "exit")) {
      exit(0);
    }
    free(commandLine);
  }
  return 0;
}
