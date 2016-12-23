#include "rogue.h"

Player *playerSetUp() {
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    
    newPlayer->position->x = 14;
    newPlayer->position->y = 14;
    newPlayer->health = 20;
    newPlayer->maxHealth = 20;
    newPlayer->attack = 1;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    
    mvprintw(newPlayer->position->y, newPlayer->position->x, "@");
    move(newPlayer->position->y, newPlayer->position->x);
    
    return newPlayer;
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
            move(user->position->y, user->position->x);
            break;
    }

    return 0;
}

int playerMove(Position *newPosition, Player *user, char **level) {
    char buffer[8];

    sprintf(buffer,"%c", level[user->position->y][user->position->x]);
    //Remove old position
    mvprintw(user->position->y, user->position->x, buffer);
    //Update player position
    user->position->y = newPosition->y;
    user->position->x = newPosition->x;
    //Draw player to new position
    mvprintw(user->position->y, user->position->x, "@");
    
    //ncurses moves cursor right after pritning, so this moves it back
    move(user->position->y, user->position->x);

    return 0;
}