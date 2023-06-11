#ifndef GAME_H
#define GAME_H

#include <string>

using namespace std;

class Game
{
    public:
        Game();

        void Reset();

        bool Update(int button);
        void Draw();

        void nextWave();

        int score;
        int highScore;

        const std::string buttons[8] = { "Up", "Down", "Left", "Right", "Z", "X", "A", "S" };
        int wave[10];

        int nextButton;
        
        float time;
        int elapsedTime;
        
        
};

#endif
