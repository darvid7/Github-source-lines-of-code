/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 29/8/2016
 * @modified: 2/9/2016
 * @params: char *fileName, the name of the file to be create including the extension i.e. "apple.py"
 * 
 * Description: Checks to see if a file with the same name already exists, if so prints error message assuming we do not want to 
 *               accidentally overwrite a file, else creates the file
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <unistd.h>

int newFile(char *fileName) {
   
   if ( access( fileName, F_OK ) != -1 ){
      // file already exists
      printf("Error: %s exists already, don't want to overwrite it\n", fileName);
   } 
   else {
      FILE *fp;
      fp = fopen(fileName, "w");       // creates file if not there
      fclose(fp);                      // closes file

      if (access(fileName, F_OK) != -1){
         printf("File %s created\n", fileName);
      } 
      else {
         printf("ERROR: Did not create file\n");
      }

   }
   return 0;
}

