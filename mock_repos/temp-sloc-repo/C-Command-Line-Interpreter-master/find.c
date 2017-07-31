/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 31/8/2016
 * @modified: 2/9/2016
 * @params: char *fileName, char character
 *			fileName is the name of the file that to be searched for occurrences of character
 *			character is guaranteed to be a string of length 1
 *
 * Description: Searches fileName for the number of times character appears, prints this out
 *				If fileName does not exist, prints error message
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int find(char character, char *fileName)
{
	if (access(fileName, F_OK) != -1) {						// check file exits
		FILE *fp;
		int count = 0;
		int comparsionResult;
		fp = fopen(fileName, "r");							// open file
		char ch;

		while ( ( ch != EOF ) ) 							// loop and compare
		{
			ch = fgetc(fp);

			comparsionResult = strncmp(&ch, &character, 1);	// comparison ok as character guaranteed to be string of length 1
			/*
			printf("ch: %c\n", ch);							// check contents of variables, wouldn't work before because had random stuff in those variables
			printf("&ch: %s\n", &ch);
			printf("character: %c\n", character);
			printf("&character: %s\n", &character);
			*/
			if (comparsionResult == 0) {					// match
				count ++;
			}			

		}

		fclose(fp);

		printf("%c occurred %d times in file %s\n", character, count, fileName);

	}
	else {
		printf("Error: file %s does not exist\n", fileName);
	}
	return 0;	
}

