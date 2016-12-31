#include "rogue.h"

Level *createLevel(int level) {
    Level *newLevel = malloc(sizeof(Level));
    newLevel->level = level;
    newLevel->noOfRooms = 6;
    newLevel->rooms = roomSetUp(newLevel->noOfRooms);
    
    //Save level after rooms are created!
    newLevel->tiles = saveLevelPositions();
    newLevel->user = playerSetUp();
    spawnPlayer(newLevel->rooms, newLevel->user);

    addEnemy(newLevel);

    return newLevel;
}

Room **roomSetUp(int noOfRooms) {

    /*
     We need to dereference twice, access first address which happens to be a
     pointer then deference that pointer.
     */
    Room **rooms;
    //Allocates no of bytes for object type Room * 6, enough for 6 rooms
    rooms = malloc(sizeof(Room) * noOfRooms);

    for(int x = 0; x < noOfRooms; x++) {
        rooms[x] = createRoom(x);
        drawRoom(rooms[x]);
    }
    pathFind(rooms[0]->doors[3], rooms[1]->doors[1]);
    return rooms;
}

char **saveLevelPositions() {
    int x, y;
    char **positions;
    positions = malloc(sizeof(char *) * MAX_HEIGHT);
    
    for(y = 0; y < MAX_HEIGHT; y++) {
        positions[y] = malloc(sizeof(char) * MAX_WIDTH);
        for(x = 0; x < MAX_WIDTH; x++) {
            positions[y][x] = mvinch(y,x);
        }
    } 
    return positions;
}