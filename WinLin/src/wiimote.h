#include "xwiimote.h"
#include "keys.h"

#ifndef WIIMOTE_H
#define WIIMOTE_H

class Wiimote
{
    private:
        xwii_iface *iface;
        xwii_event event;
        bool freeze = false;

        int ret;
        int fds_num;



    public:
        Wiimote();
        Keys allKeys;

        char *get_dev();
        void key_show(xwii_event *event);

        void Update();
};

#endif
