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
    m_bEnabled = true;
    m_bInsertMode = false;

    // marshal internal signal from worker thread to main thread using a queued connection
    connect(this, SIGNAL(keyPressed_Internal(QString)), this, SIGNAL(keyPressed(QString)), Qt::QueuedConnection);
}

void KeyGrabber::run()
{
    struct input_event ev;
    int ret;
    int shift = 0;
    int altgr = 0;
    int meta = 0;
    int ctrl = 0;
    const char *symbol = 0;

    while (!m_bShutdown) {
        ret = read(keyboard_fd, &ev, sizeof(ev));
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret != sizeof(ev)) {
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
                case KEY_LEFTCTRL:
                    ctrl &= (~1);
                    break;
                case KEY_RIGHTCTRL:
                    ctrl &= (~2);
                    break;
                case KEY_LEFTMETA:
                    meta &= (~1);
                    break;
                case KEY_RIGHTMETA:
                    meta &= (~2);
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
                    break;
                case KEY_RIGHTSHIFT:
                    shift |= 2;
                    break;
                case KEY_LEFTCTRL:
                    ctrl |= 1;
                    break;
                case KEY_RIGHTCTRL:
                    ctrl |= 2;
                    break;
                case KEY_RIGHTALT:
                    altgr = 1;
                    break;
                case KEY_LEFTMETA:
                    meta |= 1;
                    break;
                case KEY_RIGHTMETA:
                    meta |= 2;
                    break;
                case KEY_F10:
                    if (meta)
                        m_bEnabled = !m_bEnabled;
                    break;
                default:
                    break;
                }
                symbol = key_lookup(ev.code, shift, altgr, ctrl);
                printf("pressed %s (%i), shift=%i, altgr=%i, ctrl=%i\n", symbol, ev.code, shift, altgr, ctrl);
                break;
            case KEY_REPEATED:
                break;
            }
        }

        if (symbol) {
            bool control_key = ctrl | altgr | meta;
            if (m_bEnabled) {
                if (!m_bInsertMode || control_key) { /* only show control keys in insertmode */
                    QString key = QString::fromUtf8(symbol);
                    qDebug() << "QString key:" << key;
                    emit keyPressed_Internal(key);
                }
            }
            symbol = 0;
        }
    }
}

void KeyGrabber::stop()
{
    m_bShutdown = true;
}

