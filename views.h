#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structs.h"

int isRandomHorseFell( int num );
void viewPreRace(int userScore, horsesArr * horsesArr);
void viewRace(gameContext * game, horsesArr * horses);
void viewRaceAfter(gameContext * game, horsesArr * horses);
void viewRaceFallenHorses(gameContext * game, horsesArr * horses);
char * generatePassiveHorseSprite(int num, int winnerNum, horsesArr * horses);
char * generateActiveHorseSprite(int num, horsesArr * horses, char * horseLegsPosition, char * handsPosition);
void clearViewMemory(char * res, char ** horseSprites);