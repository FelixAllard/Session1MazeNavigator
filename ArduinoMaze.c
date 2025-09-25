//
// Created by xilef on 9/22/2025.
//

#include "ArduinoMaze.h"
#include "CurrentTile.h"

#include "lib/LibRobUS/src/LibRobus.h"

#define ROWS 3
#define COLS 7

_Bool tileMap[ROWS][COLS] = {0}; //All variable initialized as false


void SetupMaze() {
    BoardInit();
}


void LoopMaze() {

}

void Advance() {

}
void Turn() {

}

typedef struct {
    int x;
    int y;
} Coordinate;