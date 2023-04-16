#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <raylib.h>
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

        Color getColor() const;
        void setColor(const Color);
};
#endif
