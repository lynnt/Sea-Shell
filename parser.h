/*
 * Lynn Tran (c) 2016
 */
#include <stdio.h>

#define MAX_LEN 1024
#define ARG_NUM 4
#define LEFT 1
#define RIGHT 2
#define MAX_COMMANDS 100

char delimiters[] = {'>', '<', '&', '|'};
const char* list[] = {"cd", "help", "exit", "pwd"};

typedef struct commands {
    char* str;
    int length;
} commands;

typedef struct cmdline {
    commands cmd[MAX_COMMANDS];
    int length;
} cmdline;

typedef struct redirectCmd {
    int dir;
    commands cmd;
    char* file;
} redirectCmd;

typedef struct cdStruct {
    commands cmd;
} cdStruct;

typedef struct execStruct {
    commands cmd;
    char** argv;
} execStruct;

char* readLine(char *str);
int isBuiltinCommand(const commands cmd);
void clearBuffer(char *word, int pos);
void insertNewArg(commands *cmd, char *word, int pos);
void parseArg(char *str, cmdline *cmd);
void parse(char *str);
