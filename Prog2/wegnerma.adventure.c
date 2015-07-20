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
				
	//Create 3 connections for 2
	while(two.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&two, r);

		if (r == 1) {
			updateConnection(&one, 2);
		}
		else if (r == 3) {
			updateConnection(&three, 2);
		}
		else if (r == 4) {
			updateConnection(&four, 2);
		}
		else if (r == 5) {
			updateConnection(&five, 2);
		}
		else if (r == 6) {
			updateConnection(&six, 2);
		}
		else if (r == 7) {
			updateConnection(&seven, 2);
		}
	}
	//Create 3 connections for 3
	while(three.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&three, r);

		if (r == 2) {
			updateConnection(&two, 3);
		}
		else if (r == 1) {
			updateConnection(&one, 3);
		}
		else if (r == 4) {
			updateConnection(&four, 3);
		}
		else if (r == 5) {
			updateConnection(&five, 3);
		}
		else if (r == 6) {
			updateConnection(&six, 3);
		}
		else if (r == 7) {
			updateConnection(&seven, 3);
		}
	}
	//Create 3 connections for 4
	while(four.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&four, r);

		if (r == 2) {
			updateConnection(&two, 4);
		}
		else if (r == 3) {
			updateConnection(&three, 4);
		}
		else if (r == 1) {
			updateConnection(&one, 4);
		}
		else if (r == 5) {
			updateConnection(&five, 4);
		}
		else if (r == 6) {
			updateConnection(&six, 4);
		}
		else if (r == 7) {
			updateConnection(&seven, 4);
		}
	}
	//Create 3 connections for 5
	while(five.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&five, r);

		if (r == 2) {
			updateConnection(&two, 5);
		}
		else if (r == 3) {
			updateConnection(&three, 5);
		}
		else if (r == 4) {
			updateConnection(&four, 5);
		}
		else if (r == 1) {
			updateConnection(&one, 5);
		}
		else if (r == 6) {
			updateConnection(&six, 5);
		}
		else if (r == 7) {
			updateConnection(&seven, 5);
		}
	}
	//Create 3 connections for 6
	while(six.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&six, r);

		if (r == 2) {
			updateConnection(&two, 6);
		}
		else if (r == 3) {
			updateConnection(&three, 6);
		}
		else if (r == 4) {
			updateConnection(&four, 6);
		}
		else if (r == 5) {
			updateConnection(&five, 6);
		}
		else if (r == 1) {
			updateConnection(&one, 6);
		}
		else if (r == 7) {
			updateConnection(&seven, 6);
		}
	}
	//Create 3 connections for 1
	while(seven.numConnections < 3) {
		//Generate random room
		int r = (rand() % 7) + 1;	

		//Update connection for A and random room
		updateConnection(&seven, r);

		if (r == 2) {
			updateConnection(&two, 7);
		}
		else if (r == 3) {
			updateConnection(&three, 7);
		}
		else if (r == 4) {
			updateConnection(&four, 7);
		}
		else if (r == 5) {
			updateConnection(&five, 7);
		}
		else if (r == 6) {
			updateConnection(&six, 7);
		}
		else if (r == 1) {
			updateConnection(&one, 7);
		}
	}

	char file[22];

	//Create and write to room files
	for (i = 1; i < 8; i++) {
		//File pathway
		snprintf(file, sizeof file, "%s/%d", directory, i);
	
		//open file
		afile = fopen(file, "w");

		//Info for file
		int numCon;
		int * con;
		if (i == 1) {
			numCon = one.numConnections;
			con = one.connections;
		}
		else if (i == 2) {
			numCon = two.numConnections;
			con = two.connections;
		}
		else if (i == 3) {
			numCon = three.numConnections;
			con = three.connections;
		}
		else if (i == 4) {
			numCon = four.numConnections;
			con = four.connections;
		}
		else if (i == 5) {
			numCon = five.numConnections;
			con = five.connections;
		}
		else if (i == 6) {
			numCon = six.numConnections;
			con = six.connections;
		}
		else if (i == 7) {
			numCon = seven.numConnections;
			con = seven.connections;
		}		

		//Write name to file
		fprintf(afile, "ROOM NAME: %d\n", i);
		//Write connections to files
		int j;
		for (j = 0; j < numCon; j++) {
			fprintf(afile, "CONNECTION %d: %d\n", j + 1, con[j]);
		}

		close(afile);
      }

	//exit(0);
}
