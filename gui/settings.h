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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QPoint>
#include <QColor>

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(DockingPosition)
    Q_PROPERTY(int fontSize         READ fontSize     WRITE setFontSize     NOTIFY fontSizeChanged)
    Q_PROPERTY(int fadeoutTime      READ fadeoutTime  WRITE setFadeoutTime  NOTIFY fadeoutTimeChanged)
    Q_PROPERTY(int dockWidth        READ dockWidth    WRITE setDockWidth    NOTIFY dockWidthChanged)
    Q_PROPERTY(int dockHeight       READ dockHeight   WRITE setDockHeight   NOTIFY dockHeightChanged)
    Q_PROPERTY(int offsetFromEdge          READ offsetFromEdge   WRITE setOffsetFromEdge   NOTIFY offsetFromEdgeChanged)
    Q_PROPERTY(QPoint dockOffset    READ dockOffset   WRITE setDockOffset   NOTIFY dockOffsetChanged)
    Q_PROPERTY(QColor backgroundColor  READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(double backgroundOpacity  READ backgroundOpacity WRITE setBackgroundOpacity NOTIFY backgroundOpacityChanged)
    Q_PROPERTY(bool backspaceEnabled  READ backspaceEnabled WRITE setBackspaceEnabled NOTIFY backspaceEnabledChanged)
    Q_PROPERTY(DockingPosition dockPosition  READ dockPosition WRITE setDockPosition NOTIFY dockPositionChanged)
    Settings(QObject *parent = 0);

public:
    enum DockingPosition {
        Top,
        Bottom,
        Left,
        Right
    };

    virtual ~Settings();

    int fontSize() const;
    void setFontSize(int val);
    int fadeoutTime() const;
    void setFadeoutTime(int val);
    int dockWidth() const;
    void setDockWidth(int val);
    int dockHeight() const;
    void setDockHeight(int val);
    QPoint dockOffset() const;
    void setDockOffset(const QPoint &val);
    DockingPosition dockPosition() const;
    void setDockPosition(const DockingPosition val);
    int offsetFromEdge() const;
    void setOffsetFromEdge(int val);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &col);
    double backgroundOpacity() const;
    void setBackgroundOpacity(double opacity);
    bool backspaceEnabled() const;
    void setBackspaceEnabled(bool enabled);

    static Settings *instance();

signals:
    void fontSizeChanged(int newVal);
    void fadeoutTimeChanged(int newVal);
    void dockWidthChanged(int newVal);
    void dockHeightChanged(int newVal);
    void dockOffsetChanged(const QPoint &newVal);
    void dockPositionChanged(DockingPosition newVal);
    void backgroundColorChanged(const QColor &col);
    void backgroundOpacityChanged(double opacity);
    void backspaceEnabledChanged(bool enabled);
    void offsetFromEdgeChanged(int newVal);

private:
    void computeDockPos();

private:
    int m_fontSize;
    int m_fadeoutTime;
    int m_dockWidth;
    int m_dockHeight;
    int m_offsetFromEdge;
    QPoint m_dockOffset;
    QColor m_bgcolor;
    double m_bgopacity;
    bool   m_bBackspaceEnabled;
    DockingPosition m_dockPos;
    static Settings *m_instance;
};

#endif /* end of include guard: SETTINGS_H */

