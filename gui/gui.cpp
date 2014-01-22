#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "keygrabber.h"

extern "C" int qtmain(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<KeyGrabber>("com.gappy.keygrabber", 1, 0, "KeyGrabber");

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.rootContext()->setContextProperty("globalGrabber", &grabber);
    viewer.setMainQmlFile(QLatin1String("qml/KeyStrokeOverlay.qml"));
    // transparent background
    viewer.setAttribute(Qt::WA_TranslucentBackground);
    viewer.setStyleSheet("background:transparent;");
    // no window decorations
//    viewer.setWindowFlags(Qt::FramelessWindowHint);
    viewer.showExpanded();
    viewer.move(10, 10);


    return app.exec();
}

