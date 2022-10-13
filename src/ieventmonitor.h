/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#ifndef IEVENTMONITOR_H
#define IEVENTMONITOR_H

#include <QObject>

extern "C" {
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
}

class IEventMonitor : public QObject
{
    Q_OBJECT

public:
    explicit IEventMonitor(QObject *parent = nullptr);

    void start();

signals:
    void deviceAdded(const QString &uuid);
    void deviceRemoved(const QString &uuid);

private:
    void onEventCallback(const idevice_event_t *event);
};

#endif // IEVENTMONITOR_H
