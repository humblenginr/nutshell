#ifndef COMMAND_H
#define COMMAND_H

#include "common.h"

// COMMAND
typedef struct {
	char**	argv;
} Command;

void Execute(Command* cmd);
void FreeCommand(Command* cmd);

//COMMAND STACK
typedef struct {
	Command* items;
	int	count;
	int	capacity;
} CommandStack;

void PushCommand(CommandStack* cmdArr, Command cmd);
int PopCommand(CommandStack* cmdArr, Command* res);
#endif // !COMMAND_H
//


char ** Split(char * a_str, const char a_delim);
