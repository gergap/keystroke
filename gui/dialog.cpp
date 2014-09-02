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
#include "aboutdialog.h"
#include <QtGui>

Dialog::Dialog() : QDialog()
{
    ui.setupUi(this);

    settings = Settings::instance();
    connect(ui.spinBoxFadeoutTime, SIGNAL(valueChanged(double)), this, SLOT(fadeoutTimeChanged(double)));
    connect(ui.sliderFadeoutTime, SIGNAL(valueChanged(int)), this, SLOT(fadeoutTimeChanged(int)));
    connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(ui.btnApply, SIGNAL(clicked()), this, SLOT(applyPressed()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));
    connect(ui.btnShortcut, SIGNAL(clicked()), this, SLOT(changeShortcut()));
    connect(ui.btnSelectColor, SIGNAL(clicked()), this, SLOT(selectColor()));
    connect(ui.lineEditColor, SIGNAL(textChanged(QString)), this, SLOT(backgroundColorChanged(QString)));
    connect(ui.cmbDockPos, SIGNAL(currentIndexChanged(int)), this, SLOT(dockPositionChanged(int)));

    loadSettings();

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
    qDebug() << "iconActivated";
    if (reason == QSystemTrayIcon::DoubleClick)
        show();
}

void Dialog::createActions()
{
    configureAction = new QAction(tr("&Configuration..."), this);
    connect(configureAction, SIGNAL(triggered()), this, SLOT(show()));

    aboutAction = new QAction(tr("&About..."), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Dialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(configureAction);
    trayIconMenu->addAction(aboutAction);
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

void Dialog::loadSettings()
{
    ui.spinBoxFadeoutTime->setValue(settings->fadeoutTime() / 1000.0);
    ui.spinBoxFontSize->setValue(settings->fontSize());
    ui.spinBoxDockSize->setValue(settings->dockHeight());
    ui.spinBoxDockOffset->setValue(settings->offsetFromEdge());
    setBackgroundColor(settings->backgroundColor());
    ui.spinOpacity->setValue(settings->backgroundOpacity() * 100);
}

void Dialog::saveSettings()
{
    settings->setFadeoutTime(ui.spinBoxFadeoutTime->value() * 1000);
    settings->setFontSize(ui.spinBoxFontSize->value());
    settings->setDockHeight(ui.spinBoxDockSize->value());
    settings->setOffsetFromEdge(ui.spinBoxDockOffset->value());
    switch (ui.cmbDockPos->currentIndex()) {
    case 0:
        settings->setDockPosition(Settings::Top);
        break;
    case 1:
        settings->setDockPosition(Settings::Bottom);
        break;
    case 2:
        settings->setDockPosition(Settings::Left);
        break;
    case 3:
        settings->setDockPosition(Settings::Right);
        break;
    default:
        settings->setDockPosition(Settings::Top);
        break;
    }
    settings->setBackgroundColor(parseColorString(ui.lineEditColor->text()));
    settings->setBackgroundOpacity(ui.spinOpacity->value() / 100.0);
}

QColor Dialog::parseColorString(const QString &col)
{
    QString red, green, blue;

    red = col.mid(1, 2);
    green = col.mid(3, 2);
    blue = col.mid(5, 2);
    return QColor::fromRgb(red.toInt(0, 16), green.toInt(0, 16), blue.toInt(0, 16));
}

void Dialog::setBackgroundColor(const QColor &col, ColorUpdateType update)
{
    QString sColor;
    QImage img(32, 32, QImage::Format_RGB32);

    img.fill(col);

    // convert color to hex string
    sColor = QString("#%1%2%3")
        .arg(col.red(), 2, 16, QLatin1Char('0'))
        .arg(col.green(), 2, 16, QLatin1Char('0'))
        .arg(col.blue(), 2, 16, QLatin1Char('0'));

    if (update == UpdateLineEdit)
        ui.lineEditColor->setText(sColor);
    ui.lblColorPreview->setPixmap(QPixmap::fromImage(img));
}

void Dialog::backgroundColorChanged(const QString &sColor)
{
    QColor col = parseColorString(sColor);
    setBackgroundColor(col, NoUpdateLineEdit);
}

void Dialog::fadeoutTimeChanged(int value)
{
    ui.spinBoxFadeoutTime->setValue(value / 1000.0);
}

void Dialog::fadeoutTimeChanged(double value)
{
    ui.sliderFadeoutTime->setValue(value * 1000);
}

void Dialog::changeShortcut()
{
    QMessageBox::information(this, tr("Change shortcut"), tr("Sorry, not yet implemented."));
}

void Dialog::selectColor()
{
    QColorDialog dlg;

    if (dlg.exec() == QDialog::Accepted) {
        QColor col = dlg.selectedColor();
        setBackgroundColor(col);
    }
}

void Dialog::showAbout()
{
    AboutDialog dlg;

    dlg.exec();
}

void Dialog::dockPositionChanged(int)
{

}

