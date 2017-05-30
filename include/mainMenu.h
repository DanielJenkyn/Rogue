#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <menu.h>
#include <stdlib.h>

enum {START_GAME, OPTIONS_MENU, QUIT_GAME};

int mainMenu(int numberItems, char *choices[]);
void closeMenu(int numberItems, MENU *menu, ITEM **items);

#endif