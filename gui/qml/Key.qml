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
            if (text === "ENTER") {
                pic.source = "../png/enter.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "SPACE") {
                pic.source = "../png/space.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "META") {
                pic.source = "../png/tux_white.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "SHIFT") {
                pic.source = "../png/shift.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "LEFT") {
                pic.source = "../png/left.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "RIGHT") {
                pic.source = "../png/right.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "UP") {
                pic.source = "../png/up.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
            } else if (text === "DOWN") {
                pic.source = "../png/down.png";
                pic.visible = true;
                label.visible = false;
                key.width = 128;
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
