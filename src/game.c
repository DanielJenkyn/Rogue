#include "rogue.h"
#include "game.h"
#include "level.h"
#include "utils.h"

void render(Game *game) {
	clear();
	printStats(game->levels[game->currentLevel - 1]);
	drawLevel(game->levels[game->currentLevel - 1]);
}

void gameLoop(Game *game) {
    int ch = '\0';
    ch = tolower(ch);
    Position *newPosition;
    Level *level;

    if(game->currentLevel == 0) {
    	game->levels[game->currentLevel] = createLevel(1);
    	game->currentLevel++;
    }

    level = game->levels[game->currentLevel - 1];

    //Main game loop
    bool isRunning = true;
    while(isRunning) {

        if(ch == 'q') {
            break;
        }

        if(ch == 'i') {
            printInventory(level->user);
        }else {
            newPosition = handleInput(ch, level->user);
            checkPosition(newPosition, level);
            moveEnemy(level);

            render(game);

            if(level->user->health <= 0) {
                return;
            }
        }
        ch = getch();
    }
}