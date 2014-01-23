#include <QApplication>
#include <QtDeclarative>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include "qmlapplicationviewer.h"
#include "keygrabber.h"
#include "dialog.h"

extern "C" int qtmain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopWidget desktop;
    int primary = desktop.primaryScreen();
    QRect r = desktop.screenGeometry(primary);
    int width = r.width();
    int height = r.height() / 3;
    int ret;
    Dialog dlg;

    dlg.show();

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
    viewer.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    viewer.resize(width, height);
    viewer.move(0, r.height() - height);
    viewer.show();

    ret = app.exec();

    return ret;
}

