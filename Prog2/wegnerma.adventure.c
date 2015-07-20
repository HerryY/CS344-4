#include<stdio.h>

int main(){
	//Create directory variable <username>.rooms.<pid>
	char *user = "wegnerma.rooms.";

	int pid  = getpid();

	char directory[30];

	snprintf(directory, sizeof directory, "%s%d", user, pid);

	//Create directory
	mkdir(directory, 0777);

	//Create rooms
	
	
	//exit(0);
}
