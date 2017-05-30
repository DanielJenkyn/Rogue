#include "mainMenu.h"

int mainMenu(int numberItems, char *choices[]) {
	int i;
	MENU * menu;
	ITEM ** items = malloc(sizeof(**items)*numberItems);
	ITEM * current;
	int value;

	for(i = 0; i < numberItems; i++) {
		items[i] = new_item(choices[i], "");
	}
	items[i] = (ITEM*)NULL;

	menu = new_menu((ITEM**)items);
	post_menu(menu);
	refresh();

	//Menu loop
	int c;
	while(true) {
		c = getch();
		switch(c) {
			case KEY_DOWN:
				menu_driver(menu,REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case 10: //Enter key
				current = current_item(menu);
				value = item_index(current);
				closeMenu(numberItems, menu, items);
				return value;
		}
	}
}

void closeMenu(int numberItems, MENU *menu, ITEM **items) {
	unpost_menu(menu);
	free_menu(menu);
	for(int i = 0; i < numberItems;i++) {
		free_item(items[i]);
	}
}