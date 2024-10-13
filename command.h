#ifndef COMMAND_H
#define COMMAND_H

#include "common.h"
#include <errno.h>


// COMMAND
typedef struct {
	char**	argv;
} SimpleCommand;

typedef struct {
	SimpleCommand* items;
	int capacity;
	int count;

} Command;

void AppendSimpleCommand(Command* cmd, SimpleCommand sCmd);

void Execute(Command* cmd);
void FreeCommand(Command* cmd);

char ** Split(char * a_str, const char a_delim);

#endif // !COMMAND_H

