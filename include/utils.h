#ifndef UTILS_H
#define UTILS_H

int pathFind(Position *start, Position *end);
void addPositionYX(int **frontier, int frontierCount, int y, int x);
int addNeighbours(int **frontier, int frontierCount, int ***cameFrom, int y, int x);

#endif