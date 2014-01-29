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

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include "ui_dialog.h"

class Settings;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void applyPressed();
    void okPressed();
    void cancelPressed();
    void fadeoutTimeChanged(int value);
    void fadeoutTimeChanged(double value);

private:
    void createActions();
    void createTrayIcon();
    void saveSettings();

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    Settings *settings;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    Ui_Dialog ui;
};

#endif /* end of include guard: DIALOG_H */

