#ifndef UTILS_H
#define UTILS_H

#include "level.h"
#include "position.h"
#include "player.h"
#include "enemy.h"

void pathFind(Position *start, Position *end);
void addPositionYX(int **frontier, int frontierCount, int y, int x);
int addNeighbours(int **frontier, int frontierCount, int ***cameFrom, int y, int x);
int checkPos(int y, int x);

//Screen functions
void screenSetUp();
void printStats(Level *level);
void printInventory(Player *player);

//Combat functions
void combat(Player *player, Enemy *enemy, int order);

#endif