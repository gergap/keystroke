#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include "ui_dialog.h"

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void createActions();
    void createTrayIcon();

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    Ui_Dialog ui;
};

#endif /* end of include guard: DIALOG_H */

