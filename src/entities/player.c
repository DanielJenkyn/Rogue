#include "rogue.h"
#include "player.h"

Player *playerSetUp() {
    MAX_ITEMS = 25;
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    newPlayer->items = malloc(sizeof(Item*));
    
    newPlayer->symbol = '@';
    newPlayer->health = 20;
    newPlayer->maxHealth = 20;
    newPlayer->attack = 1;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    newPlayer->numberOfItems = 0;

    //Give player weapon
    newPlayer->items[newPlayer->numberOfItems] = createSword(1,20);
    newPlayer->numberOfItems++;

    //Create string output from formatted data
    sprintf(newPlayer->string, "%c", newPlayer->symbol);
    
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

void playerMove(Position *newPosition, Player *user, char **level) {
    //Update player position
    user->position->y = newPosition->y;
    user->position->x = newPosition->x;
}

void drawPlayer(Player *player) {
    mvprintw(player->position->y, player->position->x, player->string);
    move(player->position->y, player->position->x);
}