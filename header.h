#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HEIGHT 10
#define WIDTH 10
#define ALIVE '*'
#define DEAD '0'

typedef struct _cel {
    char alive;
    int neighbours;
} cel;


void checkNeighbours(int x, int y, int limitX, int limitY, cel **table);
void checkAlive(int x, int y, cel **table);
void updateTable(int x, int y, cel **table);
void displayTable( int x, int y, cel **table, int neighbours);
cel **defineTable(int x, int y);
void insertCel(int x, int y, cel **table);
int  mainMenu();
cel **loadTable(int *x, int *y, int *currentGen);
void gameMenu(int x, int y, int counter, cel **table);



#endif // HEADER_H_INCLUDED
