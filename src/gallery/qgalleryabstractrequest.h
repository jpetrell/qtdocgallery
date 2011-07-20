/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDocGallery module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGALLERYABSTRACTREQUEST_H
#define QGALLERYABSTRACTREQUEST_H

#include "qgallery_p.h"

#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QAbstractGallery;
class QGalleryAbstractResponse;
class QGalleryAbstractRequestPrivate;

class Q_GALLERY_EXPORT QGalleryAbstractRequest : public QObject
{
    Q_OBJECT

    Q_ENUMS(State)
    Q_ENUMS(RequestType)

    Q_PROPERTY(QAbstractGallery* gallery READ gallery WRITE setGallery NOTIFY galleryChanged)
    Q_PROPERTY(bool supported READ isSupported NOTIFY supportedChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorChanged)
    Q_PROPERTY(int currentProgress READ currentProgress NOTIFY progressChanged)
    Q_PROPERTY(int maximumProgress READ maximumProgress NOTIFY progressChanged)

public:
    enum State {
        Inactive,
        Active,
        Canceling,
        Canceled,
        Idle,
        Finished,
        Error
    };

    enum RequestError {
        NoError,
        NoGallery,
        NotSupported,
        GalleryError = 100
    };

    enum RequestType {
        QueryRequest,
        ItemRequest,
        TypeRequest
    };

    explicit QGalleryAbstractRequest(RequestType type, QObject *parent = 0);
    explicit QGalleryAbstractRequest( QAbstractGallery *gallery, RequestType type, QObject *parent = 0);
    ~QGalleryAbstractRequest();

    QAbstractGallery *gallery() const;
    void setGallery(QAbstractGallery *gallery);

    bool isSupported() const;

    RequestType type() const;
    State state() const;

    int error() const;
    QString errorString() const;

    int currentProgress() const;
    int maximumProgress() const;

    bool waitForFinished(int msecs);

public Q_SLOTS:
    void execute();
    void cancel();
    void clear();

Q_SIGNALS:
    void galleryChanged();
    void supportedChanged();
    void finished();
    void canceled();
    void error(int error, const QString &errorString);
    void stateChanged(QGalleryAbstractRequest::State state);
    void errorChanged();
    void progressChanged(int current, int maximum);

protected:
    virtual void setResponse(QGalleryAbstractResponse *response) = 0;

    explicit QGalleryAbstractRequest(QGalleryAbstractRequestPrivate &dd, QObject *parent);

    QScopedPointer<QGalleryAbstractRequestPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QGalleryAbstractRequest)
    Q_PRIVATE_SLOT(d_func(), void _q_finished())
    Q_PRIVATE_SLOT(d_func(), void _q_canceled())
    Q_PRIVATE_SLOT(d_func(), void _q_resumed())
    Q_PRIVATE_SLOT(d_func(), void _q_progressChanged(int, int))
};

QT_END_NAMESPACE
QT_END_HEADER

#endif
