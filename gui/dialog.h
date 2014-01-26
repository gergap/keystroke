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

