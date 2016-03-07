/********************************************************** 
 * Name: Marta Wegner
 * File: keygen.c
 * Date: 3/7/16
 * Description: creates key file of specified length.
 * Characters in the file are A-Z and space and generated 
 * using standard UNIX randomization methods. 
 * syntax: keygen [keylength]
 * where keylength is the length of the gile in characters
 * outputs to stdout
 *********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
   int i;
   int randNum;
   int randChar;

   //seed rand num generator
   srand(time(NULL));

   if (argc < 2) {
	printf("Must specify a key length");
        exit(1);
   }

   //get key length from args
   int keyLen = atoi(argv[1]);

   //create key
   for (i = 0; i < keyLen; i++) {
	randNum = rand() % 27;

	if(randNum < 26) {
	   //determine letter
	   randChar = 65 + randNum;
	   printf("%c", randChar);
	}
	else {
	   //print space
	   printf(" ");
	}
   }

   //Add new line to end
   printf("\n");

   return 0;
}
