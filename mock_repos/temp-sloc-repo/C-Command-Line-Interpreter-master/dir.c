/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: char *destinationDir, string of path to the destination folder 
 * 
 * Description: Opens destinationDir and prints out all files in it, if no argument given does it for the current directory
 *				if destinationDir does not exist, prints appropriate error message.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <dirent.h>		// allows for dir struct
#include <sys/types.h>
#include <stdlib.h>

int dir(char *destinationDir)
{
	DIR *dir;			
	struct dirent *sd;	// pointer to dirent struct

	if (destinationDir == NULL)		
	{
		dir = opendir(".");				// default to current directory
	}
	else
	{
		dir = opendir(destinationDir);	// open destination directory 
	}

	if (dir == NULL)					// error message and return 
	{
		printf("Error: %s doesn't exist\n", destinationDir);
		return 0;
	}

	while ( (sd = readdir(dir) ) != NULL ) 
	{
		printf("%s\n", sd->d_name);		// print name for each item in dir, -> like dot notation
	}
	return 0;
}