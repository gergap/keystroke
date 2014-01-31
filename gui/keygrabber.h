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

#ifndef KEYGRABBER_H
#define KEYGRABBER_H

#include <QThread>

class KeyGrabber : public QThread
{
    Q_OBJECT
public:
    explicit KeyGrabber(QObject *parent = 0);

    virtual void run();
    void stop();

    bool enabled() const { return m_bEnabled; }
    void setEnabled(bool bEnabled) { m_bEnabled = bEnabled; }

signals:
    void keyPressed(const QString &key);
    void keyPressed_Internal(const QString &key);

private:
    bool m_bShutdown;
    bool m_bEnabled;
};

#endif /* end of include guard: KEYGRABBER_H */

