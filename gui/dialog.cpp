#include "dialog.h"
#include <QtGui>

Dialog::Dialog() : QDialog()
{
    ui.setupUi(this);

    if (QSystemTrayIcon::isSystemTrayAvailable())
        qDebug() << "Systemtray is available.";
    else
        qDebug() << "Systemtray is available.";
    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}

void Dialog::closeEvent(QCloseEvent *e)
{
    qDebug() << "closeEvent";
    if (trayIcon->isVisible()) {
        qDebug() << "tray icon is visible";
        /* keep running in tray */
        hide();
        e->ignore();
    }
}

void Dialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
}

void Dialog::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Dialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    qDebug() << "create tray icon";
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/png/icon.png"));
}

