#include "cpuPaddle.h"

void cpuPaddle::update(int ball_y)
{
    if(yCoord + height/2 > ball_y)
    {
        yCoord = yCoord - speed;
    }
    if(yCoord + height/2 <= ball_y)
    {
        yCoord = yCoord + speed;
    }
}