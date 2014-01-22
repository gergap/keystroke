#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

volatile int stop = 0;

#define KEY_RELEASED 0
#define KEY_PRESSED  1
#define KEY_REPEATED 2

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
    struct input_event ev;
    char device[] = "/dev/input/event4";
    int fd;
    int ret;
    int shift = 0;
    int altgr = 0;
    const char *symbol;

    loadmap("de.map");
    //printmap();

    fd = open(device, O_RDONLY);
    if (fd < 0) die("Cannot open device '%s'\n", device);
    while (!stop) {
        ret = read(fd, &ev, sizeof(ev));
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
    close(fd);

    return 0;
}

