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
	printf("socket creation error\n");
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
	printf("bind call failed\n");
	exit(1);
   }

   //Listen for connections
   if(listen(socketfd, 5) == -1) {//listen
	//If listen call error
	printf("listen call failed\n");
	exit(1);
   }

   //loop and accept
   while(1) { //loop
	//accpet
	client_socket = accept(socketfd, NULL, NULL);
	if (client_socket == -1) {
	    //if accept fails	
	    printf("accept call failed\n");
	    exit(1);
	}
	
	//fork
	int pid = fork();

	if (pid == -1) {//fork error
	   printf("fork error\n");
	}
	else if(pid == 0) {//child
	   //Send connection confimation num
	   int toSend = htonl(1);

	   if(send(client_socket, &toSend, sizeof(toSend),
		    0) == -1){
		//If confirmation number failed to send
		printf("client send failed\n");
		exit(1);
	   }

	   //get size of plain text
	   int pNum;
	   if(recv(client_socket, &pNum, sizeof(pNum), 0) == -1) {
		//Error receiving
		printf("recv plain text size end_d -1\n");
	   }
	   else if(pNum == 0) {
		//Plain text file size == 0
		printf("recv plain text size of 0\n");
	   }
		
	   //pLen == length of plain text file
	   int pLen = ntohl(pNum);//convert
	   
	   //get size of key text
	   int kNum;
	   if(recv(client_socket, &kNum, sizeof(kNum), 0) == -1) {
		//Error receiving size
		printf("recv key text size end_d -1\n");
	   }
	   else if(kNum == 0) {
		//If size of key file == 0
		printf("recv key text size of 0\n");
	   }

	   //kLen == length of key file
	   int kLen = ntohl(kNum);//convert

	   //Allocate memory for plain text
   	   char *plainText = malloc(sizeof(char) * pLen); 
   	   char buffer[1024];

	   //Receive plain text
	   int len = 0;
	   int r;
	   while(len < pLen) {
	      r = recv(client_socket, buffer, pLen, 0);
	      len += r;
	
	      if (r <= pLen) {
		   if(r == -1) {
		       //Error receiving data
		       printf("recv plain text file -1\n");
			exit(1);
		   }
		   if (r == 0) {
		       //end of data
		       if (len < pLen) {
			   printf("%recv plain text file <\n",len,pLen);
			   exit(1);
			}
		   }
		   else {
	 		//Concat string
	 		//Add to length
			strncat(plainText,buffer,r);
		   }
	      } 
	   }
	
	   //Allocate memory for key text
   	   char *keyText = malloc(sizeof(char) * kLen); 
   	   //clear buffer
   	   memset((char *)&buffer, '\0', sizeof(buffer));

	   //Receive plain text
	   len = 0;
	   while(len < kLen) {
	      r = recv(client_socket, buffer, kLen, 0);
	      len += r;
	
	      if (r <= kLen) {
		   if(r == -1) {
		       //Error receiving data
		       printf("recv key text file -1\n");
			exit(1);
		   }
		   if (r == 0) {
		       //end of data
		       if (len < pLen) {
			   printf("recv plain text file <\n");
			   exit(1);
			}
		   }
		   else {
	 		//Concat string
	 		//Add to length
			strncat(keyText,buffer,r);
		   }
	      } 
	   }
 printf("%s\n",keyText);
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
