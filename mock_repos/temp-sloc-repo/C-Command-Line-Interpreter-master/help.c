/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/7/2016
 * @modified: 1/8/2016
 * @params: None
 * 
 * Description: Displays user manual using less. Sets path to abs path of less command, executes it then sets it back to current 
 				working directory 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int help(char *helpABSpath)
{	
	
	char cmd[300];
	
	strcpy(cmd, "less ");
	strcat(cmd, helpABSpath);				// concatenate less and abs path to help manual

	char *passArgs[3];
	passArgs[0] = "/usr/bin/less";			// command
	passArgs[1] = helpABSpath;				// path to basic_manual.txt file
	passArgs[2] = NULL;						// null terminated
	
	execv(passArgs[0], passArgs);

	return 0;
}