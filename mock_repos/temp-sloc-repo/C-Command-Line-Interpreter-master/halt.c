/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 1/9/2016
 * @modified: 2/9/2016
 * @params: char *programName, name of program to be killed
 * 
 * Description: Kills program with programName, if multiple instances kills all, if doesn't exist prints appropriate message
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	
int halt(char *programName){

	
	char cmd[300];
	strcpy(cmd, "pkill ");
	strcat(cmd, programName);				// command = "pkill process name"

	char *argsKill[3];
	argsKill[0] = "/usr/bin/pkill";			// path to pkill 
	argsKill[1] = programName;				// program name prefixed with pkill
 	argsKill[2] = NULL;						// null terminated 

	int status;
	status = execv(argsKill[0], argsKill);

	if (status != 0) {						// process not killed
		if (status == 1) {					// no processes matched
			printf("Error: could not kill program as it doesn't exist\n");
		}	
		else{								// Internal error 
			printf("Error: could not kill %s\n", programName);
			printf("Exit code: %d\n", status);
		}
		
	}
	else {									// should never get down here, but i want a msg if it ever does
		printf("Error: halt.c line 27, killed %s but it went down here\n", programName);	
	}
	return 0;								// will return after execv by itself if executed properly
}

