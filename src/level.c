#include "rogue.h"

Level *createLevel(int level) {
    Level *newLevel = malloc(sizeof(Level));
    newLevel->level = level;
    newLevel->noOfRooms = 3;
    newLevel->rooms = roomSetUp();
    //Save level after rooms are created!
    newLevel->tiles = saveLevelPositions();

     addEnemy(newLevel);

    return newLevel;
}

Room **roomSetUp() {
    /*
     We need to dereference twice, access first address which happens to be a
     pointer then deference that pointer.
     */
    Room **rooms;
    //Allocates no of bytes for object type Room * 6, enough for 6 rooms
    rooms = malloc(sizeof(Room)*6);
    rooms[0] = createRoom(13,13,6,8);
    drawRoom(rooms[0]);
    
    rooms[1] = createRoom(2,40,6,8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(13,55,6,8);
    drawRoom(rooms[2]);
    
    createCorridor(rooms[0]->doors[3], rooms[1]->doors[1]);
    createCorridor(rooms[1]->doors[3], rooms[2]->doors[1]);

    //createCorridor(rooms[0]->doors[3], rooms[2]->doors[1]);
    return rooms;
}

char **saveLevelPositions() {
    int x, y;
    int mapWidth = 100;
    int mapHeight = 25;
    char **positions;
    positions = malloc(sizeof(char *) * mapHeight);
    
    for(y = 0; y < mapHeight; y++) {
        positions[y] = malloc(sizeof(char) * mapWidth);
        for(x = 0; x < mapWidth; x++) {
            positions[y][x] = mvinch(y,x);
        }
    } 

    return positions;
}
