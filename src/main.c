#include "rogue.h"
#include "mainMenu.h"

int gameLoop() {
    int ch = '\0';
    Position *newPosition;
    Level *level;
    level = createLevel(1);
    
    //Main game loop
    while(ch != 'q') {
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveEnemy(level);

        clear();
        printStats(level);
        drawLevel(level);

        if(level->user->health <= 0) {
            return -1;
        }
        ch = getch();
    }
    return 0;
}

void menuLoop() {
    int choice;
    char *choices[] = {"Start Game","Options","End Game"};
    bool menuFlag = true;
    while(menuFlag) {
        choice = mainMenu(3, choices);

        switch(choice) {
            case START_GAME:
                gameLoop();
                clear();
                break;
            //Todo: Options menu
            case OPTIONS_MENU:
                break;
            case QUIT_GAME:
                return;
            default:
                return;
        }
    }
}

int main() {
    screenSetUp();
    menuLoop();
    endwin();
    return 0;
}

//Todo: Make more readable
int randRange(int min, int max) {
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}