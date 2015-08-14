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

int main(int argc, char* argv[]) {
   int ilisteningPort;   
   int socketfd;
   struct sockaddr_in server;
   struct sockaddr_in client;
   int clientSockfd;

   if(argv < 2) { //port # is not specified
	printf("You must include a port number\n");
	exit(1);
   }
   else {
	//Else get port # from args
	listeningPort = atoi(argv[1]);
   }

   //create socket to listen to
   if (socketfd = socket(AF_INET, SOCK_STREAM, 0) == -1) { //Create
	//If error creating
	perror("socket");
	exit(1);
   }
 
     //bind socket to a port
   if(bind(socketfd, (sruct sockaddr *) &server, sizeof(server)) == -1) {
	//If error binding
	perror("bind");
	exit(1);
   }

    //Fill in socket address sruct
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(listeningPort);
  
   //Listen for connections
   if(listen(sockfd, 5) == -1) {
	//If error listening
	perror("listen");
	exit(1);
   }

    while(1) {
	//Accept connections
	clientSockfd = 
	accept(sockfd, (struct sockaddr *) &client, sizeof(client));

	//If error accepting
	if (clientSockfd == -1) {
		perror("accept");
	}

	//fork
	pid = fork();

	if (pid == -1) {
	   perror("fork");
	}
	else if(pid == 0) { //child
	  
	}
	else { //Parent

	}

   }

   return 0;
}
