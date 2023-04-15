#include "paddle.h"

void Paddle::Draw()
{
    DrawRectangle(xCoord, yCoord, width, height, WHITE);
}

void Paddle::updatePaddle()
{
    if(IsKeyDown(KEY_UP))
    {
        yCoord = yCoord - speed;
    }

    if(IsKeyDown(KEY_DOWN))
    {
        yCoord = yCoord + speed;
    }
    LimitMovement();
    
    // if(yCoord <= 0)
    // {
    //     yCoord = 0;
    // }

    // if(yCoord + height >= GetScreenHeight())
    // {
    //     yCoord = GetScreenHeight() - height;
    // }
}
void Paddle::LimitMovement()
{
    if(yCoord <= 0)
    {
        yCoord = 0;
    }

    if(yCoord + height >= GetScreenHeight())
    {
        yCoord = GetScreenHeight() - height;
    }
}