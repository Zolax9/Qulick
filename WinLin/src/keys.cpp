#include "raylib.h"
#include "xwiimote.h"
#include "keys.h"

Keys::Keys()
{
};

void Keys::Update()
{
    for (int i = 0; i < 8; ++i)
    {
        switch (keys[i])
        {
            case true:
                switch (stillDown[i])
                {
                    case true:
                        pressed[i] = false;
                        break;

                    case false:
                        stillDown[i] = true;
                        pressed[i] = true;
                        break;
                }

                keys[0] = true;
                break;

            case false:
                if (stillDown[i])
                {
                    stillDown[i] = false;
                    pressed[i] = false;
                }

                keys[0] = false;
                break;
        }
    }
};

bool Keys::XIsKeyPressed(int key) { return pressed[key]; };
bool Keys::XIsKeyReleased(int key) { return !pressed[key]; };
