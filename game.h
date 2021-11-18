#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "constants.h"
#include "structs.h"
#include "views.h"

void runGame();
gameContext * initGameContext();
horsesArr * initHorses();
void clearScreen();
int getRandomHorseSpeed();
void freeGameMemory(gameContext * game, horsesArr * horses);