import QtQuick 1.1

Rectangle {
    id: key
    width: 128
    height: 128
    color: "#c8000000"
    radius: 10
    property alias text: label.text
    visible: false

    Text {
        id: label
        color: "#ffffff"
        text: qsTr("\u2190")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: true
        font.family: "DejaVu Sans Mono"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: false
        font.pointSize: 25

        onTextChanged: {
            font.pointSize = 25;
            if (width > key.width) {
                font.pointSize = 20;
            }
            if (width > key.width) {
                font.pointSize = 15;
            }
        }
    }
}
