/**********************************************************
* Name: Marta Wegner
* Assignment #3
* CS 344
* Filename: smallsh
* Date: 8/2/15
***********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main() {
   char *line = NULL;
   char *token;
   char *iFileName;
   char *oFileName;
   char * args[513];
   int numArgs = 0;
   int bg = 0;
   int status = 0;

   //Print prompt
   printf(": ");
   fflush(stdout);

   //Read in a line
   ssize_t size = 0;
   getline(&line, &size, stdin);

   //Splint the line into args
   token = strtok(line, "\n");

   while(token != NULL) {
	if(strcmp(token, "<") == 0) {
	   //Input file
	   //Get file name
	   token = strtok(NULL, "\n");
	   
	   iFileName = token;
	  
	   //Get next token
	   token = strtok(NULL, "\n");
	}
	else if(strcmp(token, ">") == 0) {
	   //Output file
	   //Get file name
	   token = strtok(NULL, "\n");

	   oFileName = token;

	   //Get next token
	   token = strtok(NULL, "\n");
	}
	else if(strcmp(token, "&") == 0) {
	   //Command run in backgroud
	   bg = 1;

	   //End of line = break
	   break;
	}
	else {
	   //Else this is a arg - store it in the args array
	   args[numArgs] = token;

	   //get next token and increase # of args variable
	   token = strtok(NULL, "\n");
	   numArgs++;
	}
   }
   
   //End array of args with NULL
   args[numArgs] = NULL;

   if(args[0] == NULL || strncmp(args[0], "#", 1)) {
	//Comment of null - do nothing
   }
   else if (strcmp(args[0], "exit") == 0) {
	exit(0);
   }
   else if (strcmo(args[0], "status") == 0) {
	//Print status
	printf("Exit status: %d\n", status);
	fflush(stdout);
   }  
   else if (strcmp(args[0], "cd") == 0) {
	if (arg[1] == NULL) {
	   //There is no argument for cd
	   chdir(getenv("HOME"));
	}
	else {
	   //Else change to specified dir
	   chdir(args[1]);
	}
   }

   return 0;
}


   
