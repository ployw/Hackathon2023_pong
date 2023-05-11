//Project: Hackathon 2023 Pong Game
//Names: Josh Matni, Angelo Calingo, Ploy Wandeevong

#include <iostream>
#include <raylib.h>
#include <sstream>
#include "../functions/functions.cpp"
#include <string>
using namespace std;


typedef enum screen { TITLE = 0, OPTIONS, GAMEPLAY} screen;

//Global Object variables
Ball ball;
Paddle player;
cpuPaddle bot;

int main() 
{
    screen currentScreen = TITLE;

    const int screen_width = 1200;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong");

    SetTargetFPS(60);

    //load music!!
    InitAudioDevice();
    Music title = LoadMusicStream("../resources/title.mp3");
    Music music = LoadMusicStream("../resources/intense_music.mp3");
    Sound bonk = LoadSound("../resources/bonk.mp3");
    Sound click = LoadSound("../resources/click.mp3");
    
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
                    makeSound(click, 0.35);
                    
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
                    makeSound(click, 0.35);
                    currentScreen = OPTIONS;
                }
            } break;
            
            case OPTIONS:
            {
                //allow player to set color of their paddle
                if(IsKeyPressed(KEY_ONE))
                {
                    makeSound(click, 0.25);
                    player.setColor(Purple); //purple paddle 
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_TWO))
                {
                    makeSound(click, 0.25);
                    player.setColor(Blue); //blue paddle
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_THREE))
                {
                    makeSound(click, 0.25);
                    player.setColor(Orange); //orange paddle
                    changeColorPaddle = true;
                }
                if(IsKeyPressed(KEY_FOUR))
                {
                    makeSound(click, 0.25);
                    player.setColor(Cream); //green paddle
                    changeColorPaddle = true;
                }
                
                //allow player to change ball color
                if(IsKeyPressed(KEY_FIVE))
                {
                    makeSound(click, 0.25);
                    ball.setColor(Purple); //purple ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_SIX))
                {
                    makeSound(click, 0.25);
                    ball.setColor(Blue); //blue ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_SEVEN))
                {
                    makeSound(click, 0.25);
                    ball.setColor(Orange); //orange ball
                    changeColorBall = true;
                }
                if(IsKeyPressed(KEY_EIGHT))
                {
                    makeSound(click, 0.25);
                    ball.setColor(Cream); //green ball
                    changeColorBall = true;
                }
                
                //exit case
                if(IsKeyPressed(KEY_Z))
                {
                    makeSound(click, 0.35);
                    currentScreen = TITLE; //exit options
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
                    makeSound(bonk, 0.25);
                }

                if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{bot.xCoord, bot.yCoord, bot.width, bot.height}))
                {
                    ball.xSpeed *= -1;
                    makeSound(bonk, 0.25);
                }
                if(IsKeyPressed(KEY_Z))
                {
                    //reset scores
                    cpuScore = 0;
                    playerScore = 0;
                    makeSound(click, 0.35);
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
                //title screen
                playMusic(title, 0.15);
                drawTitleScreen();
            
            break;
            }

            case OPTIONS:
            {
                playMusic(title, 0.15);
                drawOptionScreen();
                
            } break;
            
            case GAMEPLAY:
            {
                playMusic(music, 0.20);
                
                drawGameplayScreen();

                //draw assets
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

    //unload all files
    UnloadMusicStream(title);
    UnloadMusicStream(music);
    UnloadSound(bonk);
    UnloadSound(click);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
