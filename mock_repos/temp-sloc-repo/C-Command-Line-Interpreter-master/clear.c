/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: None
 * 
 * Description: Clears the output screen
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int clear(void){
	char *argsClear[2];
	argsClear[0] = "/usr/bin/clear";	// path
	argsClear[1] = NULL;				// null termination	
    
    execv(argsClear[0], argsClear);		// execute 
	return 0;
}
