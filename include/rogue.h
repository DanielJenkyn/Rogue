//Include only once, to avoid duplicate function declarations
#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Level {
    int level;
    int noOfRooms;
    struct Room **rooms;
    int noOfEnemies;
    struct Enemy **enemies;
    char **tiles;
    struct Player *user;
}Level;

typedef struct Position {
    int x;
    int y;
}Position;

typedef struct Room {
    Position position;
    int height;
    int width;
    
    Position **doors;
    //Enemies ** enemies //Array of pointers to montsters
    //Item ** items //Array of pointers to items
}Room;

typedef struct Player {
    Position *position;
    int health;
    //Room *room;
}Player;

typedef struct Enemy {
    Position *position;

    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    
}Enemy;

//Main functions
int screenSetUp();
int randRange(int min, int max, int exclusive);

//Level functions
Level *createLevel(int level);
Room **roomSetUp();
char **saveLevelPositions();

//Player functions
Player *playerSetUp();
Position *handleInput(int input, Player *user);
int checkPosition(Position *newPosition, Player *user, char **level);
int playerMove(Position *newPosition, Player *user, char **level);

//Room functions
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
int createCorridor(Position *doorOne, Position *doorTwo);

//Enemy functions
int addEnemy(Level *level);
Enemy *selectEnemy(int level);
Enemy *createEnemy(char symbol, int health, int attack, int defence, int speed, int pathfinding);
int setStartPos(Enemy *enemy, Room *room);

#endif
