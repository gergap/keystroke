#include <QApplication>
#include <QtDeclarative>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include "qmlapplicationviewer.h"
#include "keygrabber.h"
#include "dialog.h"
#include "file.h"

extern "C" int qtmain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopWidget desktop;
    int primary = desktop.primaryScreen();
    QRect r = desktop.screenGeometry(primary);
    int width = r.width();
    int height = r.height() / 4;
    int ret;
    Dialog dlg;

    dlg.show();

    qmlRegisterType<KeyGrabber>("com.gappy.keygrabber", 1, 0, "KeyGrabber");
    qmlRegisterType<File>("com.gappy.keygrabber", 1, 0, "File");

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    // we make our mainwindow accessible from QML, so we can hide it
    viewer.rootContext()->setContextProperty("mainWindow", &viewer);
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

