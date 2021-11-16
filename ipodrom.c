#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define HORSE_SPEED_MAX 90
#define HORSE_SPEED_MIN 60
#define HORSES_AMOUNT 4
#define DISTANCE 1000

typedef struct {
	int speed;
	int distance_raced;
} horsesArr[HORSES_AMOUNT];

typedef struct {
	int isRaceNow;
	int userScore;
   int firstHorseNumber;
   int firstHorseDistanceRaced;
   int raceTime;
   int usersHorseNumber;
} gameContext;

gameContext * initGameContext();
horsesArr * initHorses();
void clearScreen();
int randomHorseSpeed();
void viewPreRace(int userScore);
void viewRace(gameContext * game, horsesArr * horses);
void viewRaceAfter(gameContext * game, horsesArr * horses);
void freeGameMemory(gameContext * game, horsesArr * horses);

int main() {

   srand(time(NULL));

   clearScreen();

   gameContext * game = initGameContext();
   horsesArr * horses = initHorses();

   viewPreRace(game->userScore);

   scanf("%d", &game->usersHorseNumber);
   
   while( game->usersHorseNumber ) {

      game->isRaceNow = 1;
      
      do {
   
         float momentTime = 1;
         sleep(momentTime);
         game->raceTime = game->raceTime + momentTime;

         for(int i=0; i < HORSES_AMOUNT; i++) {
            horses[i]->speed = randomHorseSpeed();
            horses[i]->distance_raced = horses[i]->distance_raced + ( horses[i]->speed * momentTime );
            if(game->firstHorseDistanceRaced < horses[i]->distance_raced) {
               game->firstHorseNumber = i+1;
               game->firstHorseDistanceRaced = horses[i]->distance_raced;
            }
         }

         clearScreen();
         viewRace(game, horses);

      } while(game->firstHorseDistanceRaced < DISTANCE);

      game->isRaceNow = 0;
      if(game->firstHorseNumber == game->usersHorseNumber) {
         game->userScore = game->userScore + 50;
      }
      else {
         game->userScore = game->userScore - 50;
      }

      clearScreen();
      viewRaceAfter(game, horses);

      scanf("%d", &game->usersHorseNumber);

      game->firstHorseDistanceRaced = 0;
      game->raceTime = 0;
      for(int i=0; i < HORSES_AMOUNT; i++) {
         horses[i]->speed = 0;
         horses[i]->distance_raced = 0;
      }
   }

   freeGameMemory(game, horses);

   return 0;
}

gameContext * initGameContext() {

   gameContext * game = malloc(sizeof(gameContext));

   return game;
}

horsesArr * initHorses() {

   horsesArr * horses = malloc(sizeof(horsesArr) * HORSES_AMOUNT);

   if( horses != NULL ) {
      for(register int i = 0; i < HORSES_AMOUNT; i++) {
         horses[i]->speed = 0;
         horses[i]->distance_raced = 0;
      }
   }
   
   return horses;
}

void freeGameMemory(gameContext * game, horsesArr * horses) {

   free(game);
   free(horses);
}

void clearScreen()
{
   system("clear");
}

/* in m/s */
int randomHorseSpeed(){
   return ( HORSE_SPEED_MIN + rand() / (RAND_MAX / (HORSE_SPEED_MAX - HORSE_SPEED_MIN + 1) + 1) ) * 1000 / 3600;
}

void viewPreRace(int userScore) {

   char * res     = malloc(sizeof(char) * 4000);
   char * tmplt   = malloc(sizeof(char) * 1000);

   tmplt = "\n"
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

   printf("%s\n", res);

   free(res);
   // free(tmplt);
}

void viewRace(gameContext * game, horsesArr * horses) {

   char * res     = malloc(sizeof(char) * 4000);
   char * tmplt   = malloc(sizeof(char) * 3000);
   
   char * horseLegsPosition = malloc(sizeof(char) * 7);

   if( game->raceTime % 2 == 1 ) {
      horseLegsPosition = "/\/\\\\";
   }
   else {
      horseLegsPosition =  "\\/\/ ";
   }

   tmplt = "\n"
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

   sprintf(res, tmplt, game->userScore, game->usersHorseNumber, game->raceTime, game->firstHorseNumber,
      horses[0]->speed, horseLegsPosition, horses[0]->distance_raced,
      horses[1]->speed, horseLegsPosition, horses[1]->distance_raced,
      horses[2]->speed, horseLegsPosition, horses[2]->distance_raced,
      horses[3]->speed, horseLegsPosition, horses[3]->distance_raced);

   printf("%s\n", res);

   free(res);
   // free(tmplt);
   // free(horseLegsPosition);
}

void viewRaceAfter(gameContext * game, horsesArr * horses) {

   char * res     = malloc(sizeof(char) * 4000);
   char * tmplt   = malloc(sizeof(char) * 3000);
   char * userScoreChange = malloc(sizeof(char) * 3);

   if( game->firstHorseNumber == game->usersHorseNumber ) {
      userScoreChange = "+50";
   }
   else {
	   userScoreChange =  "-50";
   }

   tmplt = "\n"
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

   sprintf(res, tmplt, game->userScore, userScoreChange, game->usersHorseNumber, game->raceTime, game->firstHorseNumber);

   printf("%s\n", res);

   free(res);
   // free(tmplt);
   // free(userScoreChange);
}