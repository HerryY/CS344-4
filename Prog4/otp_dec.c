/**********************************************************
 *  Name: Marta Wegner
 * CS 344
 * Program #4
 * filename: otp_dec.c
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
#include<netdb.h>

int main (int argc, char* argv[]) {
   int i;
   int fdCipher;
   int fdKey;
   int port;
   char buffer[1024];
   char message[] = "dec";
   char c;
   int socketfd;
   struct hostent *server_ip_address;
   struct sockaddr_in server;
   int length;
   int r;
   int w;

   if (argc < 4) {
	fprintf(stderr, "Must specify ciphertext, key, and port number\n");
   }

   //open cipher text and key files for reading
   fdCipher = open(argv[1], O_RDONLY);
   fdKey = open(argv[1], O_RDONLY);
   
   //check that there was not an error opening
   if(fdCipher == -1 || fdKey == -1) {
	perror("open");
	exit(1);
   }

   //get port number form args
   port = atoi(argv[3]);

   //check for valid chars
   while(read(fdCipher, buffer, 1)) {
	c = buffer[0];

	if (c != ' ' && c < 'A' || c > 'Z') {
	   perror("ciphertext invalid chars");
	   exit(1);
 	}
   }

   //check that key right length
   int cipherLen = lseek(fdCipher, 0, SEEK_END); //length of plaintext
   if (lseek(fdKey, 0, SEEK_END < cipherLen)) {//compare plain len to key len
	perror("Key too short");
	exit(1);
   }
   
   //create socket
   if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	//Error if can't create
	perror("socket");
	exit(1);
   }

   //Setting up address
    server_ip_address = gethostbyname("localhost");

   if(server_ip_address == NULL) {
	fprintf(stderr, "could not resolve host name\n");
	exit(1);
   }

   //Fill in address struct
   server.sin_family = AF_INET;
   server.sin_port = htons(port);
   memcpy(&server.sin_addr, server_ip_address->h_addr, server_ip_address->h_length);

   //Connect to socket
   if((connect(socketfd, (struct sockaddr*) &server, sizeof(server))) == -1) {
	perror("connect");
	exit(2);
   }

   //confirm connection
   write(socketfd, message, sizeof(message));//send confirmation message
   read(socketfd, buffer, sizeof(buffer)); //receive confirmation message
   if (strcmp(buffer, "dec_d") != 0) {
	fprintf(stderr, "could not contact otp_dec_d on port %d\n", port); 
   	exit(2);
   }

   //send cipher text file
   //get length of file
   length = lseek(fdCipher, 0, SEEK_END);
      
   //set file ptr to beginning
   lseek(fdCipher, 0, SEEK_SET);

   //send length of file
   write(socketfd, &length, sizeof(int));
   

   //send the file
   //get part of the file
   while((r = read(fdCipher, buffer, sizeof(buffer))) > 0) {//keep sending
							   //until whole file
							   //is sent
	//send part of the file
	for (i = 0; i < r; i += w) {//write part of file until amount sent
				    //is equal to amount to send
	   //write
	   w = write(socketfd, buffer + i, r - i);

	   if (w < 0) { //unable to write
		perror("write");
		exit(1);
	   }
	}
   }

   //reset buffer
   memset(buffer, '\0', sizeof(buffer));

   //get confirmation that file received
   if ((r =  read(socketfd, buffer, sizeof(buffer))) < 0) {
	//error reading
	perror("read confirmation");
   }
   if (strcmp(buffer, "received") != 0) {
	//error being received
	perror("confirmation");
	exit(1);
   }  	
   
    //send key file
   //get length of file
   length = lseek(fdKey, 0, SEEK_END);
      
   //set file ptr to beginning
   lseek(fdKey, 0, SEEK_SET);

   //send length of file
   write(socketfd, &length, sizeof(int));
   

   //send the file
   //get part of the file
   while((r = read(fdKey, buffer, sizeof(buffer))) > 0) {
	//send part of the file
	for (i = 0; i < r; i += w) {//write part of file until amount sent
				    //is equal to amount to send
	   //write
	   w = write(socketfd, buffer + i, r - i);

	   if (w < 0) { //unable to write
		perror("write");
		exit(1);
	   }
	}
   }

   //reset buffer
   memset(buffer, '\0', sizeof(buffer));

   //get confirmation that file received
   if ((r =  read(socketfd, buffer, sizeof(buffer))) < 0) {
	perror("confirmation");
   }
   if (strcmp(buffer, "received") != 0) {
	perror("confirmation");
	exit(1);
   }

   //get text file and print
   for(i = 0; i < cipherLen; i += r) {
	//get part of plain file
	if ((r = read(socketfd, buffer, sizeof(buffer) - 1))  < 0) {
	   //error reading file
	   perror("plain read");
	   exit(1);
	}
	else {
	   buffer[r] = '\0'; //null terminate string
	   printf("%s", buffer); //print string received from cipher file 
 	}
   }
	
   return 0;
}

