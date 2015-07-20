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
		return;
	}
	else if (s->name == connection) {
		//Return if trying to make a connection to same room
	
		return;
	}
	else {
		//If connection to that room is already made return
		int i;
		for (i = 0; i < s->numConnections; i++) {
			if (s->connections[i] == connection) {
				return;
			}
		}

		//update conncetions
		s->connections[s->numConnections] = connection;
		
		//update # connections
		s->numConnections++;
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

	//array of rooms
	int roomArr[7];


	//rooms
	struct Room one;
	struct Room two;
	struct Room three;
	struct Room four;
	struct Room five;
	struct Room six;
	struct Room seven;
	struct Room eight;
	struct Room nine;
	struct Room ten;

	//Select and create rooms
	for (i = 0; i < 7; i++) {
		int unique = 0;
		int roomNum;
	
		//Generate random room number while roomNum is in 
		//roomArr
		while (!unique) {	
			roomNum = (rand() % 10) + 1;

			unique = 1;
			int u;
			for (u = 0;  u < i; u++) {
				if (roomArr[u] == roomNum) {
					unique = 0;
				}
			}
		}

		//Add room to arr
		roomArr[i] = roomNum;

		//Create room and initilaize
		if ( roomNum == 1) {	
			createRoom(&one, 1);
		}
		else if(roomNum == 2) {
			createRoom(&two, 2);
		}
		else if(roomNum == 3) {
			createRoom(&three, 3);
		}
		else if(roomNum == 4) {
			createRoom(&four, 4);
		}	
		else if(roomNum == 5) {
			createRoom(&five, 5);
		}
		else if(roomNum == 6) {
			createRoom(&six, 6);
		}
		else if(roomNum == 7) {
			createRoom(&seven, 7);
		}
		else if(roomNum == 8) {
			createRoom(&eight, 8);	
		}
		else if(roomNum == 9) {
			createRoom(&nine, 9);
		}
		else if(roomNum == 10) {
			createRoom(&ten, 10);
		}
	}

	//Create connections
	for (i = 0; i < 7; i++){
		if (roomArr[i] == 1) {
			//Create 3 connections for 1
			while(one.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];

				//Update connection for 1 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 1);
				}
				else if (r == 9) {
					updateConnection(&nine, 1);
				}
				else if (r == 10) {
					updateConnection(&ten, 1);
				}
			}
		}
		else if (roomArr[i] == 2) {
			//Create 3 connections for 2
			while(two.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];
				
				//Update connection for 2 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 2);
				}
				else if (r == 9) {
					updateConnection(&nine, 2);
				}
				else if (r == 10) {
					updateConnection(&ten, 2);
				}
			}
		}
		else if (roomArr[i] == 3) {
			//Create 3 connections for 3
			while(three.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];

				//Update connection for 3 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 3);
				}
				else if (r == 9) {
					updateConnection(&nine, 3);
				}
				else if (r == 10) {
					updateConnection(&ten, 3);
				}
			}
		}
		else if (roomArr[i] == 4) {
			//Create 3 connections for 4
			while(four.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];

				//Update connection for 4 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 4);
				}
				else if (r == 9) {
					updateConnection(&nine, 4);
				}
				else if (r == 10) {
					updateConnection(&ten, 4);
				}
			}
		}
		else if (roomArr[i] == 5) {
			//Create 3 connections for 5
				while(five.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];

				//Update connection for 5 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 5);
				}
				else if (r == 9) {
					updateConnection(&nine, 5);
				}
				else if (r == 10) {
					updateConnection(&ten, 5);
				}
			}
		}
		else if (roomArr[i] == 6) {
			//Create 3 connections for 6
			while(six.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;
				int r = roomArr[rnd];	

				//Update connection for 6 and random room
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
				else if (r == 8) {
					updateConnection(&eight, 6);
				}
				else if (r == 9) {
					updateConnection(&nine, 6);
				}
				else if (r == 10) {
					updateConnection(&ten, 6);
				}
			}
		}
		else if (roomArr[i] == 7) {
			//Create 3 connections for 1
			while(seven.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;
				int r = roomArr[rnd];	

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
				else if (r == 8) {
					updateConnection(&eight, 7);
				}
				else if (r == 9) {
					updateConnection(&nine, 7);
				}
				else if (r == 10) {
					updateConnection(&ten, 7);
				}
			}
		}
		else if (roomArr[i] == 8) {
			//Create 3 connections for 8
			while(eight.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;	
				int r = roomArr[rnd];

				//Update connection for 5 and random room
				updateConnection(&eight, r);
		
				if (r == 2) {
					updateConnection(&two, 8);
				}
				else if (r == 3) {
					updateConnection(&three, 8);
				}
				else if (r == 4) {
					updateConnection(&four, 8);
				}
				else if (r == 5) {
					updateConnection(&five, 8);
				}
				else if (r == 6) {
					updateConnection(&six, 8);
				}
				else if (r == 7) {
					updateConnection(&seven, 8);
				}
				else if (r == 1) {
					updateConnection(&one, 8);
				}
				else if (r == 9) {
					updateConnection(&nine, 8);
				}
				else if (r == 10) {
					updateConnection(&ten, 8);
				}
			}
		}
		else if (roomArr[i] == 9) {
			//Create 3 connections for 9
			while(nine.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;
				int r = roomArr[rnd];	

				//Update connection for 9 and random room
				updateConnection(&nine, r);

				if (r == 2) {
					updateConnection(&two, 9);
				}
				else if (r == 3) {
					updateConnection(&three, 9);
				}
				else if (r == 4) {
					updateConnection(&four, 9);
				}
				else if (r == 5) {
					updateConnection(&five, 9);
				}
				else if (r == 6) {
					updateConnection(&six, 9);
				}
				else if (r == 7) {
					updateConnection(&seven, 9);
				}
				else if (r == 8) {
					updateConnection(&eight, 9);
				}
				else if (r == 1) {
					updateConnection(&one, 9);
				}
				else if (r == 10) {
					updateConnection(&ten, 9);
				}
			}
		}
		else if (roomArr[i] == 10) {
			//Create 10 connections for 1
			while(ten.numConnections < 3) {
				//Generate random room
				int rnd = rand() % 7;
				int r = roomArr[rnd];	

				//Update connection for A and random room
				updateConnection(&ten, r);

				if (r == 2) {
					updateConnection(&two, 10);
				}
				else if (r == 3) {
					updateConnection(&three, 10);
				}
				else if (r == 4) {
					updateConnection(&four, 10);
				}
				else if (r == 5) {
					updateConnection(&five, 10);
				}
				else if (r == 6) {
					updateConnection(&six, 10);
				}
				else if (r == 7) {
					updateConnection(&seven, 10);
				}
				else if (r == 8) {
					updateConnection(&eight, 10);
				}
				else if (r == 9) {
					updateConnection(&nine, 10);
				}
				else if (r == 1) {
					updateConnection(&one, 10);
				}
			}
		}
	}

	char file[23];

	//Create and write to room files
	int k;
	for (k = 0; k < 7; k++) {
		i = roomArr[k];

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
		else if (i == 8) {
			numCon = eight.numConnections;
			con = eight.connections;
		}
		else if (i == 9) {
			numCon = nine.numConnections;
			con = nine.connections;
		}
		else if (i == 10) {
			numCon = ten.numConnections;
			con = ten.connections;
		}

		//Write name to file
		fprintf(afile, "ROOM NAME: %d\n", i);
		//Write connections to files
		int j;
		for (j = 0; j < numCon; j++) {
			fprintf(afile, "CONNECTION %d: %d\n", j+1, con[j]);
		}

		close(afile);
	}     
}
