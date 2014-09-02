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
    m_dockOffset = s.value("dockOffset", QPoint(0, r.height() - m_dockHeight)).toPoint();
    m_bgcolor = s.value("backgroundColor", Qt::black).value<QColor>();
    m_bgopacity = s.value("backgroundOpacity", 0.4).toDouble();
    m_bBackspaceEnabled = s.value("backspaceEnabled", false).toBool();
    m_dockPos = (DockingPosition)s.value("dockPos", Bottom).toInt();
    m_offsetFromEdge = s.value("offsetFromEdge", 0).toInt();
}

Settings::~Settings()
{
    QSettings s;

    s.setValue("fontSize", m_fontSize);
    s.setValue("fadeoutTime", m_fadeoutTime);
    s.setValue("dockWidth", m_dockWidth);
    s.setValue("dockHeight", m_dockHeight);
    s.setValue("dockOffset", m_dockOffset);
    s.setValue("backgroundColor", m_bgcolor);
    s.setValue("backgroundOpacity", m_bgopacity);
    s.setValue("backspaceEnabled", m_bBackspaceEnabled);
    s.setValue("dockPos", m_dockPos);
    s.setValue("offsetFromEdge", m_offsetFromEdge);
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
        emit dockWidthChanged(val);
        computeDockPos();
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
        computeDockPos();
    }
}

QPoint Settings::dockOffset() const
{
    return m_dockOffset;
}

void Settings::setDockOffset(const QPoint &val)
{
    if (val != m_dockOffset) {
        m_dockOffset = val;
        emit dockOffsetChanged(val);
    }
}

Settings::DockingPosition Settings::dockPosition() const
{
    return m_dockPos;
}

void Settings::setDockPosition(const Settings::DockingPosition val)
{
    m_dockPos = val;
    computeDockPos();
}

Settings *Settings::instance()
{
    if (m_instance == 0)
        m_instance = new Settings(qApp);
    return m_instance;
}

QColor Settings::backgroundColor() const
{
    return m_bgcolor;
}

void Settings::setBackgroundColor(const QColor &col)
{
    if (col != m_bgcolor) {
        m_bgcolor = col;
        emit backgroundColorChanged(col);
    }
}

double Settings::backgroundOpacity() const
{
    return m_bgopacity;
}

void Settings::setBackgroundOpacity(double opacity)
{
    if (opacity != m_bgopacity) {
        m_bgopacity = opacity;
        emit backgroundOpacityChanged(opacity);
    }
}

bool Settings::backspaceEnabled() const
{
    return m_bBackspaceEnabled;
}

void Settings::setBackspaceEnabled(bool enabled)
{
    if (enabled != m_bBackspaceEnabled) {
        m_bBackspaceEnabled = enabled;
        emit backspaceEnabledChanged(enabled);
    }
}

int Settings::offsetFromEdge() const
{
    return m_offsetFromEdge;
}

void Settings::setOffsetFromEdge(int val)
{
    if (val != m_offsetFromEdge) {
        m_offsetFromEdge = val;
        computeDockPos();
        emit offsetFromEdgeChanged(val);
    }
}

void Settings::computeDockPos()
{
    QDesktopWidget desktop;
    int primary = desktop.primaryScreen();
    QRect r = desktop.screenGeometry(primary);

    switch (m_dockPos) {
    case Top:
        m_dockOffset = QPoint(0, m_offsetFromEdge);
        //m_dockWidth = r.width();
        //m_dockHeight = r.height() / 4;
        break;
    case Bottom:
        //m_dockWidth = r.width();
        //m_dockHeight = r.height() / 4;
        m_dockOffset = QPoint(0, r.height() - m_dockHeight - m_offsetFromEdge);
        break;
    case Left:
        m_dockOffset = QPoint(m_offsetFromEdge, 0);
        //m_dockWidth = r.width() / 4;
        //m_dockHeight = r.height();
        break;
    case Right:
        //m_dockWidth = r.width() / 4;
        //m_dockHeight = r.height();
        m_dockOffset = QPoint(r.width() - m_dockWidth - m_offsetFromEdge, 0);
        break;
    }
}
