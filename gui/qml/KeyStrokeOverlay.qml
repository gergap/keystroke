import QtQuick 1.1
import "keystroke.js" as Keystroke
import com.gappy.keygrabber 1.0

Item {
    id: main
    width: 800
    height: 130
    focus: true

    Component.onCompleted: {
        Keystroke.init();
        grabber.start();
    }

    Row {
        id: row
        spacing: 10
    }

    KeyGrabber {
        id: grabber;
        onKeyPressed: {
            console.log("key: "+key);
            Keystroke.showKey(key);
            timer.stop();
            timer.start();
        }
    }
/*    KeyGrabber.onKeyPressed: {
        console.log("key: "+key);
    }
*/
    Keys.onPressed: {
        var text = "";
        console.log("key: "+event.key+", mod: "+event.modifiers);
        if (event.key === Qt.Key_Shift) return;
        if (event.key === Qt.Key_Control) return;
        if (event.key === Qt.Key_Alt) return;
        if (event.key === Qt.Key_Meta) return;
        if (event.key === Qt.Key_AltGr) return;
        if (event.key === Qt.Key_Meta) return;

        if (event.modifiers & Qt.ShiftModifier) text += "Shift+";
        if (event.modifiers & Qt.ControlModifier) text += "Ctrl+";
        if (event.modifiers & Qt.AltModifier) text += "Alt+";
        if (event.modifiers & Qt.MetaModifier) text += "Meta+";
        if (event.modifiers & Qt.KeypadModifier) text += "Keypad+";
        if (event.modifiers & Qt.GroupSwitchModifier) text += "AltGr+";

        switch(event.key)
        {
        case Qt.Key_Escape: text += "Esc"; break;
        case Qt.Key_Return: text += "Return"; break;
        case Qt.Key_Enter: text += "Enter"; break;
        case Qt.Key_Backspace: text += "Backspace"; break;
        case Qt.Key_Delete: text += "Del"; break;
        case Qt.Key_Insert: text += "Ins"; break;
        case Qt.Key_Home: text += "Home"; break;
        case Qt.Key_End: text += "End"; break;
        case Qt.Key_PageUp: text += "PgUp"; break;
        case Qt.Key_PageDown: text += "PgDown"; break;
        case Qt.Key_Left: text = "\u2190"; break;
        case Qt.Key_Right: text = "\u2192"; break;
        case Qt.Key_Up: text = "\u2191"; break;
        case Qt.Key_Down: text = "\u2193"; break;
        default:
            if (event.key >= Qt.Key_F1 && event.key <= Qt.Key_F12) {
                text += "F" + (event.key - Qt.Key_F1 + 1);
            } else {
                text += String.fromCharCode(event.key);
            }
            break;
        }

        Keystroke.showKey(text);
        timer.stop();
        timer.start();
    }

    Timer {
        id: timer
        interval: 1500; running: false; repeat: false
        onTriggered: {
            Keystroke.hide();
        }
    }
}

