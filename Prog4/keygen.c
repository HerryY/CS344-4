/**********************************************************
 *  Name: Marta Wegner
 * CS 344
 * Program #4
 * filename: keygen.c
 *********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char* argv[]){
   int i;
   int randNum;
   char randChar;

   //seed random #generator
   srand(time(NULL));

   if (argc < 2) {
	printf("must specify a key length");
	exit(1);
   }

   //get key lengthfrom args
   int keyLength = atoi(argv[1]);

   //create key
   for (i = 0; i < keyLength; i++) {
	randNum = rand() % 27;
	if (randNum < 26) {
	   //determine letter
	   randChar = 65 + randNum;
	   printf("%c", randChar);
	}
	else {
	   //print space 
      	   printf(" ");
	}
   }

   return 0;
}

