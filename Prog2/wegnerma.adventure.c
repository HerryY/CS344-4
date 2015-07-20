#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct Room {
	char name;
	char connections[6];
	int numConnections;
};

/**********************************************************
 * 			createRoom
 * 	Creates room - assigns name and initializes
 * 	# of connections to 0
 *********************************************************/
void createRoom (struct Room s, char n) {
	s.name = n;
	s.numConnections = 0;
}

/**********************************************************
 * 			updateConnections
 * 	Updates connection. If the max # of connections 
 * 	for a room has been reached returns. If a 
 * 	connections to that room is already made returns/
 * 	Else the connection is made and # of connections 
 * 	is increments and the function returns
 *********************************************************/
void updateConnection (struct Room s, char connection) {
	if (s.numConnections = 6) {
		//Return - max # of connections reached
		return;
	}
	else {
		//If connection to that room is already made return
		int i;
		for (i = 0; i < s.numConnections; i++) {
			if (s.connections[i] = connection) {
				return;
			}
		}

		//update conncetions
		s.connections[s.numConnections] = connection;
		
		//update # connections
		s.numConnections++;
	}
}

/**********************************************************
 * 			main
 *********************************************************/
int main(){
	//Seed rand
	srand(time(NULL));

	//Create directory variable <username>.rooms.<pid>
	char *user = "wegnerma.rooms.";

	int pid  = getpid();

	char directory[30];

	snprintf(directory, sizeof directory, "%s%d", user, pid);

	//Create directory
	mkdir(directory, 0777);

	//Create rooms
	struct Room A;
	struct Room B;
	struct Room C;
	struct Room D;
	struct Room E;
	struct Room F;
	struct Room G;

	createRoom(A, 'A');		
	createRoom(B, 'B');	
	createRoom(C, 'C');	
	createRoom(D, 'D');	
	createRoom(E, 'E');	
	createRoom(F, 'F');	
	createRoom(G, 'G');	

	//Create 3 connections for A
	while(A.numConnections < 3) {
		char r = (rand() % 7) + 65;	

		updateConnection(A, r);
	}

	//exit(0);
}
