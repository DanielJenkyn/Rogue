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
    switch(tolower(input)) {
        case 'w':
            playerMove(user->yPos - 1,user->xPos, user);
            break;
        case 'a':
             playerMove(user->yPos,user->xPos - 1, user);
            break;
        case 's':
            playerMove(user->yPos + 1,user->xPos, user);
            break;
        case 'd':
         playerMove(user->yPos,user->xPos + 1, user);
            break;
        default:
            break;
    }
}

int playerMove(int newYPos, int newXPos, Player *user) {
    //Remove old position
    mvprintw(user->yPos, user->xPos, ".");
    //Update player position
    user->yPos = newYPos;
    user->xPos = newXPos;
    //Draw player to new position
    mvprintw(user->yPos, user->xPos, "@");

    //ncurses moves cursor right after pritning, so this moves it back
    move(user->yPos, user->xPos);
}