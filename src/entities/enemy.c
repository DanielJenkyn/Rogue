#include "rogue.h"
#include "enemy.h"

/*
0 Spider: 
	levels: 1-3
	symbol: X
	health: 2
	attack: 1
	defence: 1
	speed: 2
	pathfinding: 0 //Random
1 Goblin:
	levels: 2-5
	symbol: G
	health: 5
	attack: 3
	defence: 1
	speed: 1
	pathfinding: 1 //Seek
2 Troll:
	levels: 4-6
	symbol: T
	health: 15
	attack: 5
	defence: 3
	speed: 1
	pathfinding: 1
*/

Enemy *selectEnemy(int level) {
	int enemy;
	switch(level) {
		case 1:
			enemy = 0;
			break;
		case 2:
		case 3:
			enemy = randRange(0,1);
			break;
		case 4:
		case 5:
			enemy = randRange(1,2);
			break;
		case 6:
			enemy = 2;
			break;
		default:
			enemy = 0;
	}

	switch(enemy) {
		case 0://Spider
			return createEnemy('X',2,1,1,2,0);
		case 1://Goblin
			return createEnemy('G',5,3,1,1,1);
		case 2://Troll
			return createEnemy('T',15,5,3,1,1);
		default:
			return 0;
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
	newEnemy->alive = 1;

	//Create string output from formatted data
	sprintf(newEnemy->string, "%c", symbol);

	newEnemy->position = malloc(sizeof(Position));

	return newEnemy;
}

void killEnemy(Enemy *enemy) {
	enemy->alive = 0;
}

void drawEnemy(Enemy *enemy) {
	if(enemy->alive) {
		mvprintw(enemy->position->y, enemy->position->x, enemy->string);
	}
}

void pathfindingSeek(Position *start, Position *destination) {
	if((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y,start->x - 1) == '.')) {
		start->x = start->x - 1;
	}else if((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y,start->x + 1) == '.')) {
		start->x = start->x + 1; 
 	}else if((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1,start->x) == '.')) {
		start->y = start->y + 1; 
 	}else if((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1,start->x) == '.')) {
		start->y = start->y - 1;
	}
}

void pathfindingRandom(Position *position) {
	int random = randRange(0,4);

	switch(random) {
		case 0:
			if(mvinch(position->y - 1, position->x) == '.'){position->y -= 1;}
			break;
		case 1:
			if(mvinch(position->y + 1, position->x) == '.'){position->y += 1;}
			break;
		case 2:
			if(mvinch(position->y, position->x + 1) == '.'){position->x += 1;}
			break;
		case 3:
			if(mvinch(position->y, position->x - 1) == '.'){position->x -= 1;}
			break;
		case 4:
			break;
	}
}

Enemy *getEnemyAt(Position *position, Enemy **enemies) {
	for(int x = 0; x < 6; x++) {
		if((position->y == enemies[x]->position->y) && (position->x == enemies[x]->position->x)) {
			return enemies[x];
		}
	}
	return NULL;
}