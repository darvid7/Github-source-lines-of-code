/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: char *destinationDir, string of path to the destination folder 
 * 
 * Description: Changes directory to the destination folder if possible, else prints appropriate error message
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int cd(char *destinationDir)
{	
	char *homeDir;	
	int changeResult;
	homeDir = getenv("HOME");							// default destination if no destination is specified 
	if (destinationDir != NULL)	
	{
		changeResult = chdir(destinationDir);
	}
	else
	{
		changeResult = chdir(homeDir);
	}

	if (changeResult < 0) 
	{
		printf("Error: %s\n", strerror(errno));			// Error printed if can't change
	}
	else 
	{
		char workingDir[4096];							
		getcwd(workingDir, 4096);						// get working directory, 4069 is max path size

		int setevnResult; 
		setenv("PATH", workingDir, setevnResult);		// update PWD variable, quite sure this is correct

		// Tests
		//printf("Setevn test: %d\n", setevnResult);
		//printf("CUR PATH: %s\n", getenv("PATH"));		// correctly changes PWD

		printf("%s\n", workingDir);

	}
	return 0;
}