#include <stdio.h>
#include "ncurses.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef  struct Position {
    int x;
    int y;

    
}Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position doors[4];
    //Monster ** monsters //Array of pointers to montsters
    //Item ** items //Array of pointers to items
    
}Room;

typedef struct Player {
    Position position;
    int health;
    //Room *room;
}Player;

int screenSetUp();
Room **mapSetUp();
Player *playerSetUp();
int handleInput(int, Player *user);
int checkPosition(int, int, Player *user);
int playerMove(int, int, Player *user);

//Room functions
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);

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
    srand(time(NULL));

    return 1;
}

Room **mapSetUp() {

    /*
    We need to dereference twice, access first address which happens to be a
    pointer then deference that pointer. 
    */
    Room **rooms;
    //Allocates no of bytes for object type Room * 6, enough for 6 rooms
    rooms = malloc(sizeof(Room)*6);
    rooms[0] = createRoom(13,13,6,8);
    drawRoom(rooms[0]);

    return rooms;

}

Room *createRoom(int y, int x, int height, int width) {

    Room *newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;
 
    //a%b is a random integer in the range 0 .. (b-1)

    //Top doors
    newRoom->doors[0].x = rand() % (width -2) + newRoom->position.x +1;
    newRoom->doors[0].y = newRoom->position.y;

    //Bottom doors
    newRoom->doors[1].x = rand() % (width -2) + newRoom->position.x +1;
    newRoom->doors[1].y = newRoom->position.y + newRoom->height -1;

    //Left side
    newRoom->doors[2].x = newRoom->position.x;
    newRoom->doors[2].y = rand() % (height -1) + newRoom->position.y + 1;

    //Right side
    newRoom->doors[3].x = newRoom->position.x + newRoom->width -1;
    newRoom->doors[3].y = rand() % (height -1) + newRoom->position.y + 1;

    return newRoom;

}

int drawRoom(Room *room) {
    int x;
    int y;

    // //Draw corners
    // mvprintw(room->position.y, room->position.x, "+");
    // mvprintw(room->position.y, room->position.x + room->width - 1, "+");
    // mvprintw(room->position.y + room->height - 1, room->position.x, "+");
    // mvprintw(room->position.y + room->height - 1,room->position.x + room->width - 1, "+");
    //Draw top and bottom
    for(x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); //Top
        mvprintw(room->position.y + room->height - 1, x, "-"); //bottom
    }

    //Draw floor and walls(side)
    for(y = room->position.y + 1; y < room->position.y + room->height -1;y++) {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        //Draw floor
        for(x = room->position.x + 1; x<room->position.x + room->width - 1; x++) {
            mvprintw(y,x,".");
        }
    }

    //Draw doors 
    mvprintw(room->doors[0].y,room->doors[0].x, "+");
    mvprintw(room->doors[1].y,room->doors[1].x, "+");
    mvprintw(room->doors[2].y,room->doors[2].x, "+");
    mvprintw(room->doors[3].y,room->doors[3].x, "+");

    return 1;
}

Player *playerSetUp() {
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);

    return newPlayer;
}


int handleInput(int input, Player *user) {
    int newY;
    int newX;
    switch(tolower(input)) {
        case 'w':
            newY = user-> position.y -1;
            newX = user-> position.x;
            break;
        case 'a':
            newY = user-> position.y;
            newX = user-> position.x -1;
            break;
        case 's':
            newY = user-> position.y + 1;
            newX = user-> position.x;
            break;
        case 'd':
            newY = user-> position.y;
            newX = user-> position.x + 1;
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
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player *user) {
    //Remove old position
    mvprintw(user->position.y, user->position.x, ".");
    //Update player position
    user->position.y = y;
    user->position.x = x;
    //Draw player to new position
    mvprintw(user->position.y, user->position.x, "@");

    //ncurses moves cursor right after pritning, so this moves it back
    move(user->position.y, user->position.x);
}

