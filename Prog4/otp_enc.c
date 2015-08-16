/**********************************************************
 *  Name: Marta Wegner
 * CS 344
 * Program #4
 * filename: otp_enc.c
 *********************************************************/
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


int main(int argc, char **argv)
{
	int i;
    int fdPlain;
    int fdKey;
    int portno;
    char buffer[1024];
    int connection;
	int conNum;
    int socketfd;
    struct hostent *server_ip_address;
    struct sockaddr_in server;
    int plength, klength, length;
	int pChars, kChars;
    char *plainText, *keyText;    

    if (argc < 4) {
	  fprintf(stderr, "Must specify plaintext, key, and port number\n");
	  exit(1);
    }

	//get port number form args
    portno = atoi(argv[3]);

   //open plain text and key files for reading
   fdPlain = open(argv[1], O_RDONLY);
   fdKey = open(argv[2], O_RDONLY);

   //check that there was not an error opening
   if(fdPlain == -1 || fdKey == -1) {
	  perror("open");
	  exit(1);
   }

    // get size of plain text
    plength = lseek(fdPlain, 0, SEEK_END);
    
	//get size of key text
    klength = lseek(fdKey, 0, SEEK_END);
 
    // Verify that the key file is larger than the input file
    if(klength < plength) { //compare plain text length to 
        perror("Key too short");
		exit(1);
    }

    // Create string long enough to hold text file contents
    plainText = malloc(sizeof(char) * plength);
   
    // Read plain text into string
	//Store # of chars
    pChars = read(fdPlain, plainText, plength);
    if(pChars == -1){
        perror("read plain text enc");
        exit(1);
    }

    //null terminate string
    plainText[plength - 1] = '\0';

	//check for valid chars
    for(i = 0; i < strlen(plainText); i++) {
        if(plainText[i] != ' ' && (plainText[i] > 'Z' || plainText[i] < 'A'))
        {
			//If not letter or space it is invalid
            perror("Plaintext invalid chars");
			exit(1);
        }
    }

    // Allocate memory for key text
    keyText = malloc(sizeof(char) * klength);

    // Read in key text
    kChars = read(fdKey, keyText, klength);

	//If error reading key text
    if(kChars == -1){
        perror("read key text enc");
        exit(1);
    }

    // Null terminate key string
    keyText[klength - 1] = '\0';

    //create socket
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
		//Error if cannot create
        perror("socket");
        exit(1);
    }

    //Setting up address
       server_ip_address = gethostbyname("localhost");

    if(server_ip_address == NULL) {
	   fprintf(stderr, "could not resolve host name\n");
	   exit(1);
     }

     //fill socket struct with zeros 
     memset((char *)&server, 0, sizeof(server));

    // Fill in address structure
    server.sin_family = AF_INET;
    server.sin_port = htons(portno); 
    memcpy(&server.sin_addr, server_ip_address->h_addr_list[0], server_ip_address->h_length);

    //connect to server
    if(connect(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
		//Error if cannot connet
        perror("connect failed");
        exit(1);
    }
    
	//confirm connection
    if((connection = recv(socketfd, &conNum, sizeof(conNum), 0)) == -1)
    {
        perror("recv enc");
        exit(1);
    }
    else if(connection == 0)
    {
        perror("recv 0 enc");
        exit(1);
    }

    int serverNum = ntohl(conNum); 

	//If the number received does not match
    if(serverNum != 1) {
	    fprintf(stderr, "could not contact otp_enc_d on port %d\n", portno); 
     	exit(2);
    }

	 //send plain text file size
     int psend = htonl(plength); //convert

    if(send(socketfd, &psend, sizeof(psend), 0) == -1) {
        perror("plain text size send");
        exit(1);
    }

    // send key text file size
     int ksend = htonl(klength); //convert

    if(send(socketfd, &ksend, sizeof(ksend), 0) == -1) {
        perror("key text size send");
        exit(1);
    }
    
    // Send the plain text file
    if(send(socketfd, plainText, plength, 0) == -1)
    {
        perror("plain text send");
        exit(1);
    }

    // Send the key file
    if(send(socketfd, keyText, klength, 0) == -1)
    {
        perror("key text send");
        exit(1);
    }

    //get received file and actual received length
    length = 0;
	
	int num;
	while (length < plength) {
		//receive file
		if((num = recv(socketfd, buffer, sizeof(buffer), 0)) == -1) { 
           perror("enc recv -1");
           exit(1);
       }
       else if(num == 0)
       {
           perror("recv 0");
           exit(1);
       }
	   else {
		    strncat(plainText, buffer, num);
           length += num;	
	   }
	}

    // Print the contents of encoded file
    printf("%s\n", plainText);

    // Close the connection
    close(socketfd);

    // Free memory
	free(plainText);
	free(keyText);

	//Close file streams
    close(fdPlain);
	close(fdKey);

    return 0;
}