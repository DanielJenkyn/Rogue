#ifndef LEVEL_H
#define LEVEL_H

#include "position.h"
#include "enemy.h"
#include "player.h"
#include "room.h"

typedef struct Level {
    int level;
    int noOfRooms;
    struct Room **rooms;
    int noOfEnemies;
    struct Enemy **enemies;
    char **tiles;
    struct Player *user;
}Level;

//Level functions
Level *createLevel(int level);
void drawLevel(Level *level);
Room **roomSetUp();
void connectDoors(Level *level);
char **saveLevelPositions();

void addEnemy(Level *level);
void moveEnemy(Level *level);
void checkPosition(Position *newPosition, Level *level);

#endif