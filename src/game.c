#include "rogue.h"

void render(Game *game) {
	clear();
	printStats(game->levels[game->currentLevel - 1]);
	drawLevel(game->levels[game->currentLevel - 1]);
}

int gameLoop(Game *game) {
    int ch = '\0';
    Position *newPosition;
    Level *level;

    if(game->currentLevel == 0) {
    	game->levels[game->currentLevel] = createLevel(1);
    	game->currentLevel++;
    }

    level = game->levels[game->currentLevel - 1];

    //Main game loop
    while(ch != 'q') {
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveEnemy(level);

        render(game);

        if(level->user->health <= 0) {
            return -1;
        }
        ch = getch();
    }
    return 0;
}