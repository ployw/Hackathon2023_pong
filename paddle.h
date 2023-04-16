#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <raylib.h>
#include <sstream>
using namespace std;

class Paddle
{
    private:
        Color color;
    protected:
        void LimitMovement();
    public:
        float xCoord, yCoord;
        float width, height;
        int speed;
    
        void Draw();
        void updatePaddle();
        Color GetUserColor(string);
};
#endif
