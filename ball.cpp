#include "ball.h"

void Ball::drawBall()
{
    DrawCircle(xCoord, yCoord, ballRadius, WHITE); //maybe change color depending on user choice
    
}
void Ball::update()
{
    xCoord += xSpeed;
    yCoord += ySpeed;

    //ball collisions
    if(yCoord + ballRadius >= GetScreenHeight() || yCoord - ballRadius <= 0)
    {
        ySpeed *= -1;
    }

    //bot wins
    if(xCoord + ballRadius >= GetScreenWidth())
    {
        cpuScore++;
        resetBall();
    }

    //player wins
    if(xCoord - ballRadius <= 0)
    {
        playerScore++;
        resetBall();
    }
}

void Ball::resetBall()
{
    xCoord = GetScreenWidth() / 2;
    yCoord = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    xSpeed *= speed_choices[GetRandomValue(0, 1)];
    ySpeed *= speed_choices[GetRandomValue(0,1)];
}