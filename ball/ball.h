#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <raylib.h>
#include <unistd.h>
using namespace std;

int playerScore = 0;
int cpuScore = 0;

class Ball
{
    Color ballColor;
    public:
        float xCoord, yCoord;
        int xSpeed, ySpeed, ballRadius;

        void resetBall();
        void drawBall();
        void update();

        void setColor(const Color);
};
#endif