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

#include "settings.h"
#include <QSettings>
#include <QDesktopWidget>
#include <QCoreApplication>

Settings *Settings::m_instance = 0;

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    QSettings s;
    QDesktopWidget desktop;
    int primary = desktop.primaryScreen();
    QRect r = desktop.screenGeometry(primary);
    int defaultDockWidth = r.width();
    int defaultDockHeight = r.height() / 4;

    m_fontSize = s.value("fontSize", 100).toInt();
    m_fadeoutTime = s.value("fadeoutTime", 2500).toInt();
    m_dockWidth = s.value("dockWidth", defaultDockWidth).toInt();
    m_dockHeight = s.value("dockHeight", defaultDockHeight).toInt();
    m_dockPos = s.value("dockPos", QPoint(0, r.height() - m_dockHeight)).toPoint();
}

Settings::~Settings()
{
    QSettings s;

    s.setValue("fontSize", m_fontSize);
    s.setValue("fadeoutTime", m_fadeoutTime);
    s.setValue("dockWidth", m_dockWidth);
    s.setValue("dockHeight", m_dockHeight);
    s.setValue("dockPos", m_dockPos);
}

int Settings::fontSize() const
{
    return m_fontSize;
}

void Settings::setFontSize(int val)
{
    if (val != m_fontSize) {
        m_fontSize = val;
        emit fontSizeChanged(val);
    }
}

int Settings::fadeoutTime() const
{
    return m_fadeoutTime;
}

void Settings::setFadeoutTime(int val)
{
    if (val != m_fadeoutTime) {
        m_fadeoutTime = val;
        emit fadeoutTimeChanged(val);
    }
}

int Settings::dockWidth() const
{
    return m_dockWidth;
}

void Settings::setDockWidth(int val)
{
    if (val != m_dockWidth) {
        m_dockWidth = val;
        emit dockHeightChanged(val);
    }
}

int Settings::dockHeight() const
{
    return m_dockHeight;
}

void Settings::setDockHeight(int val)
{
    if (val != m_dockHeight) {
        m_dockHeight = val;
        emit dockHeightChanged(val);

        QDesktopWidget desktop;
        int primary = desktop.primaryScreen();
        QRect r = desktop.screenGeometry(primary);
        QPoint pos(0, r.height() - m_dockHeight);
        setDockPosition(pos);
    }
}

QPoint Settings::dockPosition() const
{
    return m_dockPos;
}

void Settings::setDockPosition(const QPoint &val)
{
    if (val != m_dockPos) {
        m_dockPos = val;
        emit dockPositionChanged(val);
    }
}

Settings *Settings::instance()
{
    if (m_instance == 0)
        m_instance = new Settings(qApp);
    return m_instance;
}

