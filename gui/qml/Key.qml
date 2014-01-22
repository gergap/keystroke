import QtQuick 1.1

Text {
    id: label
    width: 128
    height: 192
    color: "#ffffff"
    text: "Key"
    smooth: true
    style: Text.Raised
    font.pointSize: 128
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    visible: false

    onVisibleChanged: {
        width = 90 * text.length;
    }
}
