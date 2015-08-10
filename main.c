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
#define _GNU_SOURCE
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
#include <getopt.h>
#ifdef GUI
# include "gui/gui.h"
#endif
#include <config.h>

volatile int stop = 0;
int keyboard_fd = 0;

/* the default keyboard device file. This is a symlink to one of the
 * /dev/input/eventX files.
 */
#define KBD_DEVICE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

#include "keymap.h"

void die(const char *fmt, ...)
{
    va_list ap;
    int error = errno;
    const char *errmsg = strerror(error);

    if (error != 0)
        fprintf(stderr, "Error: %s (%i)\n", errmsg, error);

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(1);
}

void versioninfo()
{
    printf("%s %s\n%s\n", PROGRAM_NAME, VERSION, COPYRIGHT);
    printf("License: %s\n", LICENSE);
}

void usage(const char *app)
{
    versioninfo();
    fprintf(stderr, "Usage: %s [-h] [-v] [-d <device>] [-l <layout>]\n", app);
    fprintf(stderr, "-h : show this help\n");
    fprintf(stderr, "-v : show version info\n");
    fprintf(stderr, "-d : configure keyboard device. E.g. "
        "/dev/input/by-path/pci-0000:00:1d.0-usb-0:1.3:1.2-event-kbd\n");
    fprintf(stderr, "-l : configure keyboard layout. E.g. \"de\", or \"us\"\n");
    exit(1);
}

/* event codes are described in /usr/src/linux/Documentation/input/event-codes.txt */
int main(int argc, char *argv[])
{
    char device[PATH_MAX] = KBD_DEVICE;
    char layout[PATH_MAX] = PREFIX_ETC "de.map";
    char ext[] = ".map";
    char *tmp;
    int ret;
    size_t len;
    int optarglen;
    int opt;
#ifndef GUI
    struct input_event ev;
    int shift = 0;
    int altgr = 0;
    int ctrl = 0;
    const char *symbol;
#endif

    if (getuid() == 0) {
        printf("WARNING: running as root!\nIt's recommended to start this application "
               "as normal user, owned be root with setuid bit set (rwsr-xr-x).\n");
    }

    while ((opt = getopt(argc, argv, "vhl:d:")) != -1) {
        switch (opt) {
        case 'v':
            versioninfo();
            exit(EXIT_SUCCESS);
            break;
        case 'l':
            /* verfiy string length before doing anything */
            optarglen = strlen(optarg);
            len = strlen(PREFIX_ETC); /* this strlen is computed at compile time */
            len += optarglen;
            len += 4;                 /* for ".map" */
            if (len > sizeof(layout) - 1) {
                die("The given layout name was too long. Paths are limited to PATH_MAX=%i bytes.\n", PATH_MAX);
            }
            /* concatenate using simple mempcpy */
            tmp = mempcpy(layout, PREFIX_ETC, strlen(PREFIX_ETC));
            tmp = mempcpy(tmp, optarg, optarglen);
            tmp = mempcpy(tmp, ext, strlen(ext));
            *tmp = 0;
            break;
        case 'd':
            len = strlen(optarg);
            if (len > sizeof(device) - 1) {
                die("The given path was too long. Paths are limited to PATH_MAX=%i bytes.\n", PATH_MAX);
            }
            /* we know already the length, so we use memcpy instead of strncpy which has various problems */
            memcpy(device, optarg, len);
            device[len] = 0;
            break;
        default: /* '?' */
            usage(argv[0]);
        }
    }

    /* the 1st thing we do is opening the keyboard device,
     * note that you will need root privileges for that */
#if 1
    keyboard_fd = open(device, O_RDONLY);
    if (keyboard_fd < 0) die("Cannot open device '%s'\n", device);
#else
    keyboard_fd = 0;
#endif

    /* the next thing is to drop root privileges if we were
     * started with setuid bit
     */
    if (geteuid() == 0 && getuid() != 0) {
        ret = seteuid(getuid());
        if (ret != 0) die("seteuid failed.\n");
        printf("Root privileges have been dropped. Running as normal user now.\n");
    }

    if (loadmap(layout) != 0) {
        die("loading keymap '%s' failed.\n", layout);
    }
    //printmap();

#ifdef GUI
    qtmain(argc, argv);
#else
    while (!stop) {
        ret = read(keyboard_fd, &ev, sizeof(ev));
        if (ret == -1 && errno == EINTR)
            continue;
        if ((size_t)ret < sizeof(ev)) {
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
                case KEY_LEFTCTRL:
                    ctrl &= (~1);
                    break;
                case KEY_RIGHTCTRL:
                    ctrl &= (~2);
                    break;
                default:
                    break;
                }
                break;
            case KEY_PRESSED:
                switch (ev.code) {
                case KEY_LEFTSHIFT:
                    shift |= 1;
                    break;
                case KEY_RIGHTSHIFT:
                    shift |= 2;
                    break;
                case KEY_RIGHTALT:
                    altgr = 1;
                    break;
                case KEY_LEFTCTRL:
                    ctrl |= 1;
                    break;
                case KEY_RIGHTCTRL:
                    ctrl |= 2;
                    break;
                default:
                    symbol = key_lookup(ev.code, shift, altgr, ctrl);
                    printf("pressed %s (%i), shift=%i, altgr=%i, ctrl=%i\n", symbol, ev.code, shift, altgr, ctrl);
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

