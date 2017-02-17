#include "rogue.h"
#include "utils.h"

Level *createLevel(int level) {
    Level *newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel->level = level;
    newLevel->noOfRooms = 6;
    newLevel->rooms = roomSetUp();
    connectDoors(newLevel);
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
    rooms = malloc(sizeof(Room) * 6);

    for(int x = 0; x < 6; x++) {
        rooms[x] = createRoom(x, 4);
        drawRoom(rooms[x]);
    }
    return rooms;
}

void connectDoors(Level *level) {
    int i,j;
    int randRoom, randDoor;
    int count;

    for (i = 0; i < level->noOfRooms; i++) {
        for (j = 0; j < level->rooms[i]->noOfDoors; j++) {
            if (level->rooms[i]->doors[j]->connected == 1) {
                continue;
            }

            count = 0;

            //Try twice to connect doors
            while (count < 2) {
                randRoom = randRange(0, level->noOfRooms - 1);
                randDoor = randRange(0, level->rooms[randRoom]->noOfDoors -1);

                if (level->rooms[randRoom]->doors[randDoor]->connected == 1 || randRoom == i) {
                    count++;
                    continue;
                }

                pathFind(&level->rooms[randRoom]->doors[randDoor]->position, &level->rooms[i]->doors[j]->position);
                
                level->rooms[randRoom]->doors[randDoor]->connected = 1;
                level->rooms[i]->doors[j]->connected = 1;
                break;
            }
        }
    }
}

char **saveLevelPositions() {
    int x,y;
    char **positions;
    positions = malloc(sizeof(char *) * MAX_HEIGHT);
    
    for(y = 0; y < MAX_HEIGHT; y++) {
        positions[y] = malloc(sizeof(char) * MAX_WIDTH);
        for(x = 0; x < MAX_WIDTH; x++) {
            positions[y][x] = (char)mvinch(y,x);
        }
    } 
    return positions;
}