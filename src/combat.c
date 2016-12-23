#include "rogue.h"

int combat(Player *player, Enemy *enemy, int order) {

	//Player attack
	if(order == 0) {
		enemy->health -= player->attack;
		if(enemy->health > 0) {
			player->health -= enemy->attack;
		}else {
			killEnemy(enemy);
		}
	}
	//enemy attack
	if(order == 1) {
		player->health -= enemy->attack;
		if(player->health > 0) {
			enemy->health -= player->attack;
		}
	}
	return 1;
}