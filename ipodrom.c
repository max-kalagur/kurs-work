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
	int race_boost;
	int is_fallen;
} horsesArr[HORSES_AMOUNT];

typedef struct {
	int isRaceNow;
	int userScore;
   int firstHorseNumber;
   int firstHorseDistanceRaced;
   int raceTime;
   int usersHorseNumber;
   int fallenHorses;
} gameContext;

gameContext * initGameContext();
horsesArr * initHorses();
void clearScreen();
int getRandomHorseSpeed();
void viewPreRace(int userScore, horsesArr * horsesArr);
void viewRace(gameContext * game, horsesArr * horses);
void viewRaceAfter(gameContext * game, horsesArr * horses);
void viewRaceFallenHorses(gameContext * game, horsesArr * horses);
void freeGameMemory(gameContext * game, horsesArr * horses);
char * generatePassiveHorseSprite(int num, int winnerNum, horsesArr * horses);
char * generateActiveHorseSprite(int num, horsesArr * horses, char * horseLegsPosition, char * handsPosition);
void clearViewMemory(char * res, char ** horseSprites);

int main() {

   srand(time(NULL));

   clearScreen();

   gameContext * game = initGameContext();
   horsesArr * horses = initHorses();

   viewPreRace(game->userScore, horses);

   scanf("%d", &game->usersHorseNumber);
   
   while( game->usersHorseNumber ) {

      game->isRaceNow = 1;
      
      do {
   
         float momentTime = 1;
         sleep(momentTime);
         game->raceTime = game->raceTime + momentTime;
         game->fallenHorses = 0; 

         for(int i=0; i < HORSES_AMOUNT; i++) {

            if( !horses[i]->is_fallen ) {
               horses[i]->speed = getRandomHorseSpeed();
               horses[i]->distance_raced = horses[i]->distance_raced + ( horses[i]->speed * momentTime );
            }
            else {
               game->fallenHorses++;
            }
            if(game->firstHorseDistanceRaced < horses[i]->distance_raced) {
               game->firstHorseNumber = i+1;
               game->firstHorseDistanceRaced = horses[i]->distance_raced;
            }
         }

         clearScreen();

         if( game->fallenHorses == HORSES_AMOUNT ) {
            break;
         }
         viewRace(game, horses);

      } while(game->firstHorseDistanceRaced < DISTANCE);

      if( game->fallenHorses == HORSES_AMOUNT ) {
         viewRaceFallenHorses(game, horses);
      }
      else {
         game->isRaceNow = 0;
         if(game->firstHorseNumber == game->usersHorseNumber) {
            game->userScore = game->userScore + 50;
         }
         else {
            game->userScore = game->userScore - 50;
         }

         clearScreen();
         viewRaceAfter(game, horses);
      }

      scanf("%d", &game->usersHorseNumber);

      if( game->usersHorseNumber == 0 ) {
         freeGameMemory(game, horses);
         break;
      }

      game->firstHorseNumber = 0;
      game->firstHorseDistanceRaced = 0;
      game->raceTime = 0;
      for(int i=0; i < HORSES_AMOUNT; i++) {
         horses[i]->speed = 0;
         horses[i]->distance_raced = 0;
         horses[i]->is_fallen = 0;
         horses[i]->race_boost = 0;
      }
   }

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
int getRandomHorseSpeed(){
   return ( HORSE_SPEED_MIN + rand() / (RAND_MAX / (HORSE_SPEED_MAX - HORSE_SPEED_MIN + 1) + 1) ) * 1000 / 3600;
}

int isRandomHorseFell( int num ){
   int r = rand() % 25;
   return num == r;
}

void clearViewMemory(char * res, char ** horseSprites) {

   free(res);
   for(register int i=0; i < HORSES_AMOUNT; i++) {
      free(horseSprites[i]);
      horseSprites[i] = NULL;
   }
   free(horseSprites);
   res = NULL;
   horseSprites = NULL;
}

char * generatePassiveHorseSprite(int num, int winnerNum, horsesArr * horses) {

   char * res     = malloc(sizeof(char) * 1000);
   char * tmplt   = malloc(sizeof(char) * 1000);
   char * win     = malloc(sizeof(char) * 13);

   if( horses[num]->is_fallen ) {
      tmplt = 
         "%d             \n"
         "   ___/\\  o     \n"
         " /(_|_/   |\\      \n"
         "   ||||   /\\    \n"
      ;

      sprintf(res, tmplt, num+1);
   }
   else {
      win[0] = '\0';
      if( winnerNum != 0 && winnerNum == num+1 ) {
         win = "<<<ПЕРЕМОЖЕЦЬ!!!";
      }

      tmplt = 
         "%d    o             \n"
         "   _/_/\\          \n"
         " /(_|_/      %s     \n"
         "   ||||            \n"
      ;

      sprintf(res, tmplt, num+1, win);
   }

   return res;
}

char * generateActiveHorseSprite(int num, horsesArr * horses, char * horseLegsPosition, char * handsPosition) {

   char * res     = malloc(sizeof(char) * 1500);
   char * tmplt   = malloc(sizeof(char) * 1500);
   char * boost   = malloc(sizeof(char) * 200);

   if( horses[num]->is_fallen ) {

      int boostI = horses[num]->race_boost;

      for(register int i=0; i < boostI; i++) {
         boost[i] = ' ';
      }
      boost[boostI] = '\0';

      tmplt = 
         "%s%d   >>> ВЕРШНИК УПАВ <<< \n"
         "%s   __ /\\      \n"
         "%s/(_/_/  %s   \n"
         "%s /||\\  _\\|    \n"
      ;
      
      sprintf(res, tmplt, boost, num+1, boost, boost, handsPosition, boost);
   }
   else {

      float boostF = (float)horses[num]->distance_raced / (float)DISTANCE * 72;
      int boostI = (int)boostF;
      horses[num]->race_boost = boostI;

      for(register int i=0; i < boostI; i++) {
         boost[i] = ' ';
      }
      boost[boostI] = '\0';

      tmplt = 
         "%s%d    o             \n"
         "%s   _/_/\\          \n"
         "%s~~(_|_/    швид.: %d м/с \n"
         "%s   %s    дист.: %d м     \n"
      ;
      
      sprintf(res, tmplt, boost, num+1, boost, boost, horses[num]->speed, boost, horseLegsPosition, horses[num]->distance_raced);

      horses[num]->is_fallen = isRandomHorseFell( num );
   }

   free(boost);

   return res;
}

void viewPreRace(int userScore, horsesArr * horsesArr) {

   char * res     = malloc(sizeof(char) * 4000);
   char * tmplt   = malloc(sizeof(char) * 1000);
   char ** horseSprites = malloc(sizeof(char) * 2000);

   for(register int i=0; i < HORSES_AMOUNT; i++) {
      horseSprites[i] = malloc(sizeof(char) * 500);
      horseSprites[i] = generatePassiveHorseSprite(i, 0, horsesArr);
   }

   tmplt = "\n"
      "Ваш Рахунок: %d\n"
      "\n"
      "\n"
      "\n"
      "\n"
      "                                       Будь ласка оберіть # коня (чи 0 для виходу)\n"
      "\n"
      "\n"
      "   СТАРТ|~\n"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "\n";

   sprintf(res, tmplt, userScore, horseSprites[0], horseSprites[1], horseSprites[2], horseSprites[3]);

   printf("%s\n", res);

   clearViewMemory(res, horseSprites);
}

void viewRace(gameContext * game, horsesArr * horses) {

   char * res                 = malloc(sizeof(char) * 6000);
   char * tmplt               = malloc(sizeof(char) * 4000);
   char ** horseSprites       = malloc(sizeof(char) * 5000);
   char * horseLegsPosition   = malloc(sizeof(char) * 7);
   char * handsPosition       = malloc(sizeof(char) * 7);

   if( game->raceTime % 2 == 1 ) {
      horseLegsPosition = "//\\\\";
   }
   else {
      horseLegsPosition =  "\\// ";
   }

   if( game->raceTime % 2 == 1 ) {
      handsPosition = "\\o/";
   }
   else {
      handsPosition =  "_o_ ";
   }

   for(register int i=0; i < HORSES_AMOUNT; i++) {
      horseSprites[i] = malloc(sizeof(char) * 1250);
      horseSprites[i] = generateActiveHorseSprite(i, horses, horseLegsPosition, handsPosition);
   }

   tmplt = "\n"
      "Ваш Рахунок: %d\n"
      "Ваш Кінь #: %d\n"
      "Дистанція: %d m\n"
      "Час Гонки: %d sec\n"
      "\n"
      "                                       Гонка почалась!\n"
      "                                       Лідирує Кінь #%d\n"
      "\n"
      "\n"
      "-------------------------------------------------------------------------------|--------------------\n"
      "%s"
      "-------------------------------------------------------------------------------|--------------------\n"
      "%s"
      "-------------------------------------------------------------------------------|--------------------\n"
      "%s"
      "-------------------------------------------------------------------------------|--------------------\n"
      "%s"
      "-------------------------------------------------------------------------------|--------------------\n"
      "\n";

   sprintf(res, tmplt, game->userScore, game->usersHorseNumber, DISTANCE, game->raceTime, game->firstHorseNumber,
      horseSprites[0],
      horseSprites[1],
      horseSprites[2],
      horseSprites[3]);

   printf("%s\n", res);

   clearViewMemory(res, horseSprites);
}

void viewRaceAfter(gameContext * game, horsesArr * horses) {

   char * res     = malloc(sizeof(char) * 4000);
   char * tmplt   = malloc(sizeof(char) * 3000);
   char * userScoreChange = malloc(sizeof(char) * 3);
   char ** horseSprites = malloc(sizeof(char) * 3000);

   for(register int i=0; i < HORSES_AMOUNT; i++) {
      horseSprites[i] = malloc(sizeof(char) * 500);
      horseSprites[i] = generatePassiveHorseSprite(i, game->firstHorseNumber, horses);
   }

   if( game->firstHorseNumber == game->usersHorseNumber ) {
      userScoreChange = "+50";
   }
   else {
	   userScoreChange =  "-50";
   }

   tmplt = "\n"
      "Ваш Рахунок: %d(%s)\n"
      "Ваш Кінь #: %d\n"
      "Час Гонки: %d sec\n"
      "\n"
      "                                       Гонка Закінчилась!\n"
      "                                         Кінь #%d Переміг\n"
      "                        Будь ласка оберіть # коня щоб розпочати гонку (чи 0 для виходу)\n"
      "\n"
      " |~ ФІНІШ \n"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "\n";

   sprintf(res, tmplt, game->userScore, userScoreChange, game->usersHorseNumber, game->raceTime, game->firstHorseNumber,
      horseSprites[0],
      horseSprites[1],
      horseSprites[2],
      horseSprites[3]);

   printf("%s\n", res);

   clearViewMemory(res, horseSprites);
}

void viewRaceFallenHorses(gameContext * game, horsesArr * horses) {

   char * res     = malloc(sizeof(char) * 2000);
   char * tmplt   = malloc(sizeof(char) * 1000);
   char ** horseSprites = malloc(sizeof(char) * 3000);

   for(register int i=0; i < HORSES_AMOUNT; i++) {
      horseSprites[i] = malloc(sizeof(char) * 500);
      horseSprites[i] = generatePassiveHorseSprite(i, 0, horses);
   }

   tmplt = "\n"
      "Ваш Рахунок: %d\n"
      "Ваш Кінь #: %d\n"
      "Час Гонки: %d sec\n"
      "\n"
      "                                       Гонка Закінчилась!\n"
      "                                      Усі вершники упали :(\n"
      "                        Будь ласка оберіть # коня щоб розпочати гонку (чи 0 для виходу)\n"
      "\n"
      " |~ ФІНІШ \n"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "%s"
      "----------------------------------------------------------------------------------------------------\n"
      "\n";

   sprintf(res, tmplt, game->userScore, game->usersHorseNumber, game->raceTime,
      horseSprites[0],
      horseSprites[1],
      horseSprites[2],
      horseSprites[3]);

   printf("%s\n", res);

   clearViewMemory(res, horseSprites);
}