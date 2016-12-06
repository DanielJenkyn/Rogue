#include "rogue.h"

Player *playerSetUp() {
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));
    
    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;
    
    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);
    
    return newPlayer;
}


int handleInput(int input, Player *user) {
    int newY;
    int newX;
    switch(tolower(input)) {
        case 'w':
            newY = user-> position.y -1;
            newX = user-> position.x;
            break;
        case 'a':
            newY = user-> position.y;
            newX = user-> position.x -1;
            break;
        case 's':
            newY = user-> position.y + 1;
            newX = user-> position.x;
            break;
        case 'd':
            newY = user-> position.y;
            newX = user-> position.x + 1;
            break;
        default:
            break;
    }
    
    checkPosition(newY,newX,user);
}

//Check what is at new position
int checkPosition(int newY, int newX, Player *user) {
    int space;
    //mvinch - move cursor to new pos, return char at pos
    switch(mvinch(newY,newX)) {
        case '.':
        case '+':
        case '#':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player *user) {
    //Remove old position
    mvprintw(user->position.y, user->position.x, ".");
    //Update player position
    user->position.y = y;
    user->position.x = x;
    //Draw player to new position
    mvprintw(user->position.y, user->position.x, "@");
    
    //ncurses moves cursor right after pritning, so this moves it back
    move(user->position.y, user->position.x);
}
