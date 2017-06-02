//Kind of conforms to the factory design pattern
#include "rogue.h"
#include "item.h"
#include "weapon.h"

Item *createSword(int attack, int durability) {
	Item *item = malloc(sizeof(Item));
	item->type = WEAPON_TYPE;
	strcpy(item->string, "Sword");

	Weapon *weapon = malloc(sizeof(Weapon));
	weapon->attack = attack;
	weapon->durability = durability;

	item->item.weapon = weapon;

	return item;
}