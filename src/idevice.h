/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#ifndef IDEVICE_H
#define IDEVICE_H

#include <QObject>
#include <QMap>

extern "C" {
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
}

class IDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString deviceName READ deviceName NOTIFY deviceNameChanged)

public:
    explicit IDevice(const QString &uuid = QString(), QObject *parent = nullptr);

    Q_INVOKABLE QString value(const QString &key, const QString &fallback);

    QString uuid() const;
    QString deviceName() const;

signals:
    void deviceNameChanged();

private slots:
    void updateInfos();

private:
    QString uuid_;
    QString device_name_;

    QMap<QString, QString> datas_;
};

#endif // IDEVICE_H
