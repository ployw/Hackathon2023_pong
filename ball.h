#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <raylib.h>
using namespace std;

int playerScore = 0;
int cpuScore = 0;

class Ball
{
    public:
        float xCoord, yCoord;
        int xSpeed, ySpeed, ballRadius;

        void resetBall();
        void drawBall();
        void update();
};
#endif