#include "rogue.h"

int main() {
    int ch;
    Position *newPosition;
    Level *level;
    
    screenSetUp();
    level = createLevel(2);
    printStats(level);
    
    //Main game loop
    while((ch = getch()) != 'q') {
        printStats(level);
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveEnemy(level);
        move(level->user->position->y,level->user->position->x);
    }
    endwin();
    return 0;
}

//Todo: readup on this function
int randRange(int min, int max) {
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}