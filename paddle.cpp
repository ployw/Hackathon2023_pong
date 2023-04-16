#include "paddle.h"

void Paddle::Draw()
{
    DrawRectangleRounded(Rectangle{xCoord, yCoord, width, height}, 0.8, 0, WHITE);
    //DrawRectangle(xCoord, yCoord, width, height, WHITE);
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
Color Paddle::GetUserColor(string hexInput)
{
    // Prompt the user to enter a color in hexadecimal format
    //cout << "Enter the color you want in hexadecimal format: ";
    //displayColors();
    //string hexInput = getInput<string>();

    // Convert the hexadecimal input string to an integer
    unsigned int hexValue;
    stringstream ss;
    ss << hex << hexInput;
    ss >> hexValue;

    // Create a Color object from the hexadecimal value using GetColor()
    Color userColor = GetColor(hexValue);

    // Return the color
    return userColor;
}