#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "constants.h"
#include "structs.h"
#include "views.h"

extern void runGame();
gameContext * initGameContext();
horsesArr * initHorses();
void clearScreen();
int getRandomHorseSpeed();
void freeGameMemory(gameContext * game, horsesArr * horses);

void runGame() {

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
