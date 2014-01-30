/* This file is part of Keystroke. A keystroke visualization tool.
 * Copyright (C) 2014 Gerhard Gappmeier <gappy1502@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <linux/input.h>
#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#ifdef GUI
# include "gui/gui.h"
#endif

volatile int stop = 0;
int keyboard_fd = 0;

/* uncomment the following file to enable same developer test code */
/*#define TEST*/
/* the default keyboard device file. This is a symlink to one of the
 * /dev/input/eventX files.
 */
#define KBD_DEVICE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

#include "keymap.h"

void die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(1);
}

/* event codes are described in /usr/src/linux/Documentation/input/event-codes.txt */
int main(int argc, char const *argv[])
{
    char device[PATH_MAX] = KBD_DEVICE;
    int ret;
#ifndef GUI
    struct input_event ev;
    int shift = 0;
    int altgr = 0;
    const char *symbol;
#endif

    if (getuid() == 0) {
        printf("WARNING: running as root!\nIt's recommended to start this application "
               "as normal user, owned be root with setuid bit set (rwsr-xr-x).\n");
    }

#ifdef TEST
    /* I don't want to allow overriding the device path in release mode,
     * because we are still running as root at this point and bad things might
     * happen, if users can start this app with root privileges (setuid bit)
     * and can open abitrary file as device.
     * So currently I use this option only to test things as non-root, which is
     * not allowed to open the keyboard device file.
     */
    if (argc > 1) {
        int len = strlen(argv[1]);
        if (len > sizeof(device) - 1) {
            die("The given path was too long. Paths a are limited to PATH_MAX=%i bytes.\n", PATH_MAX);
        }
        /* we know already the length, so we use memcpy instead of strncpy which has various problems */
        memcpy(device, argv[1], len);
        device[len] = 0;
    }
#endif

    /* the 1st thing we do is opening the keyboard device,
     * note that you will need root privileges for that */
    keyboard_fd = open(device, O_RDONLY);
    if (keyboard_fd < 0) die("Cannot open device '%s'\n", device);

    /* the next thing is to drop root privileges if we were
     * started with setuid bit
     */
    if (geteuid() == 0 && getuid() != 0) {
        ret = seteuid(getuid());
        if (ret != 0) die("seteuid failed.\n");
        printf("Root privileges have been dropped. Running as normal user now.\n");
    }

    loadmap("de.map");
    //printmap();

#ifdef GUI
    qtmain(argc, argv);
#else
    while (!stop) {
        ret = read(keyboard_fd, &ev, sizeof(ev));
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret < sizeof(ev)) {
            printf("read returned invalid size\n");
            break;
        }
        /*printf("event time=%i, type=%i, code=%i, value=%i\n",
            ev.time.tv_sec, ev.type, ev.code, ev.value);
        */
        if (ev.type == EV_SYN) {
            /* sync event, we can reset our state machine */
            continue;
        }
        if (ev.type == EV_KEY) {
            //printf("event time=%i, type=%i, code=%i, value=%i\n", ev.time.tv_sec, ev.type, ev.code, ev.value);
            switch (ev.value) {
            case KEY_RELEASED:
                switch (ev.code) {
                case KEY_LEFTSHIFT:
                    shift &= (~1);
                    break;
                case KEY_RIGHTSHIFT:
                    shift &= (~2);
                    break;
                case KEY_RIGHTALT:
                    altgr = 0;
                    break;
                default:
                    break;
                }
                break;
            case KEY_PRESSED:
                switch (ev.code) {
                case KEY_LEFTSHIFT:
                    shift |= 1;
                case KEY_RIGHTSHIFT:
                    shift |= 2;
                    break;
                case KEY_RIGHTALT:
                    altgr = 1;
                    break;
                default:
                    symbol = key_lookup(ev.code, shift, altgr);
                    printf("pressed %s (%i), shift=%i, altgr=%i\n", symbol, ev.code, shift, altgr);
                    break;
                }
                break;
            case KEY_REPEATED:
                break;
            }
        }
    }
#endif
    close(keyboard_fd);

    return 0;
}

