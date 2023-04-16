#include "paddle.h"

void Paddle::Draw()
{
    DrawRectangleRounded(Rectangle{xCoord, yCoord, width, height}, 0.8, 0, color);
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

Color Paddle::getColor() const
{
    return color;
}
void Paddle::setColor(const Color newColor)
{
    color = newColor;
}