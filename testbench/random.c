#include "random.h"

/*
	Initialise the seed
*/
void randomInitialisation(){


	if(seeded==0){
		srand(time(NULL));
		seeded=1;
	}

}

/*
	Generate a random number from l to r inclusive
*/
int randomNumber(int r,int l){

	randomInitialisation();

	return l+rand()%(r-l+1);

}

/*
	Generate a random character
*/
char randomChar(){

	return (char)randomNumber(122,97);

}

/*
	Assuming that sufficient amount of memory is avaiable
*/
char* randomString(char* s,int len){
	
	int i;
	for(i=0;i<len;i++)
		s[i]=randomChar();
	s[i]='\0';
	return s;

}

