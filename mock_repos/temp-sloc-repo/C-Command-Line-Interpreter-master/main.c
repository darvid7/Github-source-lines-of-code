/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * @author: David Lei, Student ID: 26029391
 * @since: 26/8/2016
 * @modified: 2/9/2016
 * 
 * Description: main file for FIT2070 Assignment 1, part 2 Advanced CLI
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// include libraries 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// include files for required functions
#include "help.h"
#include "clear.h"
#include "pause.h"
#include "quit.h"
#include "cd.h"
#include "echo.h"
#include "dir.h"
#include "newfile.h"
#include "copy.h"
#include "find.h"
#include "run.h"
#include "halt.h"
// define return messages 
#define OK 				1
#define ERR_TOO_LONG 	2
#define ERR_NULL		3
#define ERR_FORMAT 		4 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * @author: David Lei, Student ID: 26029391
 * @since: 26/8/2016
 * @modified: 2/9/2016
 * 
 * Description: Reads in input, buffer is set to a predefined size, will ignore anything outside that size
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int readInput(char *buffer, size_t bufferSize)
{
    // No input
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        return ERR_NULL;
    }
    // Check last index of buffer (check if it is \n)
    if (buffer[strlen(buffer)-1] != '\n')
    {
        int extra = 0;
        int ch;
        // loop until \n and EOF encountered
        // flushes stdin
        // return ERR_TOO_LONG if go in to loop, else OK
        while( ( (ch = getchar()) != '\n') && (ch != EOF) )
        {
            extra = 1;
        }
        return (extra == 1) ? ERR_TOO_LONG : OK;
    }
    // Replace new line with end of string
    buffer[strlen(buffer)-1] = '\0';

    return OK;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * @author: David Lei, Student ID: 26029391
 * @since: 26/8/2016
 * @modified: 2/9/2016
 * 
 * Description: Executes commands after input parsed, calls functions based on command
                Also checks for number of arguments needed for a command and prints error message too many or little
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int execute_commands(char *arg1, char *arg2, char *arg3, char *echoCommentBuf, char *echoComment, char *helpABSpath)
{
    if (strcmp(arg1, "cd") == 0) {                                              // cd command
        if (arg3 != NULL){
            printf("cd takes only 1 argument, try again\n");
        } 
        else {
            cd(arg2);
            return 1;
        }
    }
    else if (strcmp(arg1, "quit") == 0) {                                       // quit command
        if (arg2 != NULL || arg3 != NULL) {
            printf("quit takes 0 arguments, try again\n");
        }
        else{
            printf("Good bye..\n");
            quit();
            return 0;
        }
    }
    else if (strcmp(arg1, "pause") == 0) {                                      // pause command
        if (arg2 != NULL || arg3 != NULL) {
            printf("pause takes 0 arguments, try again\n");
        }
        else {
            pause();
            return 1;
        }
    }
    else {
                                                                                // fork 
        int pid;
        pid = fork();
        //printf("pid: %d\n", pid);
        if (pid > 0){
            wait(NULL);
            //printf("Parent Here\n");
            return(1);
        }
        else if (pid == 0) {                                                    // child process
            if (strcmp(arg1, "clear") == 0){                                    // clear command
                if (arg2 != NULL || arg3 != NULL){
                    printf("clear takes 0 arguments, try again\n");
                }
                else {
                    clear();
                }
            }
            else if (strcmp(arg1, "dir") == 0) {                                // dir command
                if (arg3 != NULL) {
                    printf("dir takes only 1 argument, try again\n");
                }
                else {
                    dir(arg2);
                }
            }
            else if (strcmp(arg1, "echo") == 0) {                               // echo command, also checks for format
                if (echoCommentBuf != NULL){
                    printf("echo takes only 1 argument, try again\n");
                }
                else if (echoComment == NULL) {
                    printf("echo needs at least 1 argument, try again\n");
                }
                else {
                    if ( strncmp(&echoComment[0], "\"", 1) == 0) {                                          // has opening "
                        if (strncmp(&echoComment[strlen(echoComment)-1], "\"", 1) == 0) {                   // has ending "
                            echo(echoComment);
                        }
                        else {
                            printf("Missing ending quotation, make sure comment is of form \"comment\"\n");
                        }
                    }
                    else {
                        printf("Missing starting quotation, make sure comment is of form \"comment\"\n");
                    }
                }
            }
            else if (strcmp(arg1, "help") == 0) {                                                           // help command 
                if (arg2 != NULL || arg3 != NULL) {
                    printf("help takes 0 arguments, try again\n");
                }
                else {
                    help(helpABSpath);
                }
            }
            else if (strcmp(arg1, "new") == 0) {                                                             // new <file> command
                if (arg2 != NULL) {
                    if (arg3 == NULL) {
                        newFile(arg2);
                    }
                    else {
                        printf("new only takes 1 argument\n");
                    }
                }
                else {
                    printf("new requires the file name and extension\n");
                }
            }
            else if (strcmp(arg1, "cp") == 0) {                                                              // cp (copy) <old> <new> command
                if ((arg2 != NULL) && (arg3 != NULL)) {
                    copy(arg2, arg3);
                }
                else {
                    printf("cp takes 2 arguments\n");
                }
            }
            else if (strcmp(arg1, "find") == 0) {                                                           // find <char> <file> command
                if ((arg2 != NULL) && (arg3 != NULL)) {                                                     // check arg2 and arg3 not null   
                    if (strlen(arg2) == 1) {                                                                // check arg2 is a character
                        find(*arg2, arg3);
                    }
                    else {
                    printf("the first argument in find needs to be a single character\n");
                    }
                }
                else {
                    printf("find takes 2 arguments, a character and a filename]\n");
                }
            }

            else if (strcmp(arg1, "run") == 0) {                                                             // run <program> command
                if (arg2 != NULL) {
                    if (arg3 == NULL) {
                        run(arg2);
                    }
                    else {
                        printf("run only takes 1 argument\n");
                    }
                }
                else {
                    printf("run requires the name of the program\n");
                }
            }
            else if (strcmp(arg1, "halt") == 0) {                                                            // halt <program> command
                if (arg2 != NULL) {
                    if (arg3 == NULL) {
                        halt(arg2);
                    }
                    else {
                        printf("halt only takes 1 argument\n");
                    }
                }
                else {
                    printf("halt requires the name of the program\n");
                }
            }

            else {                                                              // not a valid command
                printf("Invalid command, try again\n");
            }
        }
        else {                                                                  // failed to fork
            printf(" Failed to fork a process \n");
            exit(-1);
        }

    }
    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * @author: David Lei 
 * @since: 29/7/2016
 * @modified: 2/8/2016
 * 
 * Description: Main loop to run the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main()
{   
    int run;
    run = 1;
    char startDir[150];           
    getcwd(startDir, 150);                      // absolute path 
    char helpABSpath[250];
    strcat(helpABSpath, startDir);              
    strcat(helpABSpath, "/advanced_manual.txt\0");  // absolute path to help

    while (run)
    {
        printf("$ ");

        int readInputResult;
        int bufferSize = 100;
        char buffer[bufferSize];
        char echoInput[bufferSize];
        char echoInputCpy[bufferSize];

        readInputResult = readInput(buffer, bufferSize);	// read from stdin, store in buffer

        // Error checking on input
        if (readInputResult == ERR_NULL) {
            printf("Error: No input provided \n");
        } 
        else if (readInputResult == ERR_TOO_LONG) {
            printf("Error: Input too long\n");
        }
        else {
            strcpy(echoInput, buffer);                  // copy buffer, needed for echo command
            strcpy(echoInputCpy, buffer);

            char *arg1 = strtok(buffer, " \n");         // if this is null, we don't have enough arguments
            char *arg2 = strtok(NULL, " \n");
            char *arg3 = strtok(NULL, " \n");
            char *arg4 = strtok(NULL, " \n");           // if this exists we have too many arguments

            char *discard = strtok(echoInputCpy, " \n");
            char *echoPlaceHolder = strtok(NULL, "\"\0\n");       // comment to be used in the echo command
            char *echoCommentBuf = strtok(NULL, "\n\0");          // if this has anything then we have too many arguments for echo

            char *echoDiscard = strtok(echoInput, " \n");
            char *echoComment = strtok(NULL, "\0\n");

            if ( (arg4 != NULL) && (strcmp(arg1, "echo") != 0) ) {
                printf("Too many arguments, invalid command, try again\n");
            }
            else if (arg1 == NULL) {
                printf("No input provided, try again\n");
            }
            /* Note: need to do quit and cd commands before forking */
            else {
                run = execute_commands(arg1, arg2, arg3, echoCommentBuf, echoComment, helpABSpath);
            }
        }
    }
}

