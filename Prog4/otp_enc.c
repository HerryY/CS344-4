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

   //Create string to hold key text
   char *keyText = malloc(sizeof(char) * kLen); 

   //Set file point to begining of file
   lseek(fdKey, 0, SEEK_SET);

   //Read key text into string
   if (read(fdKey, keyText, kLen) == -1) {//read
	//If error reading
	perror("read key text enc");
	exit(1);
   }

   //Null terminate the string
   keyText[kLen - 1] = '\0';
 
   //Check that chars in plain text are valid
   for (i = 0; i < kLen - 1; i++) {
	if(isalpha(keyText[i]) || isspace(keyText[i])) {
	   //If letter or space do nothing
	}
	else { //not letter of space
	   //print error
	   perror("key text invalid char");
	   exit(1);
	}
   }

   //Client
   //create socket
   int socketfd;

   if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {//create
	//Id error creating
	perror("socket");
	exit(1);
   }

   //Setting up address
   struct hostent * server_ip_address;
   server_ip_address = gethostbyname("localhost");

   if(server_ip_address == NULL) {
	fprintf(stderr, "could not resolve host name\n");
	exit(1);
   }
 
   struct sockaddr_in server;

   //clear socket structure
   memset((char *)&server, 0, sizeof(server));


   server.sin_family = AF_INET;
   server.sin_port = htons(portNum);
   memcpy(&server.sin_addr, server_ip_address->h_addr, 
	  server_ip_address->h_length);


   //Connect socket
   if(connect(socketfd, (struct sockaddr*) &server, 
			 sizeof(server)) == -1) {
	perror("connect");
	exit(1);
   }

   //confirm connection
   int r;
   int conNum;
   //Receive confirmation number
   if((r = recv(socketfd, &conNum, sizeof(conNum), 0)) == -1) {
	//If error receiving
	perror("recv enc");
	exit(1);
   } 
   else if(r == 0) {
	perror("recv enc 0");
	exit(1);
   }

   //Check that confirmation number is correct
   int confirm = ntohl(conNum);

   //If number recieved is not correct
   if (confirm != 1) {
	fprintf(stderr, "could not contact otp_enc_d on port %d\n",
		portNum);
	exit(1);
   }

   //Successful connection to otp_enc_d
   //send plain text file size
   int pLenSend = htonl(pLen); //convert

   if(send(socketfd, &pLenSend, sizeof(pLenSend), 0) == -1) {
	perror("plain text file send");
	exit(1);
   }

   //send key text file size
   int kLenSend = htonl(kLen); //convert

   if(send(socketfd, &kLenSend, sizeof(kLenSend), 0) == -1) {
	perror("key text file send");
	exit(1);
   }


   return 0;
}
