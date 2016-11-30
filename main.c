#include <stdio.h>
#include "ncurses.h"
#include <stdlib.h>
#include <ctype.h>

typedef struct Player
{
    int xPos;
    int yPos;
    int health;
}Player;

int screenSetUp();
int mapSetUp();
Player *playerSetUp();
int handleInput(int, Player *user);
int checkPosition(int, int, Player *user);
int playerMove(int, int, Player *user);

int main() {
    Player *user;
    int ch;
    screenSetUp();
    mapSetUp();
    user = playerSetUp();

    //Main game loop
    while((ch = getch()) != 'q') {
        handleInput(ch, user);

    }
    endwin();
    return 0;
}

int screenSetUp() {
    initscr();
    printw("Hello World");
    noecho();
    refresh();

    return 1;
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

    playerMove(newPlayer->yPos, newPlayer->xPos, newPlayer);

    return newPlayer;
}


int handleInput(int input, Player *user) {
    int newY;
    int newX;
    switch(tolower(input)) {
        case 'w':
            newY = user-> yPos -1;
            newX = user-> xPos;
            break;
        case 'a':
            newY = user-> yPos;
            newX = user-> xPos -1;
            break;
        case 's':
            newY = user-> yPos + 1;
            newX = user-> xPos;
            break;
        case 'd':
            newY = user-> yPos;
            newX = user-> xPos + 1;
            break;
        default:
            break;
    }

    checkPosition(newY,newX,user);
}

//Check waht is at new position
int checkPosition(int newY, int newX, Player *user) {
    int space;
    //mvinch - move cursor to new pos, return char at pos
    switch(mvinch(newY,newX)) {
        case '.':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->yPos, user->xPos);
            break;
    }
}

int playerMove(int y, int x, Player *user) {
    //Remove old position
    mvprintw(user->yPos, user->xPos, ".");
    //Update player position
    user->yPos = y;
    user->xPos = x;
    //Draw player to new position
    mvprintw(user->yPos, user->xPos, "@");

    //ncurses moves cursor right after pritning, so this moves it back
    move(user->yPos, user->xPos);
}

