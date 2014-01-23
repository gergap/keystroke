import QtQuick 1.1

Item {
    id: key
    width: 192
    height: 192
    property alias text: label.text

    Text {
        id: label
        anchors.fill: parent
        /*width: 128
        height: 192*/
        color: "#ffffff"
        text: "Key"
        smooth: true
        style: Text.Raised
        font.pointSize: 128
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
                key.width = 128 * text.length;
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
