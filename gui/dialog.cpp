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

#include "dialog.h"
#include "settings.h"
#include <QtGui>

Dialog::Dialog() : QDialog()
{
    ui.setupUi(this);

    settings = Settings::instance();
    ui.spinBoxFadeoutTime->setValue(settings->fadeoutTime() / 1000.0);
    ui.spinBoxFontSize->setValue(settings->fontSize());
    ui.spinBoxDockSize->setValue(settings->dockHeight());
    connect(ui.spinBoxFadeoutTime, SIGNAL(valueChanged(double)), this, SLOT(fadeoutTimeChanged(double)));
    connect(ui.sliderFadeoutTime, SIGNAL(valueChanged(int)), this, SLOT(fadeoutTimeChanged(int)));

    connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(ui.btnApply, SIGNAL(clicked()), this, SLOT(applyPressed()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));

    if (QSystemTrayIcon::isSystemTrayAvailable())
        qDebug() << "Systemtray is available.";
    else
        qDebug() << "Systemtray is not available.";
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

void Dialog::applyPressed()
{
    saveSettings();
}

void Dialog::okPressed()
{
    saveSettings();
    hide();
}

void Dialog::cancelPressed()
{
    hide();
}

void Dialog::saveSettings()
{
    settings->setFadeoutTime(ui.spinBoxFadeoutTime->value() * 1000);
    settings->setFontSize(ui.spinBoxFontSize->value());
    settings->setDockHeight(ui.spinBoxDockSize->value());
}

void Dialog::fadeoutTimeChanged(int value)
{
    ui.spinBoxFadeoutTime->setValue(value / 1000.0);
}

void Dialog::fadeoutTimeChanged(double value)
{
    ui.sliderFadeoutTime->setValue(value * 1000);
}

