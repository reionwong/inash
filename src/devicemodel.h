/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include "idevice.h"

class DeviceManager;
class DeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        UUIdRole = Qt::UserRole + 1,
        DeviceNameRole,
        DeviceDataRole
    };

    explicit DeviceModel(QList<IDevice *> *list, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE IDevice *getData(int index);

private:
    friend class DeviceManager;

    QList<IDevice *> *list_;
};

#endif // DEVICEMODEL_H
