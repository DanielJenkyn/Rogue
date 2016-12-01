#include <stdio.h>
#include "ncurses.h"
#include <stdlib.h>
#include <ctype.h>

typedef struct Room
{
    int xPos;
    int yPos;
    int height;
    int width;
    //Monster ** monsters //Array of pointers to montsters
    //Item ** items //Array of pointers to items
    
}Room;

typedef struct Player
{
    int xPos;
    int yPos;
    int health;
}Player;

int screenSetUp();
Room **mapSetUp();
Player *playerSetUp();
int handleInput(int, Player *user);
int checkPosition(int, int, Player *user);
int playerMove(int, int, Player *user);

//Room functions
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room)

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

Room **mapSetUp() {

    /*
    We need to dereference twice, access first address which happens to be a
    pointer then deference that pointer. 
    */
    Room **rooms;
    //Allocates no of bytes for object type Room * 6, enough for 6 rooms
    rooms[0] = malloc(sizeof(Room)*6)
    createRoom(13, 13,6,8);
    drawRoom(room[0]);

	mvprintw(13,13, "+-----+");
    mvprintw(14,13, "|.....|");
    mvprintw(15,13, "|.....|");
    mvprintw(16,13, "|.....|");
    mvprintw(17,13, "|.....|");
    mvprintw(18,13, "+-----+");

    return rooms;

}

Room *createRoom(int y, int x, int height, int width) {

    Room *newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->xPos = x;
    newRoom->yPos = y;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;

}

int drawRoom(Room *room) {

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

