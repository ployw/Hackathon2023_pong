#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <raylib.h>
using namespace std;

//initalize colors
Color Dark_Red = Color{181, 89, 89,255};
Color BGRed2 = Color{201, 143, 143, 255};
Color BGRed1 = Color{201, 153, 153, 255};
Color Light = Color{219, 186, 186, 100};
Color Purple = Color{144, 50, 61, 255};
Color Blue = Color{21, 30, 63, 255};
Color Orange = Color{71, 45, 48, 255};
Color Cream = Color{230, 216, 204, 255};
Color Cream2 = Color{237, 210, 185, 255};

//visuals
void drawTitleScreen();
void drawOptionScreen();
void drawGameplayScreen();

//sounds
void makeSound(Sound, float);
void playMusic(Music, float);





#endif