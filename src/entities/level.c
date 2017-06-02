#include "rogue.h"
#include "level.h"
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

void drawLevel(Level *level) {
    int x,y,i;

    //Draw tiles
    for(y = 0; y < MAX_HEIGHT; y++) {
        for(x = 0; x < MAX_WIDTH; x++) {
            mvaddch(y, x, level->tiles[y][x]);
        }
    }

    //Draw enemies
    for(i = 0; i < level->noOfEnemies; i++) {
        drawEnemy(level->enemies[i]);
    }

    //Draw player
    drawPlayer(level->user);
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

//Check what is at new position
void checkPosition(Position *newPosition, Level *level) {
    //mvinch - move cursor to new pos, return char at pos
    Player *user;
    user = level->user;
    switch(mvinch(newPosition->y, newPosition->x)) {
        case '.':
        case '+':
        case '#':
            playerMove(newPosition, user, level->tiles);
            break;
        case 'X':
        case 'G':
        case 'T':
            combat(user, getEnemyAt(newPosition, level->enemies), 0);
        default:
            break;
    }
}

void addEnemy(Level *level) {
    //Max on enemy per room, and 6 rooms (Will probably change)
    level->enemies = malloc(sizeof(Enemy *) * 6);
    level->noOfEnemies = 0;

    for(int x = 0; x<level->noOfRooms;x++) {
        //50% spawn rate
        if((randRange(0,9) !=  (0|1|2|3))) {
            level->enemies[level->noOfEnemies] = selectEnemy(level->level);
            setStartPos(level->enemies[level->noOfEnemies],level->rooms[x]);
            level->noOfEnemies++;
        }
    }
}

void moveEnemy(Level *level) {
    for(int x = 0; x<level->noOfEnemies;x++) {
        if(level->enemies[x]->alive == 0) 
            continue;
        if(level->enemies[x]->pathfinding == 1) {
            pathfindingSeek(level->enemies[x]->position, level->user->position);
        } else {
            //Default to random movement
            pathfindingRandom(level->enemies[x]->position);
        }
    }
}