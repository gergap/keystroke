#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "keygrabber.h"
#include "dialog.h"
#include "file.h"
#include "settings.h"

extern "C" int qtmain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int ret;
    Dialog dlg;
    Settings *s = Settings::instance();

    app.setApplicationName("KeyStroke");
    app.setOrganizationName("Gappy");

//    dlg.show();

    qmlRegisterType<KeyGrabber>("com.gappy.keygrabber", 1, 0, "KeyGrabber");
    qmlRegisterType<File>("com.gappy.keygrabber", 1, 0, "File");

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    // we make our mainwindow accessible from QML, so we can hide it
    viewer.rootContext()->setContextProperty("mainWindow", &viewer);
    viewer.rootContext()->setContextProperty("settings", s);
    viewer.setMainQmlFile(QLatin1String("qml/KeyStrokeOverlay.qml"));
    // transparent background
    viewer.setAttribute(Qt::WA_TranslucentBackground);
    viewer.setStyleSheet("background:transparent;");
    // no window decorations
    viewer.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    viewer.resize(s->dockWidth(), s->dockHeight());
    viewer.move(s->dockPosition());
    qDebug() << s->dockWidth();
    qDebug() << s->dockHeight();
    qDebug() << s->dockPosition();
//    viewer.show();

    ret = app.exec();

    return ret;
}

