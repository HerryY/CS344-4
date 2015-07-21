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
#include<string.h>

struct Room {
	int name;
	int connections[6];
	int numConnections;
	int type;
};

/**********************************************************
 * 			createRoom
 * 	Creates room - assigns name and initializes
 * 	# of connections to 0
 *********************************************************/
void createRoom (struct Room *s, int n) {
	s->name = n;
	s->numConnections = 0;
	s->type = 0;
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
 * 			printRoom
 * 	Prints name and connectiosn of room
 *********************************************************/
void printRoom(struct Room * s) {
	printf("CURRENT LOCATION: %d\n", s->name);
	printf("POSSIBLE CONNECTIONS: ");
	int i;
	for (i = 0; i < s->numConnections; i++) {
		if (i != s->numConnections - 1) {
			printf("%d, ", s->connections[i]);
		}
		else {
			printf("%d.\n", s->connections[i]);
		}
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

	//Assign start and end room randomly
	int startRand = rand() % 7;
	int start = roomArr[startRand];

	int end;
	do {
		int endRand = rand() % 7;
		end = roomArr[endRand];
	} while (start == end);

	if (start == 1) one.type = 1; 
	else if (start == 2) two.type = 1;
	else if (start == 3) three.type = 1;
	else if (start == 4) four.type = 1;
	else if (start == 5) five.type = 1;
	else if (start == 6) six.type = 1;
	else if (start == 7) seven.type = 1;
	else if (start == 8) eight.type = 1;
	else if (start == 9) nine.type = 1;
	else if (start == 10) ten.type = 1;
	
	if (end == 1) one.type = 2; 
	else if (end == 2) two.type = 2;
	else if (end == 3) three.type = 2;
	else if (end == 4) four.type = 2;
	else if (end == 5) five.type = 2;
	else if (end == 6) six.type = 2;
	else if (end == 7) seven.type = 2;
	else if (end == 8) eight.type = 2;
	else if (end == 9) nine.type = 2;
	else if (end == 10) ten.type = 2;

	char file[23];

	//Create files  and write to room files
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
		int type;
		if (i == 1) {
			numCon = one.numConnections;
			con = one.connections;
			type = one.type;
		}
		else if (i == 2) {
			numCon = two.numConnections;
			con = two.connections;
			type = two.type;
		}
		else if (i == 3) {
			numCon = three.numConnections;
			con = three.connections;
			type = three.type;
		}
		else if (i == 4) {
			numCon = four.numConnections;
			con = four.connections;
			type = four.type;
		}
		else if (i == 5) {
			numCon = five.numConnections;
			con = five.connections;
			type = five.type;
		}
		else if (i == 6) {
			numCon = six.numConnections;
			con = six.connections;
			type = six.type;
		}
		else if (i == 7) {
			numCon = seven.numConnections;
			con = seven.connections;
			type = seven.type;
		}		
		else if (i == 8) {
			numCon = eight.numConnections;
			con = eight.connections;
			type = eight.type;
		}
		else if (i == 9) {
			numCon = nine.numConnections;
			con = nine.connections;
			type = nine.type;
		}
		else if (i == 10) {
			numCon = ten.numConnections;
			con = ten.connections;
			type = ten.type;
		}

		//Write name to file
		fprintf(afile, "ROOM NAME: %d\n", i);
		//Write connections to files
		int j;
		for (j = 0; j < numCon; j++) {
			fprintf(afile, "CONNECTION %d: %d\n", j+1, con[j]);
		}

		//Write room type to file
		if (type == 0) {
			fprintf(afile, "ROOM TYPE: MID_ROOM\n\n");
		}
		else if (type == 1) {
			fprintf(afile, "ROOM TYPE: START_ROOM\n\n");
		}
		else if (type == 2) {
			fprintf(afile, "ROOM TYPE: END_ROOM\n\n");
		}

		fclose(afile);
	}    
	
	struct Room begin;
	struct Room finish;
	struct Room  rn;

	//read in room info from files
	for (k = 0; k < 7; k++) {
		i = roomArr[k];

		//File pathway
		snprintf(file, sizeof file, "%s/%d", directory, i);

		//open file
		afile = fopen(file, "r");
		
		char * line;
		size_t len = 0; 

		//get lines of file
		while(!feof(afile)) {

			getline(&line, &len, afile);

			
			if (line[5] == 'N') {
				//Get the name of the file
				char num = line[11] - 48;

				if(num == 1) {
					if(line[12] == 48) {
						num = 10;		
					}
				}
				
				createRoom(&rn, num);
			}
			else if (line[0] == 'C') {
				//Get the connections for the file
				//Determine the room number
			 	char num = line[11] - 48;

				if(num == 1) {
					if(line[12] == 48) {
						num = 10;		
					}
				}

				//Update the room with the connection
				updateConnection(&rn, num);
			}
			else if (line[5] == 'T') {
				//Assign type to room
				char t = line[11];

				if (t == 'E') {
					rn.type = 2;
					finish = rn;
				}
				else if (t == 'S') {
					rn.type = 1;
					begin = rn;
				}
				else if (t == 'M') {
					rn.type = 0;
				}
			}	
		}

		if (k == 1) one = rn;
		else if (k == 2) two = rn;
		else if (k == 3) three = rn;
		else if (k == 4) four = rn;
		else if (k == 5) five = rn;
		else if (k == 6) six = rn;
		else if (k == 7) seven = rn;

		fclose(afile);
	}

	//Game
	//store # of steps
	int steps = 0;

	//store path
	int path[100];

	//set current location to start
	struct Room * cur = &begin;

	//print current room
	while(cur != &finish) {
		int valid;
		int rmNum;

		do {
		printRoom(cur);

		//Ask for input
		printf("WHERE TO?>");
		char number[3];
		fgets(number, 3, stdin); 
		rmNum = atoi(number);

		printf("\n");

		//Check that the user entered avalid room
		valid = 0;
		int j;
		for (j = 0; j < cur->numConnections; j++) {
			if (cur->connections[j] == rmNum) {
				valid = 1;
			}
		}

		if(valid == 0) {
			printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n"); 
		}
		} while (valid == 0);

		//Add number to path
		path[steps] = rmNum;
		 
		if(one.name == rmNum) cur = &one;	
		else if(two.name == rmNum) cur = &two;
		else if(three.name == rmNum) cur = &three;
		else if(four.name == rmNum) cur = &four;
		else if(five.name == rmNum) cur = &five;
		else if(six.name == rmNum) cur = &six;
		else if(seven.name == rmNum) cur = &seven;

		steps++;
	}

	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	for (i = 0; i < steps; i++) {
		printf("%d\n", path[i]);
	}
}
