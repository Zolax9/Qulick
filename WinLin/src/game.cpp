#include <raylib.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctime>

#include "game.h"

#define FRAME_RATE 60

using namespace std;

Game::Game()
{
    srand(0);
    
    Reset();
    highScore = 0;
};

void Game::Reset()
{
    for (int i = 0; i < 10; ++i) { wave[i] = rand()%8; }

    if (score > highScore) { highScore = score; }
    score = 0;
    
    nextButton = 0;

    time = FRAME_RATE * 10; // 10 seconds
    elapsedTime = 0;
}

void Game::nextWave()
{
    nextButton = 0;

    time *= 0.95f;
    if (time <= FRAME_RATE) { time = FRAME_RATE + 1.0f;}

    elapsedTime = 0;

    for (int i = 0; i < 10; ++i) { wave[i] = rand()%8; }
};

bool Game::Update(int button) // 0-7 = DPAD, A, B, 1 and 2 -1 = none, 8 = invalid
{
    ++elapsedTime;

    if (elapsedTime == (int)time)
    {
        Reset();
        return true;
    }
    else if ((button != -1) & (button != 8))
    {
        if (button == wave[nextButton])
        {
            ++score;

            ++nextButton;
            if (nextButton == 10) { nextWave(); }
        }
    }

    return false;
};

void Game::Draw()
{
};
