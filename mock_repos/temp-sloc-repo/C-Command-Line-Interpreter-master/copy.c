/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: char *oldName, char *newFileName 
 *			the names of the file to be copied (old) and the file to be copied to (new)
 *			including extensions 
 *
 * Description: Checks to see if the old file exists, if so proceed with copying, else print error message
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int copy(char *oldFileName, char *newFileName)
{

	if (access(oldFileName, F_OK) != -1){	// old file exists, can copy
		FILE *oldFp;
		FILE *newFp;

		oldFp = fopen(oldFileName, "r");	// open with read perms
		newFp = fopen(newFileName, "w");	// assume we overwrite

		char ch;
		char ch2;
		while( ( ch != EOF ) )				// copy 
		{
			ch = fgetc(oldFp);
			ch2 = fgetc(oldFp);
			fputc(ch, newFp);

			if (ch2 == EOF)					// dodge the weird char
			{
				break;
			}
			else
			{
				fputc(ch2, newFp);

			}
		}
		// close files
		fclose(oldFp);
		fclose(newFp);

		printf("Finished copying contents of %s to %s\n", oldFileName, newFileName);

    } 
    else {
    	printf("ERROR: %s does not exist\n", oldFileName);
    }
    return 0;
}

	

