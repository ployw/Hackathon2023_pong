//Project: Hackathon 2023 Pong Game
//Names: Josh Matni, Angelo Calingo, Ploy Wandeevong

#include <iostream>
#include <raylib.h>
#include <sstream>
#include "ball.cpp"
#include "paddle.cpp"
#include "cpuPaddle.cpp"

using namespace std;
#define COLORS 5

Ball ball;
Paddle player;
cpuPaddle bot;

template <typename Type>
Type getInput();
void menu();
Color GetColor(unsigned int hexValue);

int main() 
{
    const int screen_width = 1200;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Cat Pong");
    SetTargetFPS(60);

   // InitAudioDevice();
   // Music music = LoadMusicStream("intense_music.mp3");
    

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
    
    menu(); // mainMenu before playing
    
    //game loop
    while(WindowShouldClose() == false)
    {
        //UpdateMusicStream(music);
        //PlayMusicStream(music);
        //creates canvas
        BeginDrawing();
        
        //updating
        ball.update();
        player.updatePaddle();
        bot.update(ball.yCoord);

        //check for collision
        if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{player.xCoord, player.yCoord, player.width, player.height}))
        {
            ball.xSpeed *= -1;

        }

        if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{bot.xCoord, bot.yCoord, bot.width, bot.height}))
        {
            ball.xSpeed *= -1;
        }

        
        ClearBackground(SKYBLUE);
        //draw center line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        
        //user gets to choose what color they want to be, also maybe what color they want the ball
        //will be passed into the arguments when calling function

        ball.drawBall();
        bot.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpuScore), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        
        //end canvas
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void menu()
{
    cout << "Let's play Pong!" << endl;
    cout << "Enter your Name: ";
    string userName = getInput<string>();

    cout << "Welcome" << " " << userName << "!" << endl;
    
}
template <typename Type>
Type getInput()
{
    Type input;
    cin >> input;
    return input;
}

Color GetColor(unsigned int hexValue)
{
    string color;
    cout << "What color would you like your paddle to be?" << endl;
    cin >> color;
    return Color(color);
    cout << "Here is the list of colors!" << endl;
    
}
Color GetUserColor() //WORK IN PROGRESS
{
    // Prompt the user to enter a color in hexadecimal format
    cout << "Here are the Colors!" << endl;
    string Colors[COLORS] = {"WHITE: #FFFFFF", "RED: #FF0000", "GREEN: #00FF00", "BLUE: #0000FF", "YELLOW: #FFFF00"};
    for(int index = 0; index < COLORS; index++)
    {
        cout << Colors[index] << endl;
    }
    cout << "Enter the color you want in hexadecimal format: ";
    string hexInput = getInput<string>();

    // Convert the hexadecimal input string to an integer
    unsigned int hexValue;
    stringstream ss;
    ss << hex << hexInput;
    ss >> hexValue;

    // Create a Color object from the hexadecimal value using GetColor()
    Color userColor = GetColor(hexValue);

    // Return the resulting color
    return userColor;
}

