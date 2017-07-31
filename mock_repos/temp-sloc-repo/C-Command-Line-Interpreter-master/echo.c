/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: char *comment, comment to be echoed (printed) out, guaranteed to have quotations around it
 *
 * Description: prints comment out followed by new line
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>

int echo(char *comment)
{
	char echoThis[1000];							// assuming comment won't exceed 1000 characters
	int idx;
	char *c;
	for (idx = 1; idx < strlen(comment); idx ++)	// loop to get comment without quotations
	{												// note first index skipped as it is guaranteed to be "
		c = &comment[idx];
		if (strncmp(c, "\"", 1) == 0)				// end of comment as reached ending "
		{
			echoThis[idx-1] = '\0';					// terminate string
			break;									// note: "\0" won't work, need ''
		}
		else
		{
			echoThis[idx-1] = *c;
		}
	}

	printf("%s\n", echoThis);
	return 0;
}

