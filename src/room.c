#include "rogue.h"
#include "room.h"

Room *createRoom(int grid, int noOfDoors) {
    
    Room *newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->noOfDoors = noOfDoors;
    
    switch(grid) {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = 33;
            newRoom->position.y = 0;
            break;
        case 2:
            newRoom->position.x = 66;
            newRoom->position.y = 0;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 14;
            break;
        case 4:
            newRoom->position.x = 33;
            newRoom->position.y = 14;
            break;
        case 5:
            newRoom->position.x = 66;
            newRoom->position.y = 14;
            break;
    }

    newRoom->height = randRange(4,9);
    newRoom->width = randRange(4,17);
    
    //room x,y offset
    newRoom->position.x += randRange(1,(30 - newRoom->width));
    newRoom->position.y += randRange(1,(10 - newRoom->height));

    newRoom->doors = malloc(sizeof(Door *) * noOfDoors);

    for(int i = 0; i < noOfDoors; i++) {
        newRoom->doors[i] = malloc(sizeof(Door));
        newRoom->doors[i]->connected = 0;
    }
    
    //Top doors
    newRoom->doors[0]->position.x = randRange(newRoom->position.x+1, newRoom->position.x + newRoom->width-2);
    newRoom->doors[0]->position.y = newRoom->position.y;
    //Left sideposition.
    newRoom->doors[1]->position.x = newRoom->position.x;
    newRoom->doors[1]->position.y = randRange(newRoom->position.y+1, newRoom->position.y + newRoom->height-2);
    //Bottom doorsposition.
    newRoom->doors[2]->position.x = randRange(newRoom->position.x+1, newRoom->position.x + newRoom->width-2);
    newRoom->doors[2]->position.y = newRoom->position.y + newRoom->height-1;
    //Right sideposition.
    newRoom->doors[3]->position.x = newRoom->position.x + newRoom->width-1;
    newRoom->doors[3]->position.y = randRange(newRoom->position.y+1, newRoom->position.y + newRoom->height-2);
    
    return newRoom;
}

int drawRoom(Room *room) {
    int x;
    int y;
    
    //Draw top and bottom
    for(x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); //Top
        mvprintw(room->position.y + room->height - 1, x, "-"); //Bottom
    }
    
    //Draw floor and walls(side)
    for(y = room->position.y + 1; y < room->position.y + room->height -1;y++) {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        //Draw floor
        for(x = room->position.x + 1; x<room->position.x + room->width - 1; x++) {
            mvprintw(y,x,".");
        }
    }
    
    //Draw doors
    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");
    mvprintw(room->doors[2]->position.y, room->doors[2]->position.x, "+");
    mvprintw(room->doors[3]->position.y, room->doors[3]->position.x, "+");
    return 0;
}

void spawnPlayer(Room **rooms, Player *user) {
    user->position->x = rooms[3]->position.x+1;
    user->position->y = rooms[3]->position.y+1;
    move(user->position->y, user->position->x);
}

void setStartPos(Enemy *enemy, Room *room) {
    enemy->position->y = randRange(room->position.y + 1, room->position.y + room->height - 2);
    enemy->position->x = randRange(room->position.x + 1, room->position.x + room->width - 2);
}