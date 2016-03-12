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
	//Print error
	fprintf(stderr, "You must include a port number\n");
	exit(1);
   }
   else {
   	//get listening port from args
   	listeningPort = atoi(argv[1]);
   }

   //Server
   //Create socket
   if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {//Create
	//If error print msg
	fprintf(stderr, "socket creation error\n");
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
	fprintf(stderr, "bind call failed\n");
	exit(1);
   }

   //Listen for connections
   if(listen(socketfd, 5) == -1) {//listen
	//If listen call error
	fprintf(stderr, "listen call failed\n");
	exit(1);
   }

   //loop and accept
   while(1) { //loop
	//accpet
	client_socket = accept(socketfd, NULL, NULL);
	if (client_socket == -1) {
	    //if accept fails	
	    fprintf(stderr, "accept call failed\n");
	    exit(1);
	}
	
	//fork
	int pid = fork();

	if (pid == -1) {//fork error
	   fprintf(stderr, "fork error\n");
	}
	else if(pid == 0) {//child
	   //Send connection confimation num(1)
	   //to confirm otp_enc is trying to 
	   //connect
	   int toSend = htonl(1);

	   if(send(client_socket, &toSend, sizeof(toSend),
		    0) == -1){
		//If confirmation number failed to send
		fprintf(stderr, "client send failed\n");
		exit(1);
	   }

	   //get size of plain text
	   int pNum;
	   if(recv(client_socket, &pNum, sizeof(pNum), 0) == -1) {//receive
		//Error receiving
		fprintf(stderr, "recv plain text size end_d -1\n");
	   }
	   else if(pNum == 0) {
		//Plain text file size == 0
		fprintf(stderr, "recv plain text size of 0\n");
	   }
		
	   //pLen == length of plain text file
	   int pLen = ntohl(pNum);//convert
	   
	   //get size of key text
	   int kNum;
	   if(recv(client_socket, &kNum, sizeof(kNum), 0) == -1) {//receive
		//Error receiving size
		fprintf(stderr, "recv key text size end_d -1\n");
	   }
	   else if(kNum == 0) {
		//If size of key file == 0
		fprintf(stderr, "recv key text size of 0\n");
	   }

	   //kLen == length of key file
	   int kLen = ntohl(kNum);//convert

	   //Allocate memory for plain text
   	   char *plainText = malloc(sizeof(char) * pLen); 
   	   char buffer[1024];

	   //Clear plain text
   	   memset(plainText, '\0', pLen);

	   //Receive plain text
	   int len = 0;
	   int r;
	   while(len <= pLen) {//while the whole file has 
			      //not been received
	      memset((char *)buffer, '\0', sizeof(buffer));//clear buffer each use

	      r = recv(client_socket, &buffer, 1024, 0);//receive

 	      if(r == -1) {
		 //Error receiving data
		 fprintf(stderr, "recv plain text file -1\n");
		 break;
	      }
	      else if (r == 0) {
		 //end of data
		 if (len < pLen) {//If not enough received
		   break;
		 }
	      }
	      else {
	 	//Concat string
		strncat(plainText,buffer,(r - 1));
	      } 

	      len += (r-1);//add len received to total len received
	   }

	   plainText[pLen - 1] = '\0'; //null terminate

	   //Allocate memory for key text
   	   char *keyText = malloc(sizeof(char) * kLen); 
   	   //clear buffer and key
   	   memset((char *)buffer, '\0', sizeof(buffer));
	   memset(keyText, '\0', kLen);

	   //Receive key text
	   len = 0;

	   while(len <= kLen) {//while whole string not received
	      //clear buffer each use
   	      memset((char *)buffer, '\0', sizeof(buffer)); 

	      r = recv(client_socket, &buffer, 1024, 0);//receive

	   	if(r == -1) {
		   //Error receiving data
		   fprintf(stderr, "recv key text file -1\n");
	  	   break;
	   	}
	   	else if (r == 0) {
		       //end of data
		       break;
		   }
		   else {
	 		//Concat string
			strncat(keyText,buffer,(r - 1));
		   }
	       
	      len += (r - 1);//add len recived to total len received
	   }

	   keyText[kLen - 1] = '\0';

	   int plainNum;
	   int keyNum;
	   int enNum;
	   //Encrypt the plain text file using key
	   for (i = 0; i < pLen - 1; i++) {
		//change plain chars to ints 0-26
		if(plainText[i] == ' ') {//space
		  plainNum = 26;
		}
		else {//letter
		   plainNum = plainText[i] - 65;
		}

		//change key chars to ints 0-26
		if(keyText[i] == ' ') {//space
		   keyNum = 26;
		}
		else {
		   keyNum = keyText[i] - 65;
		}

		//Determine encrypted char
		enNum = plainNum + keyNum;
		if (enNum >= 27) {//If >= 27 subtract 27
		   enNum -= 27;
		}

		//replace plain char with encrypted char
		if(enNum == 26) { //space
		   plainText[i] = ' ';
		}
		else {//letter
		   plainText[i] = 'A' + (char)enNum;
		}
	   }

	   //send back encrypted file
	   len = 0;
	   while (len <= pLen) { //While whole file is not sent
		char cipherSend[1024];
	
		//Copy subsection of string to send	
		strncpy(cipherSend, &plainText[len], 1023);

		cipherSend[1024] = '\0'; //null terminate

   		if(send(client_socket, &cipherSend, 1024, 0) == -1) {
		    fprintf(stderr, "encryption text send\n");
		}

		len += 1023; //Add sent  lenght to len
	   }

	   //free memory
	   free(plainText);
	   free(keyText);
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
