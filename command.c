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

void AppendSimpleCommand(Command *cmd, SimpleCommand sCmd){
	da_append(cmd, sCmd);
}




/*void Execute(Command* cmd) {
    // Save original stdin and stdout
    int tmpin = dup(STDIN_FILENO);
    int tmpout = dup(STDOUT_FILENO);

    // Set up fdin to read from stdin initially
    int fdin = dup(tmpin);
    int fdout;
    int ret;
    int pipefd[2];  // Pipe file descriptors

    for (int i = 0; i < cmd->count; i++) {
        SimpleCommand sCmd = cmd->items[i];

        // If not the last command, create a pipe
        if (i < cmd->count - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe error");
                exit(1);
            }
            fdout = pipefd[1];  // Writing to this pipe
            fdin = pipefd[0];   // Next process will read from this pipe
        } else {
            // Last command writes to stdout
            fdout = dup(tmpout);
        }

        // Fork and execute the command
        ret = fork();
        if (ret < 0) {
            perror("fork failed");
            exit(1);
        } else if (ret == 0) {
            // In the child process

            // Redirect stdin to fdin
            dup2(fdin, STDIN_FILENO);
            close(fdin);  // Close the original fdin after duplicating

            // Redirect stdout to fdout
            if (i < cmd->count - 1) {
                dup2(fdout, STDOUT_FILENO);
            }
            close(fdout);  // Close the original fdout after duplicating

            // Execute the command
            execvp(sCmd.argv[0], sCmd.argv);
            perror("execvp failed");  // If execvp fails
            exit(1);
        }

        // In the parent process
        close(fdout);  // Close parent's write end of the pipe
        if (i > 0) {
            close(fdin);  // Close parent's read end of the previous pipe
        }
    }

    // Restore original stdin and stdout
    dup2(tmpin, STDIN_FILENO);
    dup2(tmpout, STDOUT_FILENO);
    close(tmpin);
    close(tmpout);

    // Wait for all processes to complete
    for (int i = 0; i < cmd->count; i++) {
        wait(NULL);
    }
}*/



void Execute(Command* cmd){
	// save in/out channels
	int tmpin = dup(STDIN_FILENO);		
	int tmpout = dup(STDOUT_FILENO);		

	// set fdin and fdout as 0 and 1 to begin with
	int fdin, fdout;
	fdin = dup(tmpin);
	fdout = dup(tmpout);

	int ret;

	for(int i=0; i<cmd->count; i++){
		SimpleCommand sCmd = cmd->items[i];
		// duplicate fdin and set 0 to be that
		close(STDIN_FILENO);
		dup2(fdin, STDIN_FILENO);
		// close fdin since we are only assigning a duplicate of fdin to 0
		close(fdin);

		// if last command, then set fdout to be 
		if(i == cmd->count - 1){
			fdout = dup(tmpout);
		} else {
			// not the last command
			// create a pipe and set fdout and fdin 
			int pipefd[2];
			pipe(pipefd);
			fdin = pipefd[0];
			fdout = pipefd[1];
		}
		
		close(STDOUT_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);

		// fork_exec
		ret = fork();
		if(ret<0){
			printf("fork fail");
		} else if(ret == 0){
			int res = execvp(sCmd.argv[0], sCmd.argv); 
			if(res == -1){
				// Command does not exist
				if(errno==2){
					printf("%s: command does not exist\n", sCmd.argv[0]);	
				} else {
					perror("cannot exec command: ");
				}
				exit(1);
			}
		} 
	}
	// restore 1 and 0
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	// wait for the last process to finish
	waitpid(ret, NULL, WUNTRACED);
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
