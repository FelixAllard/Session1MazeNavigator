//
// Created by xilef on 9/22/2025.
//

#include "ArduinoMaze.h"
#include "Struct/CurrentTile.h"

#include "lib/LibRobUS/src/LibRobus.h"
#include "PidTest.h"
#include <Arduino.h>


#define ROWS 3
#define COLS 7

_Bool tileMap[ROWS][COLS] = {0}; //All variable initialized as false
///@author Felix Allard
///@brief {0 = Left}
///{1 = Top ( Straight )}
///{2 = Right}
///{3 = down}
///@attention 1 is Straight
///@name Facing Direction
int facingDirection = 1;


///@author Felix
///@brief The function called before everything else. This is called by the C++ Initializer
///@file {main.cpp}
void SetupMaze() {
    BoardInit();

}

///@def The loop function of Arduino
///@brief A function that is always looped in the robot
void LoopMaze() {

}

///@brief A function that goes straight
void Advance() {
    MOTOR_SetSpeed(0,0.5);
    MOTOR_SetSpeed(1,0.5);
}

///
/// @param directionToFaceAfter Where the Robot will be facing after

void Turn(int directionToFaceAfter) {
    if directionToFaceAfter// = 0 (left);
        MOTOR_SetSpeed(0,-0.5);
        MOTOR_SetSpeed(1,0.5);
    // resetter à vitesse 0 après turn de 90 deg?

    if directionToFaceAfter// = 1 (right);
        MOTOR_SetSpeed(0,0.5);
        MOTOR_SetSpeed(1,-0.5);
    // resetter à vitesse 0 après turn de 90 deg?
}

typedef struct {
    int x;
    int y;
} Coordinate;