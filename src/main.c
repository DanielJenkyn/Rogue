#include "rogue.h"

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
    
    rooms[1] = createRoom(2,40,6,8);
    drawRoom(rooms[1]);
    
    connectDoors(rooms[1]->doors[1], rooms[0]->doors[3]);
    
    return rooms;
}
