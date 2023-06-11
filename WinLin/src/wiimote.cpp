#include <stdlib.h>
#include <iostream>
#include "xwiimote.h"
#include "wiimote.h"

Wiimote::Wiimote()
{
    ret = 0;
    char *path = NULL;
    path = get_dev();

    ret = xwii_iface_new(&iface, path);
    free(path);

    ret = xwii_iface_open(iface, xwii_iface_available(iface) | XWII_IFACE_WRITABLE);
    struct xwii_event event;
    ret = 0;
    /**
    fds_num = 0;
    struct pollfd fds[2];

    memset(fds, 0, sizeof(fds));
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[1].fd = xwii_iface_get_id(iface)
    fds[1].events = POLLIN;
     **/
    ret = xwii_iface_watch(iface, true);
    if (ret) { std::cout << "Error: cannot initialize hotplug watch descriptor\n"; }
};

char *Wiimote::get_dev()
{
    struct xwii_monitor *mon;
    char *ent;
    int i = 0;

    mon = xwii_monitor_new(false, false);
    if (!mon)
    {
        std::cout << "Cannot create monitor\n";
        return NULL;
    }

    while ((ent = xwii_monitor_poll(mon)))
    {
        if (true) { break; }
        free(ent);
    }

    xwii_monitor_unref(mon);
    //free(mon);
    return ent;
};

void Wiimote::key_show(xwii_event *event)
{
    unsigned int code = event->v.key.code;
    bool pressed = event->v.key.state;
    char *str = NULL;

    switch (code)
    {
        case XWII_KEY_UP:
            switch (pressed)
            {
                case true:
                    allKeys.keys[0] = true;
                    break;

                case false:
                    allKeys.keys[0] = false;
                    break;
            }
            break;

        case XWII_KEY_DOWN:
            switch (pressed)
            {
                case true:
                    allKeys.keys[1] = true;
                    break;

                case false:
                    allKeys.keys[1] = false;
                    break;
            }
            break;

        case XWII_KEY_LEFT:
            switch (pressed)
            {
                case true:
                    allKeys.keys[2] = true;
                    break;

                case false:
                    allKeys.keys[2] = false;
                    break;
            }
            break;

        case XWII_KEY_RIGHT:
            switch (pressed)
            {
                case true:
                    allKeys.keys[3] = true;
                    break;

                case false:
                    allKeys.keys[3] = false;
                    break;
            }
            break;

        case XWII_KEY_A:
            switch (pressed)
            {
                case true:
                    allKeys.keys[4] = true;
                    break;

                case false:
                    allKeys.keys[4] = false;
                    break;
            }
            break;

        case XWII_KEY_B:
            switch (pressed)
            {
                case true:
                    allKeys.keys[5] = true;
                    break;

                case false:
                    allKeys.keys[5] = false;
                    break;
            }
            break;

        case XWII_KEY_ONE:
            switch (pressed)
            {
                case true:
                    allKeys.keys[6] = true;
                    break;

                case false:
                    allKeys.keys[6] = false;
                    break;
            }
            break;

        case XWII_KEY_TWO:
            switch (pressed)
            {
                case true:
                    allKeys.keys[7] = true;
                    break;

                case false:
                    allKeys.keys[7] = false;
                    break;
            }
            break;

    }
};

void Wiimote::Update()
{
    /**
    ret = poll(fds, fds_num, -1);
    if (ret < 0)
    {
        if (errno != EINTR)
        {
            ret = -eerno;
            std::cout << "Error: Cannot poll fds: " << ret << "\n";
        }
    }
    **/

    ret =  xwii_iface_dispatch(iface, &event, sizeof(event));
    if (ret)
    {
        if (ret != -EAGAIN)
        {
            std::cout << "Error: Read failed with err:" << ret << "\n";
        }
    } else if (!freeze) {
        switch (event.type)
        {
            case XWII_EVENT_GONE:
                std::cout << "Info: Device gone\n";
				/**
                fds[1].fd = -1;
				fds[1].events = 0;
				fds_num = 1;
				**/
                break;

			case XWII_EVENT_KEY:
                key_show(&event);
				break;
        }
    }

    allKeys.Update();
};
