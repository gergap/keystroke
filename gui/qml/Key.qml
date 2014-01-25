import QtQuick 1.1
import com.gappy.keygrabber 1.0

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
        font.pointSize: 100
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: false

        onTextChanged: {
            key.width = 128;
            key.height = 128;
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
