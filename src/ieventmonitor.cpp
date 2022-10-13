/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#include "ieventmonitor.h"
#include <QDebug>

IEventMonitor::IEventMonitor(QObject *parent)
    : QObject(parent)
{
}

void IEventMonitor::start()
{
    char **devices = nullptr;
    int count = 0;

    if (idevice_get_device_list(&devices, &count) != IDEVICE_E_SUCCESS) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        emit deviceAdded(QString::fromLatin1(devices[i]));
    }

    if (devices)
        idevice_device_list_free(devices);

    idevice_event_subscribe([](const idevice_event_t *event, void *user_data) {
        static_cast<IEventMonitor *>(user_data)->onEventCallback(event);
    }, this);
}

void IEventMonitor::onEventCallback(const idevice_event_t *event)
{
    const QString uuid = event->udid;

    switch (event->event) {
    case IDEVICE_DEVICE_ADD: {
        emit deviceAdded(uuid);
        break;
    }

    case IDEVICE_DEVICE_REMOVE: {
        emit deviceRemoved(uuid);
        break;
    }

    default:
        break;
    }
}
