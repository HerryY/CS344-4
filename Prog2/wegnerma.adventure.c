/**********************************************************
 * Name: Marta Wegner
 * Assignent #2
 * File Name: wegnerma.adventure.c
 * CS 344
 *********************************************************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

struct Room {
	int name;
	int connections[6];
	int numConnections;
};

/**********************************************************
 * 			createRoom
 * 	Creates room - assigns name and initializes
 * 	# of connections to 0
 *********************************************************/
void createRoom (struct Room *s, int n) {
	s->name = n;
	s->numConnections = 0;
}

/**********************************************************
 * 			updateConnections
 * 	Updates connection. If the max # of connections 
 * 	for a room has been reached returns. If a 
 * 	connections to that room is already made returns/
 * 	Else the connection is made and # of connections 
 * 	is increments and the function returns
 *********************************************************/
void updateConnection (struct Room *s, int connection) {
	if (s->numConnections == 6) {
		//Return - max # of connections reached
		printf("full: %d\n", s->numConnections);
		return;
	}
	else if (s->name == connection) {
		//Return if trying to make a connection to same room
	
		printf("name: %d\n", s->numConnections);
		return;
	}
	else {
		//If connection to that room is already made return
		int i;
		for (i = 0; i < s->numConnections; i++) {
			if (s->connections[i] == connection) {
				printf("used: %d", s->numConnections);
				return;
			}
		}

		printf("here; %d\n", s->numConnections);

		//update conncetions
		s->connections[s->numConnections] = connection;
		
		//update # connections
		s->numConnections++;
		printf("after: %d\n", s->numConnections);
	}
}

/**********************************************************
 * 			main
 *********************************************************/
int main(){
	int i;
	FILE * afile;

	//Seed rand
	srand(time(NULL));

	//Create directory variable <username>.rooms.<pid>
	char *user = "wegnerma.rooms.";

	int pid  = getpid();

	char directory[20];

	snprintf(directory, sizeof directory, "%s%d", user, pid);

	//Create directory
	mkdir(directory, 0755);

	//Create rooms
	struct Room one;
	struct Room two;
	struct Room three;
	struct Room four;
	struct Room five;
	struct Room six;
	struct Room seven;

	createRoom(&one, 1);		
	createRoom(&two, 2);	
	createRoom(&three, 3);	
	createRoom(&four, 4);	
	createRoom(&five, 5);	
	createRoom(&six, 6);	
	createRoom(&seven, 7);	

	//Create 3 connections for 1
	while(one.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		printf("r %d\n", r);
		//Update connection for A and random room
		updateConnection(&one, r);

		if (r == 2) {
			updateConnection(&two, 1);
		}
		else if (r == 3) {
			updateConnection(&three, 1);
		}
		else if (r == 4) {
			updateConnection(&four, 1);
		}
		else if (r == 5) {
			updateConnection(&five, 1);
		}
		else if (r == 6) {
			updateConnection(&six, 1);
		}
		else if (r == 7) {
			updateConnection(&seven, 1);
		}
	}
//	//Create connctions for room B
//	while(B.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for B and random room
//		updateConnection(B, r);
//
//		if (r == 'A') {
//			updateConnection(A, 'B');
//		}
//		else if (r == 'C') {
//			updateConnection(C, 'B');
//		}
//		else if (r == 'D') {
//			updateConnection(D, 'B');
//		}
//		else if (r == 'E') {
//			updateConnection(E, 'B');
//		}
//		else if (r == 'F') {
//			updateConnection(F, 'B');
//		}
//		else if (r == 'G') {
//			updateConnection(G, 'B');
//		}
//	}
//	//Create connections for room C
//	while(C.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for C and random room
//		updateConnection(C, r);
//
//		if (r == 'B') {
//			updateConnection(B, 'C');
//		}
//		else if (r == 'A') {
//			updateConnection(A, 'C');
//		}
//		else if (r == 'D') {
//			updateConnection(D, 'C');
//		}
//		else if (r == 'E') {
//			updateConnection(E, 'C');
//		}
//		else if (r == 'F') {
//			updateConnection(F, 'C');
//		}
//		else if (r == 'G') {
//			updateConnection(G, 'C');
//		}
//	}
	//Create connections for D
//	while(D.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for D and random room
//		updateConnection(D, r);
//
//		if (r == 'B') {
//			updateConnection(B, 'D');
//		}
//		else if (r == 'C') {
//			updateConnection(C, 'D');
//		}
//		else if (r == 'A') {
//			updateConnection(A, 'D');
//		}
//		else if (r == 'E') {
//			updateConnection(E, 'D');
//		}
//		else if (r == 'F') {
//			updateConnection(F, 'D');
//		}
//		else if (r == 'G') {
//			updateConnection(G, 'D');
//		}
//	}
      //Create connections for E
//	while(E.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for E and random room
//		updateConnection(E, r);
//
//		if (r == 'B') {
//			updateConnection(B, 'E');
//		}
//		else if (r == 'C') {
//			updateConnection(C, 'E');
//		}
//		else if (r == 'D') {
//			updateConnection(D, 'E');
//		}
//		else if (r == 'A') {
//			updateConnection(A, 'E');
//		}
//		else if (r == 'F') {
//			updateConnection(F, 'E');
//		}
//		else if (r == 'G') {
//			updateConnection(G, 'E');
//		}
//	}
//      //Create connections for F
//	while(F.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for A and random room
//		updateConnection(F, r);
//
//		if (r == 'B') {
//			updateConnection(B, 'F');
//		}
//		else if (r == 'C') {
//			updateConnection(C, 'F');
//		}
//		else if (r == 'D') {
//			updateConnection(D, 'F');
//		}
//		else if (r == 'E') {
//			updateConnection(E, 'F');
//		}
//		else if (r == 'A') {
//			updateConnection(A, 'F');
//		}
//		else if (r == 'G') {
//			updateConnection(G, 'F');
//		}
//	}
//      //Create connections for G
//	while(G.numConnections < 3) {
//		//Generate random room
//		char r = (rand() % 7) + 65;	
//
//		//Update connection for A and random room
//		updateConnection(G, r);
//
//		if (r == 'B') {
//			updateConnection(B, 'G');
//		}
//		else if (r == 'C') {
//			updateConnection(C, 'G');
//		}
//		else if (r == 'D') {
//			updateConnection(D, 'G');
//		}
//		else if (r == 'E') {
//			updateConnection(E, 'G');
//		}
//		else if (r == 'F') {
//			updateConnection(F, 'G');
//		}
//		else if (r == 'A') {
//			updateConnection(A, 'G');
//		}
//	}

	char file1[23];

	snprintf(file1, sizeof file1, "%s/%s", directory, "1");
//	snprintf (fileB, sizeof fileB, "%s/%s", directory, "B");
//	snprintf(fileC, sizeof fileC, "%s/%s", directory, "C");
//	snprintf(fileD, sizeof fileD, "%s/%s", directory, "D");
//	snprintf(fileE, sizeof fileE, "%s/%s", directory, "E");
//	snprintf(fileF, sizeof fileF, "%s/%s", directory, "F");
//	snprintf(fileG, sizeof fileG, "%s/%s", directory, "G");
     
	printf("%s", file1);
 
	afile = fopen(file1, "w" );

	if (!afile) {
		printf("Failed");
	}
	else {	
	printf("%d", one.numConnections);
	for (i = 0; i < one.numConnections; i++){
		fprintf(afile, "%d\n", one.connections[i]);
	}
	}

      close();

	//exit(0);
}
