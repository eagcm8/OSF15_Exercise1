#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../debug.h"
#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


	//TODO FUNCTION COMMENT
/* 
 * PURPOSE: parses command line arguments
 * INPUTS: 
 *	character pointer input, Commands_t** cmd
 * RETURN:
 *  returns true if args are accepted, else false
 *
 **/
bool parse_user_input (const char* input, Commands_t** cmd) {
	
	//TODO ERROR CHECK INCOMING PARAMETERS

	check(cmd != NULL, "Pointer cannot be NULL.");

	check(input != NULL, "Pointer cannot be NULL.");

	char *string = strdup(input);
	
	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}	
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
error:
	return false;
}

	//TODO FUNCTION COMMENT
/* 
 * PURPOSE: frees commands from memory
 * INPUTS: 
 *	Commands_t double pointer cmd
 * RETURN:
 *  nothing is returned
 *
 **/
void destroy_commands(Commands_t** cmd) {

	//TODO ERROR CHECK INCOMING PARAMETERS
	check(cmd != NULL, "Pointer cannot be NULL.");
	
	for (int i = 0; i < (*cmd)->num_cmds; ++i) {
		free((*cmd)->cmds[i]);
	}
	free((*cmd)->cmds);
	free((*cmd));
	*cmd = NULL;
error:
	return;
}

