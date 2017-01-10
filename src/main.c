#include "rogue.h"
#include "mainMenu.h"

int gameLoop() {
    int ch;
    Position *newPosition;
    Level *level;
    level = createLevel(2);
    printStats(level);
    
    //Main game loop
    while((ch = getch()) != 'q') {
        printStats(level);
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveEnemy(level);
        move(level->user->position->y,level->user->position->x);

        if(level->user->health <= 0) {
            return -1;
        }
    }
    return 0;
}

void menuLoop() {
    int choice;
    char *choices[] = {"Start Game","End Game"};
    while(true) {
        choice = mainMenu(2, choices);

        switch(choice) {
            case START_GAME:
                gameLoop();
                clear();
                break;
            case QUIT_GAME:
                return;
                break;
        }
    }
}

int main() {
    screenSetUp();
    menuLoop();
    endwin();
    return 0;
}

//Todo: readup on this function
int randRange(int min, int max) {
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}