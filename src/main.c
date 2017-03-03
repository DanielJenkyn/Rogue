#include "rogue.h"
#include "mainMenu.h"

void menuLoop() {
    int choice;
    char *choices[] = {"Start Game","Options","End Game"};
    bool menuFlag = true;

    Game game;
    game.currentLevel = 0;
    while(menuFlag) {
        choice = mainMenu(3, choices);

        switch(choice) {
            case START_GAME:
                gameLoop(&game);
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