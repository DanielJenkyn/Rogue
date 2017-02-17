//Include only once, to avoid duplicate function declarations
#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/*******Struct defintions*******/
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
    
    struct Door **doors;
    int noOfDoors;
    //Enemies ** enemies //Array of pointers to montsters
    //Item ** items //Array of pointers to items
}Room;

typedef struct Door {
    Position position;
    int connected;
    
}Door;

typedef struct Player {
    Position *position;
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

/*******Global vars*******/
static const int MAX_HEIGHT = 25;
static const int MAX_WIDTH = 100;

//Main functions
int randRange(int min, int max);

//Screen functions
int screenSetUp();
int printStats(Level *level);

//Level functions
Level *createLevel(int level);
Room **roomSetUp();
void connectDoors(Level *level);
char **saveLevelPositions();

//Player functions
Player *playerSetUp();
int spawnPlayer(Room **rooms, Player *user);
Position *handleInput(int input, Player *user);
int checkPosition(Position *newPosition, Level *level);
int playerMove(Position *newPosition, Player *user, char **level);

//Room functions
Room *createRoom(int grid, int noOfDoors);
int drawRoom(Room *room);

//Enemy functions
int addEnemy(Level *level);
Enemy *selectEnemy(int level);
Enemy *createEnemy(char symbol, int health, int attack, int defence, int speed, int pathfinding);
int killEnemy(Enemy *enemy);
int setStartPos(Enemy *enemy, Room *room);
int moveEnemy(Level *level);
int pathfindingSeek(Position *start, Position *destination);
int pathfindingRandom(Position *position);
Enemy *getEnemyAt(Position *position, Enemy **enemies);

//Combat functions
int combat(Player *player, Enemy *enemy, int order);

#endif