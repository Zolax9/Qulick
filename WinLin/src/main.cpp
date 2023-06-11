#include "raylib.h"
#include "game.h"
#include "wiimote.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    Font font;

    Game game = {};
    Wiimote wiimote = {};
    int button;

    bool mainMenu = true;

    game.highScore = 0;

    InitWindow(screenWidth, screenHeight, "Qulick");
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    font = LoadFont("data/cavestory.ttf");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        button = -1;

        if (IsKeyPressed(KEY_UP) || wiimote.allKeys.XIsKeyPressed(0))
        {
            wiimote.allKeys.keys[0] = true;
            if (button == -1) { button = 0; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[0] = false;
        }
        if (IsKeyPressed(KEY_DOWN) || wiimote.allKeys.XIsKeyPressed(1))
        {
            wiimote.allKeys.keys[1] = true;
            if (button == -1) { button = 1; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[1] = false;
        }
        if (IsKeyPressed(KEY_LEFT) || wiimote.allKeys.XIsKeyPressed(2))
        {
            wiimote.allKeys.keys[2] = true;
            if (button == -1) { button = 2; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[2] = false;
        }
        if (IsKeyPressed(KEY_RIGHT) || wiimote.allKeys.XIsKeyPressed(3))
        {
            wiimote.allKeys.keys[3] = true;
            if (button == -1) { button = 3; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[3] = false;
        }
        if (IsKeyPressed(KEY_Z) || wiimote.allKeys.XIsKeyPressed(4))
        {
            wiimote.allKeys.keys[4] = true;
            if (button == -1) { button = 4; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[4] = false;
        }
        if (IsKeyPressed(KEY_X)  || wiimote.allKeys.XIsKeyPressed(5))
        {
            wiimote.allKeys.keys[5] = true;
            if (button == -1) { button = 5; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[5] = false;
        }
        if (IsKeyPressed(KEY_A)  || wiimote.allKeys.XIsKeyPressed(6))
        {
            wiimote.allKeys.keys[6] = true;
            if (button == -1) { button = 6; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[6] = false;
        }
        if (IsKeyPressed(KEY_S)  || wiimote.allKeys.XIsKeyPressed(7))
        {
            wiimote.allKeys.keys[7] = true;
            if (button == -1) { button = 7; }
            else { button = 8; }
        } else
        {
            wiimote.allKeys.keys[7] = false;
        }

        wiimote.Update();

        if (IsKeyPressed(KEY_SPACE)) { mainMenu = false; }
        if (!mainMenu) { if (game.Update(button)) { mainMenu = true; } }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(BLACK);

	    if (mainMenu)
	    {
		    DrawTextEx(
                font,
                "Qulick",
                Vector2{ (screenWidth/2) - (MeasureTextEx(font, "Qulick", 64, 1).x/2), 16 },
                64,
                1,
                Color{ 128, 32, 128, 255 }
		    );

		    DrawTextEx(
		        font,
                "Press Space to start!",
                Vector2{ (screenWidth/2) - (MeasureTextEx(font, "Press Space to start!", 32, 1).x/2), (screenHeight/2) - (32/2) - 2},
                32,
                1,
                Color{ 255, 255, 255, 255 }
		    );

		    DrawTextEx(
                font,
                ("Highscore: " + to_string(game.highScore)).c_str(),
                Vector2{ 0, screenHeight - 40 },
                32,
                1,
                Color{255, 255, 255, 255}
		    );

		    DrawTextEx(
                font,
                "Zolax",
                Vector2{ screenWidth - MeasureTextEx(font, "Zolax", 32, 1).x, screenHeight - 40 },
                32,
                1,
                Color{ 255, 255, 255, 255 }
		    );
		}
	        else
		{
		    DrawTextEx(
                font,
                to_string(game.score).c_str(),
                Vector2{ (screenWidth/2) - (MeasureTextEx(font, to_string(game.score).c_str(), 64, 1).x/2), 0},
                64,
                1,
                Color{255, 255, 255, 255}
		    );

		    DrawTextEx(
                font,
			    game.buttons[game.wave[game.nextButton]].c_str(), 
		        Vector2{ (screenWidth/2) - (MeasureTextEx(font, game.buttons[game.wave[game.nextButton]].c_str(), 64, 1).x/2), (screenHeight/2) - (72/2) - 72 - 4 },
			    64,
                1,
			    Color{ 255, 255, 0, 255 }
		    );

		    if (game.nextButton < 9)
		    {
			    DrawTextEx(
				    font,
                    game.buttons[game.wave[game.nextButton + 1]].c_str(), 
				    Vector2{ (screenWidth/2) - (MeasureTextEx(font, game.buttons[game.wave[game.nextButton + 1]].c_str(), 64, 1).x/2), (screenHeight/2) - (72/2)},
				    64,
                    1,
				    Color{255, 255, 255, 255 }
			    );
		    }
		    if (game.nextButton < 8)
		    {
			    DrawTextEx(
			        font,
                    game.buttons[game.wave[game.nextButton + 2]].c_str(),
				    Vector2{ (screenWidth/2) - (MeasureTextEx(font, game.buttons[game.wave[game.nextButton + 2]].c_str(), 64, 1).x/2), (screenHeight/2) - (72/2) + 72 + 4 },
				    64,
                    1,
				    Color{ 255, 255, 255, 255 }
                );
		    }

		    DrawRectangle(
                0,
                screenHeight - 32,
                (screenWidth * ((game.time-game.elapsedTime) / game.time)),
                32,
                Color{ 0, 255, 0, 255 }
            );
		}
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
