#include "rogue.h"

int main() {
    int ch;
    Position *newPosition;
    Level *level;
    screenSetUp();
    level = createLevel(2);
    
    
    //Main game loop
    while((ch = getch()) != 'q') {
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveEnemy(level);
        move(level->user->position->y,level->user->position->x);
    }
    endwin();
    return 0;
}

int screenSetUp() {
    initscr();
    printw("Hello World");
    noecho();
    refresh();
    srand(time(NULL));
    
    return 1;
}

//Todo: readup on this function
int randRange(int min, int max, int exclusive) {
    if(exclusive) {
        max -= 1;
    }
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}