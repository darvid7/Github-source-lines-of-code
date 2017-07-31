/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 1/9/2016
 * @modified: 2/9/2016
 * @params: char *programName, name of program to be run
 * 
 * Description: Assuming that the program to be run is in the current working directory, this will execute it using
 *				execv. If the program does not exist, appropriate error message printed
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	
int run(char *programName){
	
	char start;
	start = programName[0];
	int status;
	char cmd[300];						// assume wont exceed 300 chars
	char *argsRun[2];

	if ( strncmp(&start, "/", 1) != 0) { // program name does not starts with /, we can assume it is in current working directory

		// set up arguments for execv call
		strcpy(cmd, "./");
		strcat(cmd, programName);
		argsRun[0] = cmd;			
		argsRun[1] = NULL;
	}
	else {								// program name starts with /, can assume it includes the path to the program
		// set up arguments for execv call
		argsRun[0] = programName;
		argsRun[1] = NULL;
	}

	status = execv(argsRun[0], argsRun);

	if (status == -1) {
		printf("Error: program %s does not exist\n", programName);					// execv wouldn't have run progra,
	}
	else {
		printf("Error: Unknown error in run.c line 30, this should not happen\n");	// want to know if it ever gets here
	}
	return 0 ;	// will return after execv by itself if executed properly

	
}

