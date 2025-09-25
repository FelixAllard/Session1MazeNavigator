#include <iostream>

//Read as C
extern "C" {
#include "../ArduinoMaze.h"
}

void Setup() {
    //We are leaving C++
    SetupMaze();
}

void Loop() {
    //We are Leaving C++
    LoopMaze();
}