#ifndef ROOM_H
#define ROOM_H

#include "enemy.h"
#include "player.h"
#include "position.h"
#include "door.h"

typedef struct Room {
    Position position;
    int height;
    int width;
    
    struct Door **doors;
    int noOfDoors;
    //Enemies ** enemies //Array of pointers to montsters
    //Item ** items //Array of pointers to items
}Room;

//Room functions
Room *createRoom(int grid, int noOfDoors);
int drawRoom(Room *room);

void spawnPlayer(Room **rooms, Player *user);
void setStartPos(Enemy *enemy, Room *room);

#endif
