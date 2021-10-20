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

void termPreRace(int userScore) {

   char res[4000];

   char tmplt[1000] = "\n"
      "Your Score: %d\n"
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
      " /(_|_/            \n"
      "   ||||            \n"
      "----------------------------------------------------------------------------------------------------\n"
      "2    o             \n"
      "   _/_/\\          \n"
      " /(_|_/            \n"
      "   ||||            \n"
      "----------------------------------------------------------------------------------------------------\n"
      "3    o             \n"
      "   _/_/\\          \n"
      " /(_|_/            \n"
      "   ||||            \n"
      "----------------------------------------------------------------------------------------------------\n"
      "4    o             \n"
      "   _/_/\\          \n"
      " /(_|_/            \n"
      "   ||||            \n"
      "----------------------------------------------------------------------------------------------------\n"
      "\n";

   sprintf(res, tmplt, userScore);

   printf(res);
}

void termRace(int horsesSpeed[], int horsesRaced[], int userHorseNumber, int raceTime, int firstHorseNumber, int userScore) {

   char res[4000];
   
   char *horseLegsPosition;

   if( raceTime % 2 == 1 ) {
      horseLegsPosition = "/\/\\\\";
   }
   else {
	   horseLegsPosition =  "\\/\/ ";
   }

   char tmplt[3000] = "\n"
      "Your Score: %d\n"
      "Your Hourse #: %d\n"
      "Distance: 1000m\n"
      "Race Time: %d sec\n"
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

   sprintf(res, tmplt, userScore, userHorseNumber, raceTime, firstHorseNumber,
      horsesSpeed[0], horseLegsPosition, horsesRaced[0],
      horsesSpeed[1], horseLegsPosition, horsesRaced[1],
      horsesSpeed[2], horseLegsPosition, horsesRaced[2],
      horsesSpeed[3], horseLegsPosition, horsesRaced[3]);

   printf(res);
}

void termRaceAfter(int raceTime, int firstHorseNumber, int userHorseNumber, int userScore, int userWon) {

   char res[4000];

   char *userScoreChange;

   if( firstHorseNumber == userHorseNumber ) {
      userScoreChange = "+50";
   }
   else {
	   userScoreChange =  "-50";
   }

   char tmplt[3000] = "\n"
      "Your Score: %d(%s)\n"
      "Your Hourse #: %d\n"
      "Race Time: %d sec\n"
      "\n"
      "                                       Race is finished!\n"
      "                                         Horse #%d won\n"
      "                        Please choose the new horse to start the race again\n"
      "\n"
      " |~ FINISH \n"
      "----------------------------------------------------------------------------------------------------\n"
      "1    o             \n"
      "   _/_/\\          \n"
      " /(_|_/        \n"
      "   ||||        \n"
      "----------------------------------------------------------------------------------------------------\n"
      "2    o             \n"
      "   _/_/\\          \n"
      " /(_|_/        \n"
      "   ||||          \n"
      "----------------------------------------------------------------------------------------------------\n"
      "3    o             \n"
      "   _/_/\\          \n"
      " /(_|_/         \n"
      "   ||||        \n"
      "----------------------------------------------------------------------------------------------------\n"
      "4    o             \n"
      "   _/_/\\          \n"
      " /(_|_/       \n"
      "   ||||       \n"
      "----------------------------------------------------------------------------------------------------\n"
      "\n";

   sprintf(res, tmplt, userScore, userScoreChange, userHorseNumber, raceTime, firstHorseNumber);

   printf(res);
}

int main() {

   srand(time(NULL));

   clearScreen();

   int isRaceNow = 0;
   int userScore = 0;
   int userWon;
   int distance = 1000;
   int horsesSpeed[4] = {0,0,0,0};
   int horsesRaced[4] = {0,0,0,0};
   int firstHorseNumber;
   int firstHorseRaced;
   int raceTime = 0;
   int userHorseNumber;

   termPreRace(userScore);

   scanf("%d", &userHorseNumber);
   
   while( userHorseNumber ) {

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
         termRace(horsesSpeed, horsesRaced, userHorseNumber, raceTime, firstHorseNumber, userScore);

      } while(firstHorseRaced < distance);

      isRaceNow = 0;
      if(firstHorseNumber == userHorseNumber) {
         userScore = userScore + 50;
         userWon = 1;
      }
      else {
         userScore = userScore - 50;
         userWon = 0;
      }

      clearScreen();
      termRaceAfter(raceTime, firstHorseNumber, userHorseNumber, userScore, userWon);

      scanf("%d", &userHorseNumber);

      firstHorseRaced = 0;
      raceTime = 0;
      for(int i=0; i < 4; i++) {
         horsesSpeed[i] = 0;
         horsesRaced[i] = 0;
      }
   }

   return 0;
}
