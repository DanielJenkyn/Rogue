#include "rogue.h"

Level *createLevel(int level) {
    Level *newLevel = malloc(sizeof(Level));
    newLevel->level = level;
    newLevel->noOfRooms = 3;
    newLevel->rooms = roomSetUp();
    //Save level after rooms are created!
    newLevel->tiles = saveLevelPositions();
    newLevel->user = playerSetUp();
    spawnPlayer(newLevel->rooms, newLevel->user);

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

    for(int x =0; x < 6; x++) {
        rooms[x] = createRoom(x);
        drawRoom(rooms[x]);
    }
    
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