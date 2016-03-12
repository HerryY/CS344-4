/**********************************************************
 * Name: Marta Wegner
 * File: otp_dec_d.c
 * Description: Performs decoding. Listens on a particular 
 * port that is assigned when it is run, and receives 
 * cipher text and a key via that port. Outputs error
 * if the program cannot be run due to a network error.
 *
 * Makes a connection to opt_dec, and forks a process so
 * it is available to receive more connections (supports up
 * to 5 connections.) 
 *
 * In forked process, encyption takes place and plaintext 
 * is written back.
 *
 * syntx: otp_dec_c listening port
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
	   //to confirm otp_dec is trying to 
	   //connect
	   int toSend = htonl(0);

	   if(send(client_socket, &toSend, sizeof(toSend),
		    0) == -1){
		//If confirmation number failed to send
		fprintf(stderr, "client send failed\n");
	   }

	   //get size of cipher text
	   int cNum;
	   if(recv(client_socket, &cNum, sizeof(cNum), 0) == -1) {//receive
		//Error receiving
		fprintf(stderr, "recv cipher text size end_d -1\n");
	   }
	   else if(cNum == 0) {
		//Plain text file size == 0
		fprintf(stderr, "recv cipher text size of 0\n");
	   }
		
	   //cLen == length of cipher text file
	   int cLen = ntohl(cNum);//convert
	   
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

	   //Allocate memory for cipher text
   	   char *cipherText = malloc(sizeof(char) * cLen); 
   	   char buffer[1024];

	   //Clear cipher text
   	   memset(cipherText, '\0', cLen);

	   //Receive cipher text
	   int len = 0;
	   int r;
	   while(len <= cLen) {//while the whole file has 
			      //not been received
	      memset((char *)buffer, '\0', sizeof(buffer));//clear buf each use
	      r = recv(client_socket, &buffer, 1024, 0);//receive

	      if(r == -1) {
		//Error receiving data
		fprintf(stderr, "recv cipher text file -1\n");
		break;
	      }
	      else if (r == 0) {
		//end of data
		if (len < cLen) {//If not enough received
		   break;
		}
	      }
	      else {
		//Concat string
		strncat(cipherText,buffer,(r-1));
	      }

	      len += (r-1);//add len received to total len 
	   }

	   cipherText[cLen - 1] = '\0';//null terminate
	
	   //Allocate memory for key text
   	   char *keyText = malloc(sizeof(char) * kLen); 
   	   //clear buffer and key
   	   memset((char *)&buffer, '\0', sizeof(buffer));
	   memset(keyText, '\0', kLen);

	   //Receive key text
	   len = 0;

	   while(len <= kLen) {//while whole string not received
	      //clear buffer each use
	      memset((char *) buffer, '\0', sizeof(buffer));

	      r = recv(client_socket, &buffer, 1024, 0);//receive

		   if(r == -1) {
		       //Error receiving data
		       fprintf(stderr, "recv key text file dec_d\n");
			break;
		   }
		   else if (r == 0) {
		       //end of data
			break;
		   }
		   else {
	 		//Concat string
			strncat(keyText,buffer,(r-1));
		   }

		len += (r-1); //add len received to total len 
	   }

	   keyText[kLen - 1] = '\0';//null terminate

	   int cipherNum;
	   int keyNum;
	   int decNum;
	   //Decrypt the cipher text file using key
	   for (i = 0; i < cLen - 1; i++) {
		//change cipher chars to ints 0-26
		if(cipherText[i] == ' ') {//space
		  cipherNum = 26;
		}
		else {//letter
		   cipherNum = cipherText[i] - 65;
		}

		//change key chars to ints 0-26
		if(keyText[i] == ' ') {//space
		   keyNum = 26;
		}
		else {
		   keyNum = keyText[i] - 65;
		}

		//Determine decrypted char
		decNum = cipherNum - keyNum;
		if (decNum < 0) {//If neg add 27
		   decNum += 27;
		}

		//replace cipher char with decrypted char
		if(decNum == 26) { //space
		   cipherText[i] = ' ';
		}
		else {//letter
		   cipherText[i] = 'A' + (char)decNum;
		}
	   }

	   //send back decrypted file
	   len  = 0;

	   while (len <= cLen) {//while whole file is not sent
		char plainSend[1024];

		//Copy subsect to send
		strncpy(plainSend, &cipherText[len], 1023);

		plainSend[1024] = '\0'; //null terminate

		//send subset
   	   	if(send(client_socket, &plainSend, 1024, 0) == -1) {
		   fprintf(stderr, "decryption text send\n");
	   	}

		len += 1023; //add sent len to total leni
	   }

	   //free memory
	   free(cipherText);
//	   free(keyText);
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
