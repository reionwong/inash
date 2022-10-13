/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include "ieventmonitor.h"
#include "devicemodel.h"
#include "idevice.h"

extern "C" {
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
}

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DeviceModel *model READ model CONSTANT)

public:
    explicit DeviceManager(QObject *parent = nullptr);

    DeviceModel *model() { return deviceModel_; }

private slots:
    IDevice *findItemByUUID(const QString &uuid);
    void onDeviceAdded(const QString &uuid);
    void onDeviceRemoved(const QString &uuid);

private:
    friend class DeviceModel;

    QList<IDevice *> devices_;
    IEventMonitor *eventMonitor_;
    DeviceModel *deviceModel_;
};

#endif // CONNECTIONMANAGER_H
