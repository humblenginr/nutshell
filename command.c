#include "command.h"
#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void PrintPrompt(){
	printf("> ");
}
// COMMAND STACK
void PushCommand(CommandStack *cmdArr, Command cmd){
	da_append(cmdArr, cmd);
}

int PopCommand(CommandStack *cmdArr, Command* res){
	if(cmdArr->count <= 0){
		printf("Command stack is empty");
		return -1;
	}
	*res = (cmdArr->items)[--(cmdArr->count)];
	return 0;
}

// Execute will wait till the process is finished.
void Execute(Command* cmd){
	pid_t p = fork();
	if(p<0){
		printf("fork fail");
	} else if(p == 0){
		// this is because execvp expects the argument array to be NULl terminated
		int res = execvp(cmd->argv[0], cmd->argv); 
		if(res == -1){
			perror("Exec failure");
			exit(1);
		}
	} 
	wait(NULL);
	// parent will just go about minding their business
}

// Source: stack overflow
// Creates a NULL terminated array of c-strings split by a delimier
char ** Split(char * a_str, const char a_delim) {
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}
	
	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
		knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}
