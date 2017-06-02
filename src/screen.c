#include "rogue.h"
#include "utils.h"

void screenSetUp() {
    if(!initscr()) {
        printf("Error initializing screen.\n");
        exit(1);
    }
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    srand(time(NULL));
}

void printStats(Level *level) {
	mvprintw(25, 0, "    Level: %d", level->level);
	printw("    Health: %d/%d",level->user->health, level->user->maxHealth);
	printw("    Attack: %d", level->user->attack);
	printw("    Exp: %d", level->user->exp);
    printw("    ");
}

void printInventory(Player *player) {
    mvprintw(26, 0, "    Inventory: ");

    for(int i = 0; i < player->numberOfItems; i++){
        printw(player->items[i]->string);
    }
}