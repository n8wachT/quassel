/***************************************************************************
 *   Copyright (C) 2005-2013 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef TRANSFER_H
#define TRANSFER_H

#include <QHostAddress>
#include <QUuid>

#include "syncableobject.h"

class Transfer : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    Q_PROPERTY(QUuid uuid READ uuid);
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged);
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged);
    Q_PROPERTY(QHostAddress address READ address WRITE setAddress NOTIFY addressChanged);
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged);
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged);
    Q_PROPERTY(quint64 fileSize READ fileSize WRITE setFileSize NOTIFY fileSizeChanged);

public:
    enum State {
        New,
        Pending,
        Transferring,
        Paused,
        Completed,
        Failed,
        Rejected
    };
    Q_ENUMS(State)

    enum Direction {
        Send,
        Receive
    };
    Q_ENUMS(Direction)

    Transfer(const QUuid &uuid, QObject *parent = 0); // for creating a syncable object client-side
    Transfer(Direction direction, const QString &fileName, const QHostAddress &address, quint16 port, quint64 size = 0, QObject *parent = 0);

    QUuid uuid() const;
    State state() const;
    Direction direction() const;
    QString fileName() const;
    QHostAddress address() const;
    quint16 port() const;
    quint64 fileSize() const;

signals:
    void stateChanged(State state);
    void directionChanged(Direction direction);
    void addressChanged(const QHostAddress &address);
    void portChanged(quint16 port);
    void fileNameChanged(const QString &fileName);
    void fileSizeChanged(quint64 fileSize);

protected:
    void setState(State state);

private:
    void setDirection(Direction direction);
    void setAddress(const QHostAddress &address);
    void setPort(quint16 port);
    void setFileName(const QString &fileName);
    void setFileSize(quint64 fileSize);


    State _state;
    Direction _direction;
    QString _fileName;
    QHostAddress _address;
    quint16 _port;
    quint64 _fileSize;
    QUuid _uuid;
};

#endif