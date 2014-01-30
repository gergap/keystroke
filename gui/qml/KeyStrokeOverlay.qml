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

import QtQuick 1.1
import com.gappy.keygrabber 1.0

Item {
    id: main
    width: 800
    height: 600
    visible: false;

    Component.onCompleted: {
        grabber.start();
    }

    Rectangle {
        color: "#000000"
        opacity: 0.4
        anchors.fill: parent
    }

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 10
        Repeater {
            id: repeater
            model: 30
            Key {
                text: "Key"
                visible: false
            }
        }
    }

    KeyGrabber {
        id: grabber;
        onKeyPressed: {
            var i;
            console.log("key: "+key);

            for (i=0; i<repeater.count; i++) {
                if (repeater.itemAt(i).visible === false) {
                    repeater.itemAt(i).text = key;
                    repeater.itemAt(i).visible = true;
                    break;
                }
            }

            timer.stop();
            timer.start();
            main.visible = true;
            mainWindow.show();
        }
    }

    Timer {
        id: timer
        interval: settings.fadeoutTime; running: false; repeat: false
        onTriggered: {
            var i;
            for (i=0; i<repeater.count; i++) {
                repeater.itemAt(i).visible = false;
            }
            main.visible = false;
            mainWindow.hide();
        }
    }
}
