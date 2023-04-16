//Project: Hackathon 2023 Pong Game
//Names: Josh Matni, Angelo Calingo, Ploy Wandeevong

#include <iostream>
#include <raylib.h>
#include <sstream>
#include "ball.cpp"
#include "paddle.cpp"
#include "cpuPaddle.cpp"
#include <iostream>
#include <string>
using namespace std;


typedef enum screen { TITLE = 0, OPTIONS, GAMEPLAY} screen;

//Global Object variables
Ball ball;
Paddle player;
cpuPaddle bot;

//initalizing colors
Color Dark_Red = Color{181, 89, 89,255};
Color BGRed2 = Color{201, 143, 143, 255};
Color BGRed1 = Color{201, 153, 153, 255};
Color Light = Color{219, 186, 186, 100};
Color Purple = Color{144, 50, 61, 255};
Color Blue = Color{21, 30, 63, 255};
Color Orange = Color{71, 45, 48, 255};
Color Cream = Color{230, 216, 204, 255};
Color Cream2 = Color{237, 210, 185, 255};

//play click sound
void makeClick(Sound);

int main() 
{
    screen currentScreen = TITLE;

    const int screen_width = 1200;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong");

    //creating cat texture from picture
    //Image catto = LoadImage("jasper.png");
    //ImageDraw(&catto, catto, (Rectangle){ 0, 0, (float)catto.width, (float)catto.height }, (Rectangle){ 30, 40, catto.width*1.5f, catto.height*1.5f }, WHITE);
   // ImageCrop(&catto, (Rectangle){ 0, 50, (float)catto.width, (float)catto.height });
   // ImageResize(&catto, 500, 500);
   // Texture2D cat = LoadTextureFromImage(catto);
   // UnloadImage(catto);

    SetTargetFPS(60);

    //music!!
    InitAudioDevice();
    Music title = LoadMusicStream("resources/title.mp3");
    Music music = LoadMusicStream("resources/intense_music.mp3");
    Sound bonk = LoadSound("resources/bonk.mp3");
    Sound click = LoadSound("resources/click.mp3");
    
    //initalizing
    ball.ballRadius = 20; //size of ball
    ball.xCoord = (screen_width / 2); //ball location
    ball.yCoord = (screen_height / 2);
    ball.xSpeed = 7;
    ball.ySpeed = 7;

    player.width = 25;
    player.height = 120;
    player.xCoord = screen_width - player.width - 10;
    player.yCoord = screen_height/2 - player.height/2;
    player.speed = 6;

    bot.height = 120;
    bot.width = 25;
    bot.xCoord = 10;
    bot.yCoord = (screen_height/2) - (bot.height/2);
    bot.speed = 6;

    //to check if user changed colors
    bool changeColorPaddle = false;
    bool changeColorBall = false;

    //game loop
    while(WindowShouldClose() == false)
    {

        //updating
        switch(currentScreen)
        {
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    makeClick(click);
                    
                    //if user didn't pick a color ---> set to default white
                    if(changeColorPaddle == false)
                    {
                        player.setColor(WHITE);
                    }
                    if(changeColorBall == false)
                    {
                        ball.setColor(WHITE);
                    }
                    currentScreen = GAMEPLAY;
                }

                if(IsKeyPressed(KEY_O))
                {
                    makeClick(click);
                    currentScreen = OPTIONS;
                }
            } break;
            
            case OPTIONS:
            {
                //allow player to set color of their paddle
                if(IsKeyPressed(KEY_ONE))
                {
                    player.setColor(Purple); //purple paddle 
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_TWO))
                {
                    player.setColor(Blue); //blue paddle
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_THREE))
                {
                    player.setColor(Orange); //orange paddle
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_FOUR))
                {
                    player.setColor(Cream); //green paddle
                    changeColorPaddle = true;
                }
        
        
                if(IsKeyPressed(KEY_Z))
                {
                    makeClick(click);
                    currentScreen = TITLE; //exit options
                }
                if(IsKeyPressed(KEY_FIVE))
                {
                    ball.setColor(Purple); //purple ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_SIX))
                {
                    ball.setColor(Blue); //blue ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_SEVEN))
                {
                    ball.setColor(Orange); //orange ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_EIGHT))
                {
                    ball.setColor(Cream); //green ball
                    changeColorBall = true;
                }
               
            } break;

            case GAMEPLAY:
            {
                ball.update();
                player.updatePaddle();
                bot.update(ball.yCoord);

                //check for collision
                if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{player.xCoord, player.yCoord, player.width, player.height}))
                {
                    ball.xSpeed *= -1;
                    SetSoundVolume(bonk, 0.2);
                    PlaySound(bonk); //collision sound

                }

                if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{bot.xCoord, bot.yCoord, bot.width, bot.height}))
                {
                    ball.xSpeed *= -1;
                    SetSoundVolume(bonk, 0.2);
                    PlaySound(bonk);//collision sound
                }
                if(IsKeyPressed(KEY_Z))
                {
                    makeClick(click);
                    currentScreen = TITLE;
                }
            } break;
        }

        //rendering
        BeginDrawing();
        switch(currentScreen)
        {
            case TITLE:
            {
                //play title music
                SetMusicVolume(title, 0.15);
                UpdateMusicStream(title);
                PlayMusicStream(title);

                //Title Screen
                ClearBackground(BGRed1);
                DrawRectangle(0, 200, screen_width, 180, (Color) {255, 255, 255, 50});
                DrawText("Hackathon 2023", 305, 120, 70, Dark_Red);
                DrawText("PONG", 320, 200, 200, WHITE);
                DrawText("by Angelo Calingo, Josh Matni, Ploy Wandeevong", 345, 400, 20, WHITE);
                DrawText("press 'enter' to play!", 320, 600, 50, WHITE);
                DrawText("press 'o' for customization options!", 325, 675, 30, WHITE);
            
                //DrawTexture(cat, 200, 400, WHITE);
            break;
            }

            case OPTIONS:
            {
                SetMusicVolume(title, 0.15);
                UpdateMusicStream(title);
                PlayMusicStream(title);

                ClearBackground(BGRed1);
                DrawRectangle(50, 50, screen_width - 100, screen_height - 100, (Color) {255, 255, 255, 50});
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
            } break;
            
            case GAMEPLAY:
            {
                //play music
                SetMusicVolume(music, 0.25);
                UpdateMusicStream(music);
                PlayMusicStream(music);
                
                //background colors and middle line
                ClearBackground(BGRed2);
                DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, BGRed1);
                DrawCircle(screen_width / 2, screen_height / 2, 200, Light);
                DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
                DrawText("press z to return", 10, 10, 20, WHITE);

                //drawing all the assets
                ball.drawBall();
                bot.setColor(WHITE);
                bot.Draw();
                player.Draw();
                DrawText(TextFormat("%i", cpuScore), screen_width / 4 - 20, 20, 80, WHITE);
                DrawText(TextFormat("%i", playerScore), 3 * screen_width / 4 - 20, 20, 80, WHITE);
            } break;
        }
        
        //end canvas
        EndDrawing();
    }

    UnloadMusicStream(title);
    UnloadMusicStream(music);
    UnloadSound(bonk);
    UnloadSound(click);
   //UnloadTexture(cat);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void makeClick(Sound click)
{
    SetSoundVolume(click, 0.2);
    PlaySound(click); 
}