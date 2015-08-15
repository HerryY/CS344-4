/**********************************************************
 *  Name: Marta Wegner
 * CS 344
 * Program #4
 * filename: otp_enc_d.c
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

int main(int argc, char* argv[]) {
   int i;
   int listeningPort;   
   int socketfd;
   struct sockaddr_in server;
   struct sockaddr_in client;
   int clientSockfd;
   int pid;
   char buf[64];
   char *message = "enc_d";
   char *receive = "received";
   int plength;
   int klength;
   char* plainText;
   char* keyText;
   int r;
   int w;
   int textChar;
   int keyChar;
   int enChar;
   int status;

   if(argc < 2) { //port # is not specified
	printf("You must include a port number\n");
	exit(1);
   }
   else {
	//Else get port # from args
	listeningPort = atoi(argv[1]);
   }

   //create socket to listen to
   if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //Create
	//If error creating
	perror("socket");
	exit(1);
   }

    //Fill in socket address sruct
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(listeningPort);
 
     //bind socket to a port
   if((bind(socketfd, (struct sockaddr *) &server, sizeof(server))) == -1) {
	//If error binding
	perror("bind");
	exit(1);
   }
  
   //Listen for connections
   if((listen(socketfd, 5)) == -1) {
	//If error listening
	perror("listen");
	exit(1);
   }

    while(1) {
	//Accept connections
	int clieSize = sizeof(client); 
	clientSockfd = 
	accept(socketfd, (struct sockaddr *) &client, &clieSize);

	//If error accepting
	if (clientSockfd == -1) {
		perror("accept");
	}

	//fork
	pid = fork();

	if (pid == -1) {
	   //fork() error
	   perror("fork");
	}
	else if(pid == 0) { //child
	   close(socketfd);

	   //confirm connection
	   read(clientSockfd, buf, sizeof(buf)-1);
	   if(strcmp(buf, "enc") != 0) { //compare string read from client
					//to correct confirmation string
		//if != error with connection to client
	 	perror("client error");
		exit(2);
	   }
	   else {
		//send confirmation
		write(clientSockfd, &message, sizeof(message));
	   }
	
  	   //get length of file from client
	   read(clientSockfd, &plength, sizeof(int));

	   //get plain text file
	   //create string that is the correct length
	   plainText = (char*)malloc(plength);

	   //get plain text until length reached
	   for (i = 0; i < plength; i += r ) {
		 if ((r = read(clientSockfd, plainText + i, plength - i)) < 0) {
		   //error getting plain text file
		   perror("read plain text");
		   exit(1);
		}
	   }

	   //send message back to indicate done receiving
	   write(clientSockfd, receive, sizeof(receive));

	   //get length of key file
	   read(clientSockfd, &klength, sizeof(int));

	    //get key file
	   //create string that is the correct length
	   keyText = (char*)malloc(klength);

	   //get key text until length reached
	   for (i = 0; i < klength; i += r ) {
		 if ((r = read(clientSockfd, keyText + i, klength - i)) < 0) {
		   //error getting key text file
		   perror("read key text");
		   exit(1);
		}
	   }

	   //send message back to indicate done receiving
	   write(clientSockfd, receive, sizeof(receive));

	   //encrypt the plainText file using key
	   for (i = 0; i < plength; i++) {
		//change plain text chars to ints 0-26
		if (plainText[i] == ' ') { //space
		   textChar = 26;   
		}	   
		else { //letter
		   textChar = plainText[i] - 65;
		}

		//change key chars to ints 0-26
		if(keyText[i] == ' ') { //space
		   keyChar = 26;
		}
		else { //letter
		   keyChar = plainText[i] - 65;
		
		}

		//Determine encrypted char
		enChar = (textChar - keyChar) % 27;

		//replace encrypted char
		if (enChar == 26) { //space
		   plainText[i] = ' ';
		}
		else { //letter
		   plainText[i] = 'A' + (char)enChar;
		}
	   }

	   //send cipher file
	   for(i = 0; i < plength; i += w) { //send until length of 
					     //file reached
		if ((w = write(clientSockfd, plainText + i, plength - i)) < 0) {
		   //error sending cipher file
		   perror("cipher write");
		   exit(1);
		}
	   }
	}
	else { //Parent
	    //close client socket
	    close(clientSockfd);

	   //children finsihed?
	   do {
		pid = waitpid(-1, &status, WNOHANG);
	   } while( pid > 0);	
	}
   }

   //free memory 
   free(plainText);
   free(keyText);

   close(socketfd);

   return 0;
}
