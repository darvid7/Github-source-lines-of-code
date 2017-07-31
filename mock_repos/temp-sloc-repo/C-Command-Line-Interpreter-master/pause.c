/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
  * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: None
 * 
 * Description: Pauses execution of CLI until user presses enter 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <unistd.h>
#include <stdio.h>

int pause(void)
{
	printf("Press Enter to continue..\n");
	char *ch;
	ch = getpass("");	// prevent's user typing
	if (ch != NULL) {	// do nothing
	}
	return 0;
}

			