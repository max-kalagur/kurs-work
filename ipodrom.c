#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void clearScreen()
{
  system("clear");
}

/* in m/s */
int randomHorseSpeed(){
   int min = 60;
   int max = 90;
   return ( min + rand() / (RAND_MAX / (max - min + 1) + 1) ) * 1000 / 3600;
}

void termPreRace() {

   char output[1000] = "\n"
"Your Score: 0\n"
"\n"
"\n"
"\n"
"\n"
"                                       Please Choose The Hourse\n"
"\n"
"\n"
"   START|~\n"
"----------------------------------------------------------------------------------------------------\n"
"1    o             \n"
"   _/_/\\          \n"
"~~(_|_/            \n"
"   ||||            \n"
"----------------------------------------------------------------------------------------------------\n"
"2    o             \n"
"   _/_/\\          \n"
"~~(_|_/            \n"
"   ||||            \n"
"----------------------------------------------------------------------------------------------------\n"
"3    o             \n"
"   _/_/\\          \n"
"~~(_|_/            \n"
"   ||||            \n"
"----------------------------------------------------------------------------------------------------\n"
"4    o             \n"
"   _/_/\\          \n"
"~~(_|_/            \n"
"   ||||            \n"
"----------------------------------------------------------------------------------------------------\n"
"\n";


printf(output);


}

void termRace(int horsesSpeed[], int horsesRaced[], int userHorseNumber, int raceTime, int firstHorseNumber) {

   char res[4000];
   
   char *horseLegsPosition;

   if( raceTime % 2 == 1 ) {
        horseLegsPosition = "/\/\\\\";
   }
   else {
	horseLegsPosition =  "\\/\/ ";
   }

   char tmplt[3000] = "\n"
"Your Score: 0\n"
"Your Hourse #: %d\n"
"Race Time: %d sec\n"
"\n"
"\n"
"                                       Race is running!\n"
"                                      First Hourse is #%d\n"
"\n"
"\n"
"----------------------------------------------------------------------------------------------------\n"
"1    o             \n"
"   _/_/\\          \n"
"~~(_|_/       speed: %d m/s    \n"
"   %s       distance: %d m     \n"
"----------------------------------------------------------------------------------------------------\n"
"2    o             \n"
"   _/_/\\          \n"
"~~(_|_/       speed: %d m/s     \n"
"   %s       distance: %d m     \n"
"----------------------------------------------------------------------------------------------------\n"
"3    o             \n"
"   _/_/\\          \n"
"~~(_|_/       speed: %d m/s     \n"
"   %s       distance: %d m     \n"
"----------------------------------------------------------------------------------------------------\n"
"4    o             \n"
"   _/_/\\          \n"
"~~(_|_/       speed: %d m/s     \n"
"   %s       distance: %d m     \n"
"----------------------------------------------------------------------------------------------------\n"
"\n";

sprintf(res, tmplt, userHorseNumber, raceTime, firstHorseNumber,
	horsesSpeed[0], horseLegsPosition, horsesRaced[0],
	horsesSpeed[1], horseLegsPosition, horsesRaced[1],
	horsesSpeed[2], horseLegsPosition, horsesRaced[2],
	horsesSpeed[3], horseLegsPosition, horsesRaced[3]);

printf(res);

}

int main() {

   srand(time(NULL));

   clearScreen();

   termPreRace();

   int isRaceNow = 0;
   int distance = 1000;
   int horsesSpeed[4] = {0,0,0,0};
   int horsesRaced[4] = {0,0,0,0};
   int firstHorseNumber;
   int firstHorseRaced;
   int raceTime = 0;
   int userHorseNumber;

   scanf("%d", &userHorseNumber);
   
   isRaceNow = 1;
   
   do {
 
	float momentTime = 1;
	sleep(momentTime);
	raceTime = raceTime + momentTime;

	for(int i=0; i < 4; i++) {
		horsesSpeed[i] = randomHorseSpeed();
		horsesRaced[i] = horsesRaced[i] + ( horsesSpeed[i] * momentTime );
		if(firstHorseRaced < horsesRaced[i]) {
			firstHorseNumber = i+1;
			firstHorseRaced = horsesRaced[i];
		}
	}

	clearScreen();
	termRace(horsesSpeed, horsesRaced, userHorseNumber, raceTime, firstHorseNumber);

   } while(firstHorseRaced < distance);

   isRaceNow = 0;
   termRaceAfter();


   return 0;
}
