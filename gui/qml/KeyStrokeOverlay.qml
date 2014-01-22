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
        opacity: 0.3
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
                width: 100
                height: 80
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
        }
    }

    Timer {
        id: timer
        interval: 1500; running: false; repeat: false
        onTriggered: {
            var i;
            for (i=0; i<repeater.count; i++) {
                repeater.itemAt(i).visible = false;
            }
            main.visible = false;
        }
    }
}
