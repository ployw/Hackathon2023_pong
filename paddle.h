#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <raylib.h>
using namespace std;

class Paddle
{
    protected:
        void LimitMovement();
    public:
        float xCoord, yCoord;
        float width, height;
        int speed;
    
        void Draw();
        void updatePaddle();
};
#endif
