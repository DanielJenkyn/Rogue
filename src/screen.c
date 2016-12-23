#include "rogue.h"

int screenSetUp() {
    initscr();
    printw("Hello World");
    noecho();
    refresh();
    srand(time(NULL));
    
    return 1;
}

int printStats(Level *level) {
	mvprintw(25, 0, "    Level: %d", level->level);
	printw("    Health: %d/%d",level->user->health, level->user->maxHealth);
	printw("    Attack: %d", level->user->attack);
	printw("    Exp: %d", level->user->exp);
	return 1;
}