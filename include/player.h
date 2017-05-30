#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"

typedef struct Player {
    Position *position;
    char string[2];
    char symbol;
    int health;
    int maxHealth;
    int attack;
    int gold;
    int exp;
    //Unused
    // int defence;
    // int speed;
    //Room *room;
}Player;

//Player functions
Player *playerSetUp();

Position *handleInput(int input, Player *user);
void playerMove(Position *newPosition, Player *user, char **level);
void drawPlayer(Player *player);

#endif