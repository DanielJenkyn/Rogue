#include "rogue.h"

int main() {
    Player *user;
    int ch;
    Position *newPosition;

    Level *level;
    screenSetUp();
    level = createLevel(1);

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