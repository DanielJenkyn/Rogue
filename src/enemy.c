#include "rogue.h"
/*
0 Spider: 
	levels: 1-3
	symbol: X
	health: 2
	attack: 1
	defence: 1
	speed: 2
	pathfinding: 1 (random)

1 Goblin:
	levels: 2-5
	symbol: G
	health: 5
	attack: 3
	defence: 1
	speed: 1
	pathfinding: 2 (seeking)

2 Troll:
	levels: 4-6
	symbol: T
	health: 15
	attack: 5
	defence: 3
	speed: 1
	pathfinding: 1 (random)
*/

int addEnemy(Level *level) {
	//Max on enemy per room, and 6 rooms (Will probably change)
	level->enemies = malloc(sizeof(Enemy *) * 6);
	level->noOfEnemies = 0;

	for(int x = 0; x<level->noOfRooms;x++) {
		if((randRange(0,1,0) == 0)) {
			level->enemies[level->noOfEnemies] = selectEnemy(level->level);
			setStartPos(level->enemies[level->noOfEnemies],level->rooms[x]);
			level->noOfEnemies++;
		}

	}
	return 0;
}

Enemy *selectEnemy(int level) {
	int monster;
	switch(level) {
		case 1:
			monster = 0;
			break;
		case 2:
		case 3:
		monster = randRange(0,1,0);
			break;
		case 4:
		case 5:
			monster = randRange(1,2,0);
			break;
		case 6:
			monster = 2;
			break;

	}

	switch(monster) {
		case 0://Spider
			return createEnemy('X',2,1,1,2,1);
		case 1://Goblin
			return createEnemy('G',5,3,1,1,2);
		case 2://Troll
			return createEnemy('T',15,5,3,1,1);
	}
}

Enemy *createEnemy(char symbol, int health, int attack, int defence, int speed, int pathfinding) {
	Enemy *newEnemy = malloc(sizeof(Enemy));

	newEnemy->symbol = symbol;
	newEnemy->health = health;
	newEnemy->attack = attack;
	newEnemy->defence = defence;
	newEnemy->speed = speed;
	newEnemy->pathfinding = pathfinding;

	return newEnemy;
}

int setStartPos(Enemy *enemy, Room *room) {
	char buffer[8];
	enemy->position.y = randRange(room->position.y+1, room->position.y + room->height-2, 0);
	enemy->position.x = randRange(room->position.x+1, room->position.x + room->width-2, 0);
	sprintf(buffer, "%c", enemy->symbol);
	mvprintw(enemy->position.y, enemy->position.x,buffer);
	return 0;
}
