#include "rogue.h"

Room *createRoom(int grid) {
    
    Room *newRoom;
    newRoom = malloc(sizeof(Room));
    
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

    newRoom->height = randRange(3,10,0);
    newRoom->width = randRange(3,16,0);
    
    //room x,y offset
    newRoom->position.x += randRange(1,(29 - newRoom->width),0);
    newRoom->position.y += randRange(1,(10 - newRoom->height),0);



    newRoom->doors = malloc(sizeof(Position) * 4);
    
    //Top doors
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = randRange(newRoom->position.x+1, newRoom->position.x + newRoom->width-2, 0);
    newRoom->doors[0]->y = newRoom->position.y;
    
    //Left side
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = newRoom->position.x;
    newRoom->doors[1]->y = randRange(newRoom->position.y+1, newRoom->position.y + newRoom->height-2, 0);
    
    //Bottom doors
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = randRange(newRoom->position.x+1, newRoom->position.x + newRoom->width-2, 0);
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height-1;
    
    //Right side
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width-1;
    newRoom->doors[3]->y = randRange(newRoom->position.y+1, newRoom->position.y + newRoom->height-2, 0);
    
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
    mvprintw(room->doors[0]->y,room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y,room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y,room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y,room->doors[3]->x, "+");
    
    return 1;
}
//This function is a cluster fuck. Will switch to A* / BFS
int createCorridor(Position *doorOne, Position *doorTwo) {
    Position tempDoorOne;
    Position tempDoorTwo;

    tempDoorOne.x = doorOne->x;
    tempDoorOne.y = doorOne->y;
    tempDoorTwo.x = doorTwo->x;
    tempDoorTwo.y = doorTwo->y;

    int xPosBetweenRoom = randRange(tempDoorOne.x+1,tempDoorTwo.x, 1);
    int yPosBetweenRoom = randRange(tempDoorOne.y,tempDoorTwo.y, 0);

    //Refactor - Will most l
    //Draw Horizontal
    for(int i = tempDoorOne.x; i < xPosBetweenRoom; i++) {
        tempDoorOne.x++;
        mvprintw(tempDoorOne.y, tempDoorOne.x, "#");
    }
    
    for(int i = tempDoorTwo.x; i > xPosBetweenRoom; i--) {
        tempDoorTwo.x--;
        mvprintw(tempDoorTwo.y, tempDoorTwo.x, "#");
    }

    //Draw vertical
    if(tempDoorOne.y > yPosBetweenRoom) {
        //Draw up
        for(int i = tempDoorOne.y; i > yPosBetweenRoom; i--) {
            tempDoorOne.y--;
            mvprintw(tempDoorOne.y,tempDoorOne.x,"#");
        }
        for(int i = tempDoorTwo.y; i < yPosBetweenRoom; i++) {
            tempDoorTwo.y++;
            mvprintw(tempDoorTwo.y,tempDoorTwo.x,"#");
        }
    } else {
        //Draw down
        for(int i = tempDoorOne.y; i < yPosBetweenRoom; i++) {
            tempDoorOne.y++;
            mvprintw(tempDoorOne.y,tempDoorOne.x,"#");
        }
        for(int i = tempDoorTwo.y; i > yPosBetweenRoom; i--) {
            tempDoorTwo.y--;
            mvprintw(tempDoorTwo.y,tempDoorTwo.x,"#");
        }
    }
    return 1;
}