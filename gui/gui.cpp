/* This file is part of Keystroke. A keystroke visualization tool.
 * Copyright (C) 2014 Gerhard Gappmeier <gappy1502@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "keygrabber.h"
#include "dialog.h"
#include "file.h"
#include "settings.h"
#include "mytcpserver.h"

extern "C" int qtmain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int ret;

    app.setQuitOnLastWindowClosed(false);
    app.setApplicationName("KeyStroke");
    app.setOrganizationName("Gappy");

    Dialog dlg;
    Settings *s = Settings::instance();
//    dlg.show();

    qmlRegisterType<KeyGrabber>("com.gappy.keygrabber", 1, 0, "KeyGrabber");
    qmlRegisterType<File>("com.gappy.keygrabber", 1, 0, "File");
    qmlRegisterType<MyTcpServer>("com.gappy.mytcpserver", 1, 0, "MyTcpServer");

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
    viewer.move(s->dockOffset());
/*    switch (s->dockPosition()) {
    case Settings::Top:
        break;
    case Settings::Bottom:
        break;
    case Settings::Left:
        break;
    case Settings::Right:
        break;
    }*/

    qDebug() << s->dockWidth();
    qDebug() << s->dockHeight();
    qDebug() << s->dockOffset();
    viewer.show();

    QObject::connect(s, SIGNAL(dockWidthChanged(int)), &viewer, SLOT(dockWidthChanged(int)));
    QObject::connect(s, SIGNAL(dockHeightChanged(int)), &viewer, SLOT(dockHeightChanged(int)));
    QObject::connect(s, SIGNAL(dockOffsetChanged(const QPoint&)), &viewer, SLOT(dockOffsetChanged(const QPoint&)));

    ret = app.exec();

    delete s;

    return ret;
}

