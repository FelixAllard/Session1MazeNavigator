//
// Created by xilef on 9/25/2025.
//

#ifndef MAZEPROJECTSHERBROOKES1_PIDTEST_H
#define MAZEPROJECTSHERBROOKES1_PIDTEST_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constants for motors/encoders
#define LEFT 0
#define RIGHT 1

// PID parameters
extern float Kp;
extern float Ki;
extern float Kd;
extern float vitesse;

// PID variables
extern float error;
extern float lastError;
extern float integral;

// Functions to simulate hardware
void ENCODER_Reset(int encoder);
long ENCODER_Read(int encoder);
void MOTOR_SetSpeed(int motor, float speed);
void delay(int ms);
void arret(void);

// PID and movement functions
float getCorrection(void);
void avancePID(float vitesseCible, int distanceTicks);
void avance(void);
void recule(void);
void tourneDroit(void);
void tourneGauche(void);
#endif //MAZEPROJECTSHERBROOKES1_PIDTEST_H