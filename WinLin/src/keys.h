#include "xwiimote.h"

#ifndef KEYS_H
#define KEYS_H

class Keys
{
    private:
        bool pressed[8] = { false, false, false, false, false, false, false, false };
        bool stillDown[8] = { false, false, false, false, false, false, false, false };

    public:
        Keys();
        void Update();
        
        bool XIsKeyPressed(int key);
        bool XIsKeyReleased(int key);

        bool keys[8] = { false, false, false, false, false, false, false, false };
};

#endif
