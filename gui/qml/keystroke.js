var numKeys = 6;
var keys = new Array(numKeys);
var component = null;

function init() {
    for(var i=0; i<numKeys; i++) {
        createKey(i);
    }
}

function createKey(index) {
    if (component === null)
        component = Qt.createComponent("Key.qml");

    // Note that if Block.qml was not a local file, component.status would be
    // Loading and we should wait for the component's statusChanged() signal to
    // know when the file is downloaded and ready before calling createObject().
    if (component.status === Component.Ready) {
        var dynamicObject = component.createObject(main);
        if (dynamicObject === null) {
            console.log("error creating block");
            console.log(component.errorString());
            return false;
        }
        dynamicObject.x = index * (dynamicObject.width + 10);
        dynamicObject.y = 0;
        keys[index] = dynamicObject;
    } else {
        console.log("error loading key component");
        console.log(component.errorString());
        return false;
    }
    return true;
}

function showKey(text) {
    for(var i=0; i<numKeys; i++) {
        if (keys[i].visible === false) {
            keys[i].text = text;
            keys[i].visible = true;
            break;
        }
    }
}

function hide() {
    for(var i=0; i<numKeys; i++) {
        keys[i].visible = false;
    }
}
