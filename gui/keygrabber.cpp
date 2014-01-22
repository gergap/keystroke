#include "keygrabber.h"
#include "../keymap.h"
#include <linux/input.h>
#include <unistd.h>
#include <errno.h>
#include <QtDebug>

extern int keyboard_fd;

KeyGrabber::KeyGrabber(QObject *parent) :
    QThread(parent)
{
    m_bShutdown = false;

    // marshal internal signal from worker thread to main thread using a queued connection
    connect(this, SIGNAL(keyPressed_Internal(QString)), this, SIGNAL(keyPressed(QString)), Qt::QueuedConnection);
}

void KeyGrabber::run()
{
    struct input_event ev;
    int ret;
    int shift = 0;
    int altgr = 0;
    const char *symbol = 0;

    while(!m_bShutdown) {
        ret = read(keyboard_fd, &ev, sizeof(ev));
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret < sizeof(ev)) {
            qDebug() << "read returned invalid size\n";
            break;
        }

        if (ev.type == EV_SYN) {
            /* sync event, we can reset our state machine */
            continue;
        }
        if (ev.type == EV_KEY) {
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

        if (symbol) {
            QString key = symbol;
            emit keyPressed_Internal(key);
            symbol = 0;
        }
    }
}

void KeyGrabber::stop()
{
    m_bShutdown = true;
}

