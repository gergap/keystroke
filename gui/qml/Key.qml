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
    id: key
    width: 96
    height: 96
    property alias text: label.text

    /*
    Rectangle {
        id: debug
        color: "#ff0000"
        anchors.fill: parent
    }
    */

    File {
        id: file
    }

    Text {
        id: label
        anchors.fill: parent
        color: "#ffffff"
        text: "Key"
        smooth: true
        style: Text.Raised
        font.pointSize: settings.fontSize
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: false

        onTextChanged: {
            key.width = 96;
            key.height = 96;
            var filename = "qrc:/png/" + text.toLowerCase() + ".png";
            var b = file.exists(filename);
            //console.log(filename + ": " + b);

            if (b) {
                pic.source = filename;
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else {
                pic.visible = false;
                label.visible = true;
                key.width = 50 * text.length;
            }
        }
    }

    Image {
        id: pic
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        visible: false
        smooth: true
    }
}
