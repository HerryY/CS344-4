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
	printf("Must specifiy plaintext, key, and port number\n");
	exit(1);
   }

   //Get port num from args
   int portNum = atoi(argv[3]);

   //open plain text file and key for reading
   int fdPlain = open(argv[1], O_RDONLY);
   int fdKey = open(argv[2], O_RDONLY);

   //check that there was not an error opening
   if (fdPlain == -1 || fdKey == -1) {
	printf("error opening files\n");
	exit(1);
   }

   //Get size of plain text
   int pLen = lseek(fdPlain, 0, SEEK_END);

   //Get size of key text
   int kLen = lseek(fdKey, 0, SEEK_END);

   //Verify key file is larger than plain text
   if (kLen < pLen) { //compare key to plain
	printf("Key too short\n");
	exit(1);
   }

   //Create string to hold plain text
   char *plainText = malloc(sizeof(char) * pLen); 

   //Set file point to begining of file
   lseek(fdPlain, 0, SEEK_SET);

   //Read plain text into string
   if (read(fdPlain, plainText, pLen) == -1) {//read
	//If error reading
	printf("read plain text enc\n");
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
	   printf("Plain text invalid char\n");
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
	printf("read key text enc\n");
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
	   printf("key text invalid char\n");
	   exit(1);
	}
   }

   //Client
   //create socket
   int socketfd;

   if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {//create
	//Id error creating
	printf("socket error\n");
	exit(1);
   }

   //Setting up address
   struct hostent * server_ip_address;
   server_ip_address = gethostbyname("localhost");

   if(server_ip_address == NULL) {
	printf("could not resolve host name\n");
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
	printf("connect\n");
	exit(2);
   }

   //confirm connection
   int r;
   int conNum;
   //Receive confirmation number
   if((r = recv(socketfd, &conNum, sizeof(conNum), 0)) == -1) {
	//If error receiving
	printf("recv enc\n");
	exit(1);
   } 
   else if(r == 0) {
	printf("recv enc 0\n");
	exit(1);
   }

   //Check that confirmation number is correct
   int confirm = ntohl(conNum);

   //If number recieved is not correct
   if (confirm != 1) {
	printf("could not contact otp_enc_d on port %d\n",
		portNum);
	exit(2);
   }

   //Successful connection to otp_enc_d
   //send plain text file size
   int pLenSend = htonl(pLen); //convert

   if(send(socketfd, &pLenSend, sizeof(pLenSend), 0) == -1) {
	printf("plain text file send\n");
	exit(1);
   }

   //send key text file size
   int kLenSend = htonl(kLen); //convert

   if(send(socketfd, &kLenSend, sizeof(kLenSend), 0) == -1) {
	printf("key text file send\n");
	exit(1);
   }

   //Send plain text
   int len = 0;
   while (len <= pLen) { //while whole file not sent
	char plainSend[1024];//hold text to senf

	//subset of plain to senf
	strncpy(plainSend, &plainText[len], 1023);

	plainSend[1024] = '\0';//null terminate
	
	//send 
	if(send(socketfd, &plainSend, 1024, 0) == -1){
	   printf("plain text send\n");
	   exit(1);
	}

	len += 1023;//Add length sent to len
   }

   //Send key text
   len = 0;
   while (len <= kLen) {//while whole key is not sent
	char keySend[1024];//subset

	//subset of key to send
	strncpy(keySend, &keyText[len], 1023);

	//null terminate
	keySend[1024] = '\0';

	//send
   	if(send(socketfd, &keySend, 1024, 0) == -1){
		printf("key text send\n");
		exit(1);
   	}

	len += 1023;//add len sent to len
   }

   //Receive back encrypted text
   //allocate memory for cipher text
   char *cipherText = malloc(sizeof(char) * pLen);
   char buffer[1042];

   //Clear ciphertext 
   memset(cipherText, '\0', pLen);

   //Receive cipher
   len = 0;
   r = 0;
   while(len < pLen) { //while the whole file has not 
 		       //been received
	//clear buffer each use
	memset((char *)buffer, '\0', sizeof(buffer));

	//receive
 	r = recv(socketfd, buffer, 1024, 0);//receive

        if(r == -1) {
	   //Error receiving data
	   printf("recv cipher text file -1\n");
	   exit(1);
	}	   
	else if(r == 0) {
	   //end of data
	   if(len < pLen) {
		printf("recv cipher text file <\n");
		exit(1);
	   }
	}
	else {
	   //concat string
	   strncat(cipherText,buffer,(r-1));
	}	   

	len += (r-1); //Add len recieved to len
   }

   cipherText[pLen - 1] = '\0';

   //Print cipher text
   printf("%s\n", cipherText);

   //Free memory
   free(plainText);
   free(keyText);
   free(cipherText);

   return 0;
}
