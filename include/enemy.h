#ifndef ENEMY_H
#define ENEMY_H

#include "position.h"

typedef struct Enemy {
    Position *position;
    char string[2];
    char symbol;
    int health;
    int attack;
    int defence;
    int speed;
    int alive;
    int pathfinding;
}Enemy;

//Enemy functions
Enemy *selectEnemy(int level);
Enemy *createEnemy(char symbol, int health, int attack, int defence, int speed, int pathfinding);
void killEnemy(Enemy *enemy);
void drawEnemy(Enemy *enemy);
void pathfindingSeek(Position *start, Position *destination);
void pathfindingRandom(Position *position);
Enemy *getEnemyAt(Position *position, Enemy **enemies);

#endif