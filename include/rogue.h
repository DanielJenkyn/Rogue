//Include only once, to avoid duplicate function declarations
#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/*******Global vars*******/
static const int MAX_HEIGHT = 25;
static const int MAX_WIDTH = 100;

//Main functions 
int randRange(int min, int max); //Move

#endif