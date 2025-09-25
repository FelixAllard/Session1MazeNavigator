#include <stdlib.h>

#include "lib/LibRobUS/src/LibRobus.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Arduino.h>

//
// Created by xilef on 9/25/2025.
//
// Correction PID basée sur différence encodeurs
// ----- PID -----

// ================== CONSTANTS ==================
#define LEFT  0   // left motor/encoder IDs
#define RIGHT 1   // right motor/encoder IDs

// PID constants
float Kp = 0.6;
float Ki = 0.0;
float Kd = 0.1;

// Motor speed
float vitesse = 100.0;  // adjust according to your motors

// PID variables
float error = 0, lastError = 0, integral = 0;

// ================== ENCODER MOCK FUNCTIONS ==================
// Replace these with your actual encoder read/reset code
long leftCount = 0;
long rightCount = 0;

long ENCODER_Read(int motor) {
    if (motor == LEFT) return leftCount;
    else return rightCount;
}

void ENCODER_Reset(int motor) {
    if (motor == LEFT) leftCount = 0;
    else rightCount = 0;
}

// ================== MOTOR MOCK FUNCTIONS ==================
// Replace with actual motor control code
void MOTOR_SetSpeed(int motor, float speed) {
    // Example: just print for testing
    if (motor == LEFT) {
        Serial.print("Left motor: "); Serial.println(speed);
        leftCount += speed / 10; // simulate encoder
    } else {
        Serial.print("Right motor: "); Serial.println(speed);
        rightCount += speed / 10; // simulate encoder
    }
}

// ================== UTILITY FUNCTIONS ==================
void arret() {
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
}

// ================== PID CORRECTION ==================
float getCorrection() {
    long left = ENCODER_Read(LEFT);
    long right = ENCODER_Read(RIGHT);

    error = left - right;
    integral += error;
    float derivative = error - lastError;
    lastError = error;

    return Kp * error + Ki * integral + Kd * derivative;
}

// ================== MOVEMENTS ==================
void avancePID(float vitesseCible, int distanceTicks) {
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while ((ENCODER_Read(LEFT) + ENCODER_Read(RIGHT)) / 2 < distanceTicks) {
        float correction = getCorrection();

        float vitesseLeft  = vitesseCible - correction;
        float vitesseRight = vitesseCible + correction;

        MOTOR_SetSpeed(LEFT, vitesseLeft);
        MOTOR_SetSpeed(RIGHT, vitesseRight);

        delay(5);
    }
    arret();
}

void avance() {
    avancePID(vitesse, 3600);  // move forward 1 wheel rotation
}

void recule() {
    avancePID(-vitesse, 1800); // move backward 0.5 wheel rotation
}

void tourneDroit() {
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (abs(ENCODER_Read(LEFT)) < 1800) {
        MOTOR_SetSpeed(LEFT, vitesse);
        MOTOR_SetSpeed(RIGHT, -vitesse);
        delay(5);
    }
    arret();
}

void tourneGauche() {
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (abs(ENCODER_Read(RIGHT)) < 1800) {
        MOTOR_SetSpeed(LEFT, -vitesse);
        MOTOR_SetSpeed(RIGHT, vitesse);
        delay(5);
    }
    arret();
}

// ================== ARDUINO SETUP & LOOP ==================
void setup() {
    Serial.begin(9600);
    avance();
    delay(1000);
    recule();
    delay(1000);
    tourneDroit();
    delay(1000);
    tourneGauche();
}

void loop() {
    // nothing here
}
