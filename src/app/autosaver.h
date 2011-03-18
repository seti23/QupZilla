/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  nowrep
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef AUTOSAVER_H
#define AUTOSAVER_H

#ifdef QT_NO_DEBUG
#ifdef DEVELOPING
#error "TRYING TO RELEASE WITH DEVELOPING FLAG"
#endif
#endif

#include <QObject>
#include <QBasicTimer>
#include <QDebug>

class AutoSaver : public QObject
{
    Q_OBJECT
public:
    explicit AutoSaver(QObject* parent = 0);

signals:
    void saveApp();

public slots:

private:
    void timerEvent(QTimerEvent* event);
    QBasicTimer m_timer;

};

#endif // AUTOSAVER_H
