//Project: Hackathon 2023 Pong Game
//Names: Josh Matni, Angelo Calingo, Ploy Wandeevong

#include <iostream>
#include <raylib.h>
#include <sstream>
#include "ball.cpp"
#include "paddle.cpp"
#include "cpuPaddle.cpp"
#include <iostream>

using namespace std;
#define MAX_CHAR_INPUT 6
#define COLORS 5


typedef enum screen { TITLE = 0, OPTIONS, GAMEPLAY} screen;
Ball ball;
Paddle player;
cpuPaddle bot;

//initalizing background colors
Color Dark_Red = Color{168, 89, 89, 255};
Color Red = Color{186, 127, 127, 255};

template <typename Type>
Type getInput();
void menu();
Color GetUserColor(string);
//void displayColors();

int main() 
{
    screen currentScreen = TITLE;

    const int screen_width = 1200;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Cat Pong");

    //creating cat texture from picture
    Image catto = LoadImage("jasper.png");
    ImageDraw(&catto, catto, (Rectangle){ 0, 0, (float)catto.width, (float)catto.height }, (Rectangle){ 30, 40, catto.width*1.5f, catto.height*1.5f }, WHITE);
    ImageCrop(&catto, (Rectangle){ 0, 50, (float)catto.width, (float)catto.height });
    ImageResize(&catto, 500, 500);
    Texture2D cat = LoadTextureFromImage(catto);
    UnloadImage(catto);

    SetTargetFPS(60);

    //music!!
    InitAudioDevice();
    Music title = LoadMusicStream("title.mp3");
    Music music = LoadMusicStream("intense_music.mp3");
    Sound bonk = LoadSound("annoy.mp3");
    
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

    //for customizing options
    bool mouseOnText = false;
    Rectangle textBox = {screen_width/2.0f - 100, 180, 225, 50 };
    int letterCount = 0;
    char color[MAX_CHAR_INPUT+1] = "\0";


    //game loop
    while(WindowShouldClose() == false)
    {

        //updating
        switch(currentScreen)
        {
            case TITLE:
            {
                //check for enter --> start
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = GAMEPLAY;
                }

                if(IsKeyPressed(KEY_O))
                {
                    currentScreen = OPTIONS;
                }
            } break;
            
            case OPTIONS:
            {
                if (CheckCollisionPointRec(GetMousePosition(), textBox))
                {
                    mouseOnText = true;
                }
                else
                {
                    mouseOnText = false;
                }

                if(mouseOnText)
                {
                    //set user cursor
                    SetMouseCursor(MOUSE_CURSOR_IBEAM);

                    int key = GetCharPressed();
                    
                    //check for keys pressed, only keys in range
                    while (key > 0)
                    {
                        if((key >= 32) && (key <= 125) && (letterCount < MAX_CHAR_INPUT))
                        {
                            color[letterCount] = (char)key;

                            //add null at end
                            color[letterCount+1] = '\0';
                            letterCount++;
                        }

                        //get next char
                        key = GetCharPressed();
                    }

                    //delete if backspace is pressed
                    if(IsKeyPressed(KEY_BACKSPACE))
                    {
                        letterCount--;
                        if(letterCount < 0)
                        {
                            letterCount = 0;
                            color[letterCount] = '\0';
                        }
                    }
                }
                else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                if(IsKeyPressed(KEY_B))
                {
                    currentScreen = TITLE;
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
                    SetSoundVolume(bonk, 1);
                    PlaySound(bonk); //collision sound

                }

                if(CheckCollisionCircleRec(Vector2{ball.xCoord, ball.yCoord}, ball.ballRadius, Rectangle{bot.xCoord, bot.yCoord, bot.width, bot.height}))
                {
                    ball.xSpeed *= -1;
                    //UpdateMusicStream(bonk);
                    SetSoundVolume(bonk, 1);
                    PlaySound(bonk);//collision sound
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
                SetMusicVolume(title, 0.25);
                UpdateMusicStream(title);
                PlayMusicStream(title);
            
                ClearBackground(Red);
                DrawText("Hackathon 2023", 300, 120, 70, Dark_Red);
                DrawText("PONG", 315, 200, 200, WHITE);
                DrawText("press 'enter' to play!", 315, 600, 50, WHITE);
                DrawText("press 'o' for customization options!", 320, 700, 30, WHITE);
            
                DrawTexture(cat, 200, 400, WHITE);
            break;
            }

            case OPTIONS:
            {
                SetMusicVolume(title, 0.15);
                UpdateMusicStream(title);
                PlayMusicStream(title);

                SetSoundVolume(bonk, 1);
                PlaySound(bonk);//collision sound

                ClearBackground(Dark_Red);
                DrawText("customize your paddle color!", 160, 60, 60, WHITE);
                DrawText("enter color (in hex format, all caps):", 225, 120, 40, WHITE);

                DrawRectangleRec(textBox, WHITE);
                DrawText(color, (int)textBox.x + 5, (int)textBox.y + 8, 40, Dark_Red);
                DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_CHAR_INPUT), 510, 250, 20, DARKGRAY);
                DrawText("(press b to go back)", 380, 700, 40, WHITE);
            } break;
            
            case GAMEPLAY:
            {
                //play music
                SetMusicVolume(music, 0.25);
                UpdateMusicStream(music);
                PlayMusicStream(music);

                //background colors and middle line
                ClearBackground(Dark_Red);
                DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Red);
                DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
                
                //user gets to choose what color they want to be, also maybe what color they want the ball
                //will be passed into the arguments when calling function
                //Color colorChoice = GetUserColor(color); //do conversions to get color choice
            
                //drawing
                ball.drawBall();
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
    UnloadTexture(cat);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
template <typename Type>
Type getInput()
{
    Type input;
    cin >> input;
    return input;
}

Color GetUserColor(string hexInput)
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
/*void displayColors()
{
    cout << "Here are the Colors!" << endl;
    cout << "COLOR: HEXADECIMAL" << endl;
    string Colors[COLORS] = {"WHITE: #FFFFFF", "RED: #FF0000", "GREEN: #00FF00", "BLUE: #0000FF", "YELLOW: #FFFF00"};
    for(int index = 0; index < COLORS; index++)
    {
        cout << Colors[index] << endl;
    }
}*/
