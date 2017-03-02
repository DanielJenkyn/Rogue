#include "rogue.h"

Player *playerSetUp() {
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    
    newPlayer->health = 20;
    newPlayer->maxHealth = 20;
    newPlayer->attack = 1;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    
    return newPlayer;
}

int spawnPlayer(Room **rooms, Player *user) {
    user->position->x = rooms[3]->position.x+1;
    user->position->y = rooms[3]->position.y+1;
    move(user->position->y, user->position->x);
    return 0;
}

Position *handleInput(int input, Player *user) {
    Position *newPosition;
    newPosition = malloc(sizeof(Position));
    switch(tolower(input)) {
        case 'w':
            newPosition->y = user->position->y -1;
            newPosition->x = user-> position->x;
            break;
        case 'a':
            newPosition->y = user-> position->y;
            newPosition->x = user-> position->x -1;
            break;
        case 's':
            newPosition->y = user-> position->y + 1;
            newPosition->x = user-> position->x;
            break;
        case 'd':
            newPosition->y = user-> position->y;
            newPosition->x = user-> position->x + 1;
            break;
        default:
            break;
    }
    
    return newPosition;
}

//Check what is at new position
int checkPosition(Position *newPosition, Level *level) {
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

    return 0;
}

int playerMove(Position *newPosition, Player *user, char **level) {
    //Update player position
    user->position->y = newPosition->y;
    user->position->x = newPosition->x;

    return 0;
}

void drawPlayer(Player *player) {
    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);
}