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

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int fontSize         READ fontSize     WRITE setFontSize     NOTIFY fontSizeChanged)
    Q_PROPERTY(int fadeoutTime      READ fadeoutTime  WRITE setFadeoutTime  NOTIFY fadeoutTimeChanged)
    Q_PROPERTY(int dockWidth        READ dockWidth    WRITE setDockWidth    NOTIFY dockWidthChanged)
    Q_PROPERTY(int dockHeight       READ dockHeight   WRITE setDockHeight   NOTIFY dockHeightChanged)
    Q_PROPERTY(QPoint dockPosition  READ dockPosition WRITE setDockPosition NOTIFY dockPositionChanged)
    Settings(QObject *parent = 0);
public:
    virtual ~Settings();

    int fontSize() const;
    void setFontSize(int val);
    int fadeoutTime() const;
    void setFadeoutTime(int val);
    int dockWidth() const;
    void setDockWidth(int val);
    int dockHeight() const;
    void setDockHeight(int val);
    QPoint dockPosition() const;
    void setDockPosition(const QPoint &val);

    static Settings *instance();

signals:
    void fontSizeChanged(int newVal);
    void fadeoutTimeChanged(int newVal);
    void dockWidthChanged(int newVal);
    void dockHeightChanged(int newVal);
    void dockPositionChanged(const QPoint &newVal);

private:
    int m_fontSize;
    int m_fadeoutTime;
    int m_dockWidth;
    int m_dockHeight;
    QPoint m_dockPos;
    static Settings *m_instance;
};

#endif /* end of include guard: SETTINGS_H */

