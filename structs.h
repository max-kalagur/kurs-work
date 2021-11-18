#ifndef STRUCTS_LOADED

#include "constants.h"

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

#define STRUCTS_LOADED 1

#endif 