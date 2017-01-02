#include "rogue.h"
#include "utils.h"

void pathFind(Position *start, Position *end) {
	int i,j;
	int y,x;
	int tempY;
	int **frontier = malloc(sizeof(int*)* MAX_HEIGHT * MAX_WIDTH);
	int ***cameFrom = malloc(sizeof(int**) * MAX_HEIGHT);
	int frontierIndex = 0;
	int frontierCount = 0;

	for (i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) {
        frontier[i] = malloc(sizeof(int)*2);
    }

    for (i = 0; i < MAX_HEIGHT; i++) {
        cameFrom[i] = malloc(sizeof(int*)* MAX_WIDTH);
        for (j = 0; j < MAX_WIDTH; j++) {
            cameFrom[i][j] = malloc(sizeof(int)*2);
            cameFrom[i][j][0] = -1;
            cameFrom[i][j][1] = -1;
        }
    }
	//Add start to came from. -9 is just an arbitrary value
	cameFrom[start->y][start->x][0] = -9;
	cameFrom[start->y][start->x][1] = -9;

	//Add start to frontier
	addPositionYX(frontier, frontierCount, start->y, start->x);
	frontierCount++;

	while(frontierIndex < frontierCount) {
		y = frontier[frontierIndex][0];
		x = frontier[frontierIndex][1];
		frontierIndex++;

		if(y == end->y && x == end->x) {
			break;
		}

		frontierCount = addNeighbours(frontier, frontierCount, cameFrom, y, x);
	}

	y = end->y;
	x = end->x;

	while((y != start->y) || (x != start->x)) {
		tempY = y;
		y = cameFrom[tempY][x][0];
		x = cameFrom[tempY][x][1];
		mvprintw(y, x, "#");
	}
}

void addPositionYX(int **frontier, int frontierCount, int y, int x) {
	frontier[frontierCount][0] = y;
	frontier[frontierCount][1] = x;
}

int addNeighbours(int **frontier, int frontierCount, int ***cameFrom, int y, int x) {
	//North
	if(y > 0 && cameFrom[y - 1][x][0] < 0 && checkPos(y - 1, x)) {
		addPositionYX(frontier, frontierCount, y - 1, x);
		frontierCount++;
		cameFrom[y - 1][x][0] = y;
		cameFrom[y - 1][x][1] = x;
	}
	//South
	if(y < (MAX_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && checkPos(y + 1, x)) {
		addPositionYX(frontier, frontierCount, y+1, x);
		frontierCount++;
		cameFrom[y + 1][x][0] = y;
		cameFrom[y + 1][x][1] = x;
	}
	//East
	if(x < (MAX_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && checkPos(y, x + 1)) {
		addPositionYX(frontier, frontierCount, y, x + 1);
			frontierCount++;
		cameFrom[y][x + 1][0] = y;
		cameFrom[y][x + 1][1] = x;
	}
	//West
	if(x > 0 && cameFrom[y][x - 1][0] < 0 && checkPos(y, x - 1)) {
		addPositionYX(frontier, frontierCount, y, x - 1);
		frontierCount++;
		cameFrom[y][x - 1][0] = y;
		cameFrom[y][x - 1][1] = x;
	}
	return frontierCount;
}

int checkPos(int y, int x) {
    char temp = mvinch(y, x);

    if (temp == '.' || temp == '|' || temp == '-') {
    	return 0;
    } else {
    	return 1;
    }
}