/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#include "devicemanager.h"
#include "idevice.h"

#include <QDebug>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
    , eventMonitor_(new IEventMonitor)
    , deviceModel_(new DeviceModel(&devices_))
{
    connect(eventMonitor_, &IEventMonitor::deviceAdded, this, &DeviceManager::onDeviceAdded);
    connect(eventMonitor_, &IEventMonitor::deviceRemoved, this, &DeviceManager::onDeviceRemoved);

    eventMonitor_->start();
}

IDevice *DeviceManager::findItemByUUID(const QString &uuid)
{
    for (IDevice *device : std::as_const(devices_)) {
        if (device->uuid() == uuid)
            return device;
    }

    return nullptr;
}

void DeviceManager::onDeviceAdded(const QString &uuid)
{
    qDebug() << Q_FUNC_INFO << uuid;

    IDevice *device = findItemByUUID(uuid);
    if (device)
        return;

    device = new IDevice(uuid);
    deviceModel_->beginInsertRows(QModelIndex(), 0, 0);
    devices_.push_front(device);
    deviceModel_->endInsertRows();
}

void DeviceManager::onDeviceRemoved(const QString &uuid)
{
    qDebug() << Q_FUNC_INFO << uuid;

    IDevice *device = findItemByUUID(uuid);
    if (device) {
        int index = devices_.indexOf(device);
        deviceModel_->beginRemoveRows(QModelIndex(), index, index);
        devices_.removeOne(device);
        deviceModel_->endRemoveRows();
    }
}
