/**********************************************************
 * Name: Marta Ochoa
 * Assignment #2
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

//struct contains room info
struct Room {
   int name;
   int connections[6];
   int numConnections;
   int type;
};

/**********************************************************
 * 			createRoom
 * 	Creates room - assigns name and initializes # 
 * 	of connections to 0
 * 	Param: pointer to Room struct and integer name 
 *********************************************************/
void createRoom (struct Room *s, int n){
   s->name = n;
   s->numConnections = 0;
   s->type = 0;
}

/**********************************************************
 * 		    updateConnection
 *	Updates connections for room when they are 
 *	being loaded in from file. Takes pointer to 
 *	the room and an int of name of room to 
 *	connect to. If max num of connections for a 
 *	room has been reached returns.If a connection 
 *	to that room is already made returns. Else 
 *	the connection is mase and # of connections 
 *	is incremented and the function returns.
 *********************************************************/
void updateConnection (struct Room *s, int connection) {
   if (s->numConnections >= 6) {
	//Return - max # of connections reached
	return;
   }
   else if(s->name == connection) {
	//Return is trying to make a connection to 
	//the same room
	return;
   }
   else {
	//If connection to that room is already
	//made return
	int i;
	for (i = 0; i < s->numConnections; i++) {
	   if (s->connections[i] == connection) {
		return;
	   }
	}

	//Else update connections
	s->connections[s->numConnections] = connection;

	//Update # of connections
	s->numConnections++;
   }
}

/**********************************************************
 * 			printRoom
 * 	Takes a pointer to a room. Prints the 
 * 	name and connections of that room
 *********************************************************/
void printRoom(struct Room * s) { 
   //Print the name of the room
   printf("CURRENT LOCATION: %d\n", s->name);
   printf("POSSIBLE CONNECTIONS: ");
   
   int i;
   //Print the connections
   for (i = 0; i < s->numConnections; i++){
	if (i != s->numConnections - 1) {
	   //If not the end of list print with comma
	   printf("%d, ", s->connections[i]);
	}
	else {
	   //If end of list print with period
	   printf("%d.\n", s->connections[i]);
	}
   }
}

int main(){
   int i;
   FILE * afile;

   //Seed rand
   srand(time(NULL));

   //Create directory variable <username>.rooms.<pid>
   //Directory used to store room files
   char *user = "wegnerma.rooms.";//<username>.rooms.

   int pid = getpid();//Get pid for var

   //String to store directory name
   char directory[20];

   //Combine user with pid for directory name
   snprintf(directory, sizeof directory, "%s%d", user, pid);

   //Create directory
   mkdir(directory, 0755);

   //Array of room names
   int roomArr[7];

   //Array of Room structs
   struct Room rooms[7];

   //Room variable - to use to create room
   struct Room room;

   //Select name and create rooms
   //Names are random 7 numbers between 1 and 10
   for (i = 0; i < 7; i++) {
	int unique = 0;
	int roomNum;

	//Geneate random room number 
	//If room number is already taken
	//regenerate rand number until a unique
	//number is found
	while (!unique) {
	   //Generate room number
	   roomNum = (rand() % 10) + 1;
	   
	   unique = 1;
	   int u;
	   //Check that room number is not already used
  	   for (u = 0; u < i; u++) {
		if (roomArr[u] == roomNum) {
		   unique = 0;
		}
	   }
	}

	//Add room # to array
	roomArr[i] = roomNum;
	
  	//Create room and initialize
  	createRoom(&room, roomNum);
	
	//Store room in rooms array
	rooms[i] = room;
   }    

   //Second room variable - used to create
   //connections between two rooms
   struct Room room2;

   //Create connections
   int j;
   for (i = 0; i < 7; i++) {
	room = rooms[i]; //current room
	int roomNum = roomArr[i]; //current room name

	//Create at least 3 connections for each room
	while (room.numConnections < 3) {
	   int rnd = i;//rnd set to current room
	   int r;

	   while (rnd == i) {//While rnd is equal to the 
			     //room that is making the connection

		rnd = rand() % 7;//Generate random num 
				 //for connection

	   	r = roomArr[rnd];//Find room name in array
				     //of names

		//Search for previous connection
		for(j = 0; j < room.numConnections; j++) {
		   if (room.connections[j] == r) { //If the rooms 
						   //are already 
						   //connected no 
						   //conection made
						   //and a new rnd
						   //number is 
						   //generated
			rnd = i;//rnd = i to repeat while loop
		   }
		}
	   }
	
	   //If the room is not already connected
	   //the connection are made
	   room.connections[room.numConnections] = r;

	   //Increase number of connections for room
	   room.numConnections++;

	   //Store room back in arr
	   rooms[i] = room;

	   //Add connection in reverse
	   room2 = rooms[rnd];
	   room2.connections[room2.numConnections] = roomNum;

	   //Increase number of connections for room 2
	   room2.numConnections++;

	   //Store room2 back in arr
	   rooms[rnd] = room2;
	}
   }

   //Assign start and end room randomly
   int startRand = rand() % 7; //Random num for start
   int start = roomArr[startRand]; //Find name in array
   room = rooms[startRand]; //Find room in rooms array

   //Set room to start room
   room.type = 1; //type 2 == start

   //store start room back in array
   rooms[startRand] = room;

   int end; 
   int endRand;

   do {
	endRand = rand() % 7; //Random number for end
	end = roomArr[endRand]; //Find name in array
   } while (start == end); //Check that start and end
			   //rooms are not the same

   //If start and end are not same set room to end room
   room = rooms[endRand];
   room.type = 2; //type 2 == end

   //store end room back in array
   rooms[endRand] = room;

   //Create files and write to room files
   char file[23];

   int k;
   for (k = 0; k < 7; k++) {
	room = rooms[k]; //Get room
	int roomName = roomArr[k]; //Get room name

	//File pathway: directory/roomName
	snprintf(file, sizeof file, "%s/%d", directory, roomName);

	//open file with write permission
	afile = fopen(file, "w");

	//Info for file
	int numCon;
	int * con;
	int type;
	
	//Number of connections
	numCon = room.numConnections;

	//Room connections
	con = room.connections;

	//Room type
	type = room.type;

	//Write name to file
	fprintf(afile, "ROOM NAME: %d\n", roomName);

	//Write connections to file
	int j;
	for (j = 0; j < numCon; j++) {
	   fprintf(afile, "CONNECTION %d: %d\n", j+1, con[j]);
	}

	//Write room type to file
	if (type == 0) { //Middle room
	   fprintf(afile, "ROOM TYPE: MID_ROOM\n\n");
	}
	else if (type == 1) {//Start room
	   fprintf(afile, "ROOM TYPE: START_ROOM\n\n");
	}
	else if (type == 2) { //end room
	   fprintf(afile, "ROOM TYPE: END_ROOM\n\n");
	}

	//close file
	fclose(afile);
   }

   //Rooms for game
   struct Room begin;
   struct Room finish;
   struct Room rn;

   //Store all rooms
   struct Room gameRooms[7];

   //read room info from files
   for (k = 0; k < 7; k++) {
	int roomName = roomArr[k];

	//File pathway: directory/roomName
	snprintf(file, sizeof file, "%s/%d", directory, roomName);

	//open file with read permission
	afile = fopen(file, "r");

	char * line;
	size_t len = 0;

	//get line of file
	while(!feof(afile)) {
	   getline(&line, &len, afile);

	   //If the line is name
	   if(line[5] == 'N') {
		//Get the name of the file
		char num = line[11] - 48;

		if (num == 1) {//Determine if num is 1 or 10
		   if (line[12] == 48) {
			num = 10;
		   }
		}

	        //Create room from file
	        createRoom(&rn, num);
	   }
	   else if (line[0] == 'C') {//Else if line is 
				     //a connection
		//Get the connections for the file
		//Determine the room number
		char num = line[14] - 48;

		if (num == 1) {//Check if num is 1 or 10
		   if(line[15] == 48) {
			num = 10;
		   }
		}

		//Update room with connection
		updateConnection(&rn, num);
	   }
	   else if (line[5] == 'T') {
		//Assign type to room
		char t = line[11];

		if (t == 'E') {//If end room
		   rn.type = 2;//set type to end
		   finish = rn;//set finish room
		}
		else if (t == 'S') {//If start room
		   rn.type = 1;//set type to start
		   begin = rn; //set begin room
		}	   
	   }
	}

	//Store room in game room array
	gameRooms[k] = rn;

	//Close file
	fclose(afile);	
   }

   //Game
   //Store # of steps
   int steps = 0;

   //Store path
   int path[100];

   //Set current location to start
   struct Room * cur = &begin;

   //Play
   while(cur->type != 2) {//while the room
			  //is not the end room
	int valid;
	int rmNum;

	do {
	   //Print current room
	   printRoom(cur);

	   //Ask user for input
	   printf("WHERE TO?>");
	   char number[3];
	   fgets(number, 3, stdin);//Get input as string
	   rmNum = atoi(number);//Change input to int

	   printf("\n");

	   //Check that user entered a valid room
	   valid = 0;
	   int j;

	   for(j = 0; j < cur->numConnections; j++) {
		//Search through connections
		//for valid input
		if (cur->connections[j] == rmNum) {
		   valid = 1;//If in connections, is valid
		}
	   }

	   //If input is not a valid number
	   //print error message
	   if(valid == 0) {
		printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
	   } 
	} while (valid == 0);//Repeat until valid input

	//Add chosen room to path
	path[steps] = rmNum;

	//Find chosen room in array
	int m;
	for (m = 0; m < 7; m++){
	   if(gameRooms[m].name == rmNum) {//Search through array for
					   //room with name

		cur = &gameRooms[m];//set cur room to new room
	   }
	}

	//Increase number of steps
	steps++;
   }

   //End of game
   //When end is reached print message
   printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
   //Print steps
   printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
   //print path
   for (i = 0; i < steps; i++) {
	printf("%d\n", path[i]);
   }
   
   return 0;
}
