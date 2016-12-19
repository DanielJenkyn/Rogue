#include "rogue.h"

int main() {
    Player *user;
    int ch;
    Position *newPosition;
    Level *level;
    screenSetUp();
    level = createLevel(5);
    user = playerSetUp();
    
    //Main game loop
    while((ch = getch()) != 'q') {
        newPosition = handleInput(ch, user);
        checkPosition(newPosition, user,level->tiles);
        
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