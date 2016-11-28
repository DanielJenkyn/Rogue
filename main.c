#include <stdio.h>
#include "ncurses.h"
#include <stdlib.h>

typedef struct Player
{
    int xPos;
    int yPos;
    int health;
}Player;

int screenSetUp();
int mapSetUp();
Player *playerSetUp();

int main() {
    Player *user;
    int ch;
    screenSetUp();
    mapSetUp();
    user = playerSetUp();
    while((ch = getch()) != 'q') {

    }
    endwin();
    return 0;
}

int screenSetUp() {
    initscr();
    printw("Hello World");
    noecho();
    refresh();

    return 0;
}

int mapSetUp() {
	mvprintw(13,13, "+-----+");
    mvprintw(14,13, "|.....|");
    mvprintw(15,13, "|.....|");
    mvprintw(16,13, "|.....|");
    mvprintw(17,13, "|.....|");
    mvprintw(18,13, "+-----+");

    return 0;
}

Player *playerSetUp() {
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xPos = 14;
    newPlayer->yPos = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPos, newPlayer->xPos, "@");
    move(newPlayer->yPos, newPlayer->xPos);

    return newPlayer;

}