/**********************************************************
 * Name: Marta Wegner
 * File: otp_enc_d.c
 * Description: Performs encoding. Listens on a particular 
 * port that is assigned when it is run, and receives 
 * plain text and a key via that port. Must output error
 * if the program cannot be run due to a network error.
 *
 * Makes a connection to opt_enc, and forks a process so
 * it is available to receive more connections (supports up
 * to 5 connections.) 
 *
 * In forked process, encyption takes place and ciphertext 
 * is written back.
 *
 * syntx: otp_enc_c listening port
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

int main(int argc, char ** argv) {
   int i;
   int listeningPort;
   int socketfd;
   int client_socket;
   int status;

   //if port not specified
   if (argc < 2) {
	printf("You must include a port number\n");
	exit(1);
   }
   else {
   	//get listening port from args
   	listeningPort = atoi(argv[1]);
   }

   //Server
   //Create socket
   if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {//Create
	//If error
	perror("socket");
	exit(1);
   }

   //Fill addr struct
   struct sockaddr_in server;

   server.sin_family = AF_INET;
   server.sin_port = htons(listeningPort);
   server.sin_addr.s_addr = INADDR_ANY;

   //bind socket to port
   if(bind(socketfd, (struct sockaddr *) &server, sizeof(server)) == -1) {//bind
	//if bind error
	perror("bind call failed");
	exit(1);
   }

   //Listen for connections
   if(listen(socketfd, 5) == -1) {//listen
	//If listen call error
	perror("listen call failed");
	exit(1);
   }

   //loop and accept
   while(1) { //loop
	//accpet
	client_socket = accept(socketfd, NULL, NULL);
	if (client_socket == -1) {
	    //if accept fails	
	    perror("accept call failed");
	    exit(1);
	}
	
	//fork
	int pid = fork();

	if (pid == -1) {//fork error
	   perror("fork");
	}
	else if(pid == 0) {//child
	   //Send connection confimation num
	   int toSend = htonl(1);

	   if(send(client_socket, &toSend, sizeof(toSend),
		    0) == -1){
		//If confirmation number failed to send
		perror("client send failed");
		exit(1);
	   }

	   //get size of plain text
	   int pNum;
	   if(recv(client_socket, &pNum, sizeof(pNum), 0) == -1) {
		//Error receiving
		perror("recv plain text size end_d -1");
	   }
	   else if(pNum == 0) {
		//Plain text file size == 0
		perror("recv plain text size of 0");
	 	exit(1);
	   }
		
	   //pLen == length of plain text file
	   int pLen = ntohl(pNum);//convert
	   
	   //get size of key text
	   int kNum;
	   if(recv(client_socket, &kNum, sizeof(kNum), 0) == -1) {
		//Error receiving size
		perror("recv key text size end_d -1");
	   }
	   else if(kNum == 0) {
		//If size of key file == 0
		perror("recv key text size of 0");
	 	exit(1);
	   }

	   //kLen == length of key file
	   int kLen = ntohl(kNum);//convert
	}
	else {//parent
	   //close client connection
	   close(client_socket);

	   //Children finished?
	   do {
		waitpid(pid, &status, 0);
	   } while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
   }
	
   //close socket
   close(socketfd);

   return 0;
}
