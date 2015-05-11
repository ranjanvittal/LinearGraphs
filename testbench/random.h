#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
	To memorise whether seeded or not
*/
static int seeded=0;

/*
	Initialise the seed
*/
void randomInitialisation();


/*
	Generate a random number
*/
int randomNumber(int r,int l);


/*
	Generate a random character
*/
char randomChar();


/*
	Assuming that sufficient amount of memory is avaiable
*/
char* randomString(char* s,int len);