import QtQuick 1.1

Item {
    id: key
    width: 192
    height: 192
    property alias text: label.text

    /*
    Rectangle {
        id: debug
        color: "#ff0000"
        anchors.fill: parent
    }
    */

    Text {
        id: label
        anchors.fill: parent
        color: "#ffffff"
        text: "Key"
        smooth: true
        style: Text.Raised
        font.pointSize: 100
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: false

        onTextChanged: {
            key.width = 128;
            key.height = 128;
            if (text === "ENTER") {
                pic.source = "../png/enter.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "SPACE") {
                pic.source = "../png/space.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "META") {
                pic.source = "../png/tux_white.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "SHIFT") {
                pic.source = "../png/shift.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "LEFT") {
                pic.source = "../png/left.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "RIGHT") {
                pic.source = "../png/right.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "UP") {
                pic.source = "../png/up.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "DOWN") {
                pic.source = "../png/down.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "BACKSPACE") {
                pic.source = "../png/backspace.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else if (text === "TAB") {
                pic.source = "../png/tab.png";
                key.width = pic.sourceSize.width * key.width / 192;
                pic.visible = true;
                label.visible = false;
            } else {
                pic.visible = false;
                label.visible = true;
                key.width = 100 * text.length;
            }
        }
    }

    Image {
        id: pic
        fillMode: Image.PreserveAspectFit
        source: "../png/enter.png"
        anchors.fill: parent
        visible: false
        smooth: true
    }
}
