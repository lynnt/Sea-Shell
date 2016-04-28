#include <stdio.h>

#define MAX_LEN 1024
#define ARG_NUM 4
#define MAX_COMMANDS 100

typedef enum Direction {
    LEFT,
    RIGHT
} Direction;

const char* list[] = {"cd", "help", "exit", "pwd"};
int redirect = 0;

typedef struct NonTerminatedString {
    char* str;
    int length;
} NonTerminatedString;

typedef struct cmdline {
    NonTerminatedString cmd[MAX_COMMANDS];
    int length;
} cmdline;

typedef struct redirectCmd {
    int dir;
    NonTerminatedString cmd;
    char* file;
} redirectCmd;

typedef struct cdStruct {
    NonTerminatedString path;
} cdStruct;

typedef struct execStruct {
    NonTerminatedString cmd;
    char** argv;
} execStruct;
