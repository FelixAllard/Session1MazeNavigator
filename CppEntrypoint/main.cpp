#include "../main.h"

#include <iostream>

extern "C" {
#include "../ArduinoMaze.h"
}

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    blink_led_c();   // call your C function
    delay(500);
}