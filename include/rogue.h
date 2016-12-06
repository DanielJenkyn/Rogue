//Include only once, to avoid duplicate function declarations
#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Position {
    int x;
    int y;
}Position;

typedef struct Room {
    Position position;
    int height;
    int width;
    
    Position **doors;
    //Monster ** monsters //Array of pointers to montsters
    //Item ** items //Array of pointers to items
}Room;

typedef struct Player {
    Position position;
    int health;
    //Room *room;
}Player;

int screenSetUp();
Room **mapSetUp();
Player *playerSetUp();
int handleInput(int, Player *user);
int checkPosition(int, int, Player *user);
int playerMove(int, int, Player *user);

//Room functions
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
int connectDoors(Position *doorOne, Position *doorTwo);
int randRange(int min, int max, int exclusive);

#endif
