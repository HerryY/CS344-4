/**********************************************************
 *  Name: Marta Wegner
 * CS 344
 * Program #4
 * filename: otp_enc.c
 *********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<netinet/in.h>

int main (int argc, char* argv[]) {
   int fdPlain;
   int fdKey;
   int port;
   char buffer[64];
   char c;

   if (argc < 4) {
	printf("Must specify plaintext, key, and port number\n");
   }

   //open plain text and key files for reading
   fdPlain = open(argv[1], O_RDONLY);
   fdKey = open(argv[1], O_RDONLY);
   
   //check that there was not an error opening
   if(fdPlain == -1 || fdKey == -1) {
	perror("open");
	exit(1);
   }

   //get port number form args
   port = atoi(argv[3]);

   //check for valid chars
   while(read(fdPlain, buffer, 1)) {
	c = buffer[0];

	if (c != ' ' && c < 'A' || c > 'Z') {
	   perror("Plaintext invalid chars");
	   exit(1);
 	}
   }

   //check that key right length
   int plainLen = lseek(fdPlain, 0, SEEK_END); //length of plaintext
   if (lseek(fdKey, 0, SEEK_END < plainLen)) {//compare plain len to key len
	perror("Key too short");
	exit(1);
   }
   

   return 0;
}

