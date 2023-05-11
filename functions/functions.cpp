#include "functions.h"
#include "../paddles/paddle.cpp"
#include "../paddles/cpuPaddle.cpp"
#include "../ball/ball.cpp"


//visuals
void drawTitleScreen()
{
    ClearBackground(BGRed1);
    DrawRectangle(0, 200, GetScreenWidth(), 180, (Color) {255, 255, 255, 50});
    DrawText("Hackathon 2023", 305, 120, 70, Dark_Red);
    DrawText("PONG", 320, 200, 200, WHITE);
    DrawText("by Angelo Calingo, Josh Matni, Ploy Wandeevong", 345, 400, 20, WHITE);
    DrawText("press 'enter' to play!", 320, 600, 50, WHITE);
    DrawText("press 'o' for customization options!", 325, 675, 30, WHITE);
}

void drawOptionScreen()
{
    ClearBackground(BGRed1);
    DrawRectangle(50, 50, GetScreenWidth() - 100, GetScreenHeight() - 100, (Color) {255, 255, 255, 50});
    //customize paddle
    DrawText("paddle color:", 440, 70, 50, WHITE);
    DrawText("1", 440, 150, 40, WHITE);
    DrawText("2", 540, 150, 40, WHITE);
    DrawText("3", 640, 150, 40, WHITE);
    DrawText("4", 740, 150, 40, WHITE);
    DrawCircle(450, 250, 40, Purple);
    DrawCircle(550, 250, 40, Blue);
    DrawCircle(650, 250, 40, Orange);
    DrawCircle(750, 250, 40, Cream);

    //customize ball
    DrawText("ping pong ball color:", 350, 350, 50, WHITE);
    DrawText("5", 440, 425, 40, WHITE);
    DrawText("6", 540, 425, 40, WHITE);
    DrawText("7", 640, 425, 40, WHITE);
    DrawText("8", 740, 425, 40, WHITE);
    DrawCircle(450, 525, 40, Purple);
    DrawCircle(550, 525, 40, Blue);
    DrawCircle(650, 525, 40, Orange);
    DrawCircle(750, 525, 40, Cream);

    DrawText("(press z to go back)", 445, 700, 30, WHITE);
}

void drawGameplayScreen()
{
    float screen_width = GetScreenWidth();
    float screen_height = GetScreenHeight();

    //draw bg
    ClearBackground(BGRed2);
    DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, BGRed1);
    DrawCircle(screen_width / 2, screen_height / 2, 200, Light);
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    DrawText("press z to return", 10, 10, 20, WHITE);
}


//sounds
void makeSound(Sound effect, float volume)
{
    SetSoundVolume(effect, volume);
    PlaySound(effect); 
}

void playMusic(Music song, float volume)
{
    SetMusicVolume(song, volume);
    UpdateMusicStream(song);
    PlayMusicStream(song);
}

