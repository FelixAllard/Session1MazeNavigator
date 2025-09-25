#include <stdio.h>
#include <stdlib.h>
#include "PidTest.h"
#include <math.h>
// Déclarations des constantes
#define LEFT 0
#define RIGHT 1

// Variables globales pour simuler les encodeurs et moteurs
long leftEncoderCount = 0;
long rightEncoderCount = 0;
float leftMotorSpeed = 0;
float rightMotorSpeed = 0;

// Paramètres PID
float Kp = 0.6;
float Ki = 0.0;
float Kd = 0.1;
float vitesse = 0.5;

// Variables PID
float error = 0, lastError = 0, integral = 0;

// Fonctions de simulation matérielle
void ENCODER_Reset(int encoder) {
    if (encoder == LEFT) leftEncoderCount = 0;
    else rightEncoderCount = 0;
}

long ENCODER_Read(int encoder) {
    if (encoder == LEFT) return leftEncoderCount;
    else return rightEncoderCount;
}

void MOTOR_SetSpeed(int motor, float speed) {
    // Simulation de l'effet sur les encodeurs
    if (motor == LEFT) {
        leftMotorSpeed = speed;
        leftEncoderCount += (long)(speed * 10); // Simulation du mouvement
    } else {
        rightMotorSpeed = speed;
        rightEncoderCount += (long)(speed * 10); // Simulation du mouvement
    }
}

void delay(int ms) {
    // Simulation simple d'un délai
    for (volatile int i = 0; i < ms * 1000; i++);
}

void arret() {
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    delay(100);
}

// Fonction PID
float getCorrection() {
    long leftCount = ENCODER_Read(LEFT);
    long rightCount = ENCODER_Read(RIGHT);

    error = leftCount - rightCount;
    integral += error;
    float derivative = error - lastError;
    lastError = error;

    return (Kp * error + Ki * integral + Kd * derivative);
}

// Mouvements
void avancePID(float vitesseCible, int distanceTicks) {
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);
    integral = 0;
    lastError = 0;

    while ((ENCODER_Read(LEFT) + ENCODER_Read(RIGHT)) / 2 < distanceTicks) {
        float correction = getCorrection();

        float vitesseLeft = vitesseCible - correction;
        float vitesseRight = vitesseCible + correction;

        // Limitation des vitesses
        if (vitesseLeft > 1.0) vitesseLeft = 1.0;
        if (vitesseLeft < -1.0) vitesseLeft = -1.0;
        if (vitesseRight > 1.0) vitesseRight = 1.0;
        if (vitesseRight < -1.0) vitesseRight = -1.0;

        MOTOR_SetSpeed(LEFT, vitesseLeft);
        MOTOR_SetSpeed(RIGHT, vitesseRight);

        delay(5);
    }
    arret();
}

void avance() {
    avancePID(vitesse, 3600);
}

void recule() {
    avancePID(-vitesse, 1800);
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
