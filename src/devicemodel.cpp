/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#include "devicemodel.h"

DeviceModel::DeviceModel(QList<IDevice *> *list, QObject *parent)
    : QAbstractListModel(parent)
    , list_(list)
{
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return list_->size();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    IDevice *device = list_->at(index.row());

    switch (role) {
    case UUIdRole:
        return device->uuid();
    case DeviceNameRole:
        return device->deviceName();
    case DeviceDataRole:
        return QVariant::fromValue(device);
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    static QHash<int, QByteArray> s_roles;

    if (s_roles.isEmpty()) {
        s_roles.insert(DeviceModel::UUIdRole, "uuid");
        s_roles.insert(DeviceModel::DeviceNameRole, "deviceName");
        s_roles.insert(DeviceModel::DeviceDataRole, "data");
    }

    return s_roles;
}

IDevice *DeviceModel::getData(int index)
{
    if (index < 0 || index > list_->size())
        return nullptr;

    return list_->at(index);
}
