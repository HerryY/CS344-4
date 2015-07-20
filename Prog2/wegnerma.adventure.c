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
	if (s.numConnections == 6) {
		//Return - max # of connections reached
		return;
	}
	else if (s.name == connection) {
		//Return if trying to make a connection to same room
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
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for A and random room
		updateConnection(A, r);

		if (r == 'B') {
			updateConnection(B, 'A');
		}
		else if (r == 'C') {
			updateConnection(C, 'A');
		}
		else if (r == 'D') {
			updateConnection(D, 'A');
		}
		else if (r == 'E') {
			updateConnection(E, 'A');
		}
		else if (r == 'F') {
			updateConnection(F, 'A');
		}
		else if (r == 'G') {
			updateConnection(G, 'A');
		}
	}
	//Create connctions for room B
	while(B.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for B and random room
		updateConnection(B, r);

		if (r == 'A') {
			updateConnection(A, 'B');
		}
		else if (r == 'C') {
			updateConnection(C, 'B');
		}
		else if (r == 'D') {
			updateConnection(D, 'B');
		}
		else if (r == 'E') {
			updateConnection(E, 'B');
		}
		else if (r == 'F') {
			updateConnection(F, 'B');
		}
		else if (r == 'G') {
			updateConnection(G, 'B');
		}
	}
	//Create connections for room C
	while(C.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for C and random room
		updateConnection(C, r);

		if (r == 'B') {
			updateConnection(B, 'C');
		}
		else if (r == 'A') {
			updateConnection(A, 'C');
		}
		else if (r == 'D') {
			updateConnection(D, 'C');
		}
		else if (r == 'E') {
			updateConnection(E, 'C');
		}
		else if (r == 'F') {
			updateConnection(F, 'C');
		}
		else if (r == 'G') {
			updateConnection(G, 'C');
		}
	}
	//Create connections for D
	while(D.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for D and random room
		updateConnection(D, r);

		if (r == 'B') {
			updateConnection(B, 'D');
		}
		else if (r == 'C') {
			updateConnection(C, 'D');
		}
		else if (r == 'A') {
			updateConnection(A, 'D');
		}
		else if (r == 'E') {
			updateConnection(E, 'D');
		}
		else if (r == 'F') {
			updateConnection(F, 'D');
		}
		else if (r == 'G') {
			updateConnection(G, 'D');
		}
	}
	//Create connections for E
	while(E.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for E and random room
		updateConnection(E, r);

		if (r == 'B') {
			updateConnection(B, 'E');
		}
		else if (r == 'C') {
			updateConnection(C, 'E');
		}
		else if (r == 'D') {
			updateConnection(D, 'E');
		}
		else if (r == 'A') {
			updateConnection(A, 'E');
		}
		else if (r == 'F') {
			updateConnection(F, 'E');
		}
		else if (r == 'G') {
			updateConnection(G, 'E');
		}
	}
	//Create connections for F
	while(F.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for A and random room
		updateConnection(F, r);

		if (r == 'B') {
			updateConnection(B, 'F');
		}
		else if (r == 'C') {
			updateConnection(C, 'F');
		}
		else if (r == 'D') {
			updateConnection(D, 'F');
		}
		else if (r == 'E') {
			updateConnection(E, 'F');
		}
		else if (r == 'A') {
			updateConnection(A, 'F');
		}
		else if (r == 'G') {
			updateConnection(G, 'F');
		}
	}
	//Create connections for G
	while(G.numConnections < 3) {
		//Generate random room
		char r = (rand() % 7) + 65;	

		//Update connection for A and random room
		updateConnection(G, r);

		if (r == 'B') {
			updateConnection(B, 'G');
		}
		else if (r == 'C') {
			updateConnection(C, 'G');
		}
		else if (r == 'D') {
			updateConnection(D, 'G');
		}
		else if (r == 'E') {
			updateConnection(E, 'G');
		}
		else if (r == 'F') {
			updateConnection(F, 'G');
		}
		else if (r == 'A') {
			updateConnection(A, 'G');
		}
	}

	//exit(0);
}
