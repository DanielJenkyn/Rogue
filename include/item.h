#ifndef ITEM_H
#define ITEM_H

#include "weapon.h"
#include "position.h"

typedef enum { 
	WEAPON_TYPE, 
	POTION_TYPE
}ItemType;

typedef struct Item {
	ItemType type;
	Position *position;

	union {
		Weapon *weapon;
	}item;

	char string[256];
	
}Item;

//itemFactory functions
Item *createSword(int attack, int durability);

#endif