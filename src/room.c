#include "rogue.h"

Room *createRoom(int y, int x, int height, int width) {
    
    Room *newRoom;
    newRoom = malloc(sizeof(Room));
    
    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;
    
    newRoom->doors = malloc(sizeof(Position) * 4);
    
    //a%b is a random integer in the range 0 .. (b-1)
    
    //Top doors
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width -2) + newRoom->position.x +1;
    newRoom->doors[0]->y = newRoom->position.y;
    
    //Left side
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = newRoom->position.x;
    newRoom->doors[1]->y = rand() % (height -1) + newRoom->position.y + 1;
    
    //Bottom doors
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (width -2) + newRoom->position.x +1;
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height -1;
    
    //Right side
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width -1;
    newRoom->doors[3]->y = rand() % (height -1) + newRoom->position.y + 1;
    
    return newRoom;
    
}

int drawRoom(Room *room) {
    int x;
    int y;
    
    //Draw top and bottom
    for(x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); //Top
        mvprintw(room->position.y + room->height - 1, x, "-"); //bottom
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
    mvprintw(room->doors[0]->y,room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y,room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y,room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y,room->doors[3]->x, "+");
    
    return 1;
}
//Currently work for everything far right door to far right door
int connectDoors(Position *doorOne, Position *doorTwo) {
    Position tempDoorOne;
    Position tempDoorTwo;
    
    //if we have to connect rooms from right to left
    if(doorTwo->x < doorOne->x){
        tempDoorOne.x = doorTwo->x;
        tempDoorOne.y = doorTwo->y;
        
        tempDoorTwo.x = doorOne->x;
        tempDoorTwo.y = doorOne->y;
    }else {
        tempDoorOne.x = doorOne->x;
        tempDoorOne.y = doorOne->y;
        
        tempDoorTwo.x = doorTwo->x;
        tempDoorTwo.y = doorTwo->y;
    }
    
    int xPosBetweenRoom = randRange(tempDoorOne.x+1,tempDoorTwo.x, 1);
    int yPosBetweenRoom = randRange(tempDoorOne.y,tempDoorTwo.y, 0);
    
    for(int i = tempDoorOne.x; i < xPosBetweenRoom; i++) {
        tempDoorOne.x++;
        mvprintw(tempDoorOne.y, tempDoorOne.x, "#");
    }
    
    
    for(int i = tempDoorTwo.x; i > xPosBetweenRoom; i--) {
        tempDoorTwo.x--;
        mvprintw(tempDoorTwo.y, tempDoorTwo.x, "#");
    }
    
    // >= make sure the two corridors do not draw over the top of each other
    while(tempDoorOne.y >= yPosBetweenRoom) {
        tempDoorOne.y--;
        mvprintw(tempDoorOne.y,tempDoorOne.x,"$");
    }
    
    while(tempDoorTwo.y < yPosBetweenRoom) {
        tempDoorTwo.y++;
        mvprintw(tempDoorTwo.y,tempDoorTwo.x,"#");
    }
    
    return 1;
}

//Todo: readup on this function
int randRange(int min, int max, int exclusive) {
    if(exclusive) {
        max -= 1;
    }
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}
