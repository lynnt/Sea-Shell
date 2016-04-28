/*
 * Lynn Tran (c) 2016
 */
#include<stdio.h>

char* readLine(char *str);
int isBuiltinCommand(const cmdline cmd);
void clearWordBuffer(char *word, int pos);
void insertNewArg(NonTerminatedString *cmd, char *word, int pos);
void parse(char *str, cmdline *cmd);
