/**********************************************************
 * Name: Marta Wegner
 * File Name: otp_enc.c
 * Date: 3/7/16
 * Description: connects to otp_enc_d and asks it to
 * perform encyption.
 * syntax: otp_enc [plaintext] [key] [port]
 * When ciphertext is received, outputs it to stdout
 * If receives key or plaintext files with bad char, or key
 * file shorter than the plaintext, it exits with and error
 * If port not found error reported to screen
 **********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char **argv) {
   int i;

   //Check for correct num of args
   if (argc < 4) {
	fprintf(stderr , "Must specifiy plaintext, key, and port number\n");
	exit(1);
   }

   //Get port num from args
   int portNum = atoi(argv[3]);

   //open plain text file and key for reading
   int fdPlain = open(argv[1], O_RDONLY);
   int fdKey = open(argv[2], O_RDONLY);

   //check that there was not an error opening
   if (fdPlain == -1 || fdKey == -1) {
	perror("open files");
	exit(1);
   }

   //Get size of plain text
   int pLen = lseek(fdPlain, 0, SEEK_END);

   //Get size of key text
   int kLen = lseek(fdKey, 0, SEEK_END);

   //Verify key file is larger than plain text
   if (kLen < pLen) { //compare key to plain
	perror("Key too short");
	exit(1);
   }

   //Create string to hold plain text
   char *plainText = malloc(sizeof(char) * pLen); 

   //Set file point to begining of file
   lseek(fdPlain, 0, SEEK_SET);

   //Read plain text into string
   if (read(fdPlain, plainText, pLen) == -1) {//read
	//If error reading
	perror("read plain text enc");
	exit(1);
   }

   //Null terminate the string
   plainText[pLen - 1] = '\0';

   //Check that chars in plain text are valid
   for (i = 0; i < pLen - 1; i++) {
	if(isalpha(plainText[i]) || isspace(plainText[i])) {
	   //If letter or space do nothing
	}
	else { //not letter of space
	   //print error
	   perror("Plain text invalid char");
	   exit(1);
	}
   }

   //Check that chars in plain text are valid

   return 0;
}
