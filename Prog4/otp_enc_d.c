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


int main(int argc, char **argv) {
   int i;
   int listeningPort;   
   int socketfd;
   struct sockaddr_in server;
   struct sockaddr_in client;
   int clientSockfd;
   int pid;
   char buffer[1024];
   int plength, klength, length;
   char* plainText;
   char* keyText;
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

     //fill socket struct with zeros 
     memset((char *)&server, 0, sizeof(server));

     //Fill in socket address sruct
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(listeningPort);

    //bind socket to a port
   if(bind(socketfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
	//If error binding
	perror("bind");
	exit(1);
   }

  //Listen for connections
   if(listen(socketfd, 5) == -1) {
	//If error listening
	perror("listen");
	exit(1);
   }

    while(1) {
      //Accept connections
      socklen_t clieSize = sizeof(client); 

       clientSockfd = accept(socketfd, (struct sockaddr *) &client, &clieSize);

	   //If error accepting
	   if (clientSockfd == -1) {
		 perror("accept");
		 exit(1);
	   }

       // Fork
       pid = fork();

       if(pid == -1) { //Fork error
           perror("fork");
       }
       else if(pid == 0) { //child
           // Close server connection
           close(socketfd);

           //Send 1 to client to connfim correct connection
            int toSend = htonl(1); //convert

			 if(send(clientSockfd, &toSend, sizeof(toSend), 0) == -1) {
				perror("client send failed");
				exit(1);
			}

           // get size of plain text
			int num;
           if(recv(clientSockfd, &num, sizeof(num), 0) == -1) {
				perror("recv plain text enc_d -1");
				exit(1);
			}
			else if(num == 0) {
				perror("recv plain text enc_d 0");
				exit(1);
			}

			plength = ntohl(num); // Convert
           
           // Get the key file size
           if(recv(clientSockfd, &num, sizeof(num), 0) == -1) {
				perror("recv key text enc_d -1");
				exit(1);
			}
			else if(num == 0) {
				perror("recv key text enc_d 0");
				exit(1);
			}

			klength = ntohl(num); // Convert

           // Create string long enough to hold file
           plainText = malloc(sizeof(char) * (plength));
      
           // Get the plain text file
            length = 0;
			printf("len: %d\n", length);
			printf("plen: %d\n", plength);
	
			while (length < plength) { //recieve until whole file is recieved
				printf("num: %d\n", num);
				//receive file
				if((num = recv(clientSockfd, buffer, sizeof(buffer), 0)) == -1) { 
					perror("encd p recv -1");
					exit(1);
				}
				else if(num == 0) {
					perror("recv 0");
					exit(1);
				}
				else {
					strncat(plainText, buffer, num);
					length += num;	
				}
			}

			// Create string long enough to hold file
           keyText = malloc(sizeof(char) * (klength));
      
           // Get the key text file
            length = 0;
	
			while (length < klength) { //receive until whole file is received
				//receive file
				if((num = recv(clientSockfd, buffer, sizeof(buffer), 0)) == -1) { 
					perror("encd k recv -1");
					exit(1);
				}
				else if(num == 0) {
					perror("recv 0");
					exit(1);
				}
				else {
					strncat(keyText, buffer, num);
					length += num;	
				}
			}

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
		    if(send(clientSockfd, plainText, plength, 0) == -1) {
				perror("send cipher");
				exit(1);
			}
       }
       else { //parent
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

   //close socket
   close(socketfd);

    return 0;
}