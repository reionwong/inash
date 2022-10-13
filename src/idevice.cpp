/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

#include "idevice.h"

#include <QDebug>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>


static QStringList deviceKeys {"ActivationState",
                               "BasebandActivationTicketVersion",
                               "BasebandCertId",
                               "BasebandChipID",
                               "BasebandMasterKeyHash",
                               "BasebandRegionSKU",
                               "BasebandSerialNumber",
                               "BasebandStatus",
                               "BasebandVersion",
                               "BluetoothAddress",
                               "BoardId",
                               "BrickState",
                               "BuildVersion",
                               "CPUArchitecture",
                               "CertID",
                               "ChipID",
                               "ChipSerialNo",
                               "DeviceClass",
                               "DeviceColor",
                               "DeviceName",
                               "DieID",
                               "EthernetAddress",
                               "FirmwareVersion",
                               "FusingStatus",
                               "HardwareModel",
                               "HardwarePlatform",
                               "HasSiDP",
                               "HostAttached",
                               "InternationalMobileEquipmentIdentity",
                               "MLBSerialNumber",
                               "MobileEquipmentIdentifier",
                               "MobileSubscriberCountryCode",
                               "MobileSubscriberNetworkCode",
                               "ModelNumber",
                               "NonVolatileRAM",
                               "PartitionType",
                               "PasswordProtected",
                               "PkHash",
                               "ProductName",
                               "ProductType",
                               "ProductVersion",
                               "ProductionSOC",
                               "ProtocolVersion",
                               "ProximitySensorCalibration",
                               "RegionInfo",
                               "SIMStatus",
                               "SIMTrayStatus",
                               "SerialNumber",
                               "SoftwareBehavior",
                               "SoftwareBundleVersion",
                               "TelephonyCapability",
                               "TimeIntervalSince1970",
                               "TimeZone",
                               "TimeZoneOffsetFromUTC",
                               "TrustedHostAttached",
                               "UniqueChipID",
                               "UniqueDeviceID",
                               "UseRaptorCerts",
                               "Uses24HourClock",
                               "WiFiAddress",
                               "WirelessBoardSerialNumber",
                               "kCTPostponementInfoPRLName",
                               "kCTPostponementInfoServiceProvisioningState"
};

IDevice::IDevice(const QString &uuid, QObject *parent)
    : QObject(parent)
    , uuid_(uuid)
{
    updateInfos();
}

QString IDevice::value(const QString &key, const QString &fallback)
{
    return datas_.value(key, fallback);
}

QString IDevice::uuid() const
{
    return uuid_;
}

void IDevice::updateInfos()
{
    idevice_t device;
    idevice_new(&device, uuid_.toUtf8().constData());

    if (!device) {
        qDebug() << uuid_ << "error";
        return;
    }

    lockdownd_client_t client = nullptr;
    if (lockdownd_client_new(device, &client, "inash") != LOCKDOWN_E_SUCCESS) {
        qDebug() << Q_FUNC_INFO << uuid_;
        return;
    }

    // Read the device name.
    char *name = nullptr;
    lockdownd_get_device_name(client, &name);
    device_name_ = QString::fromLatin1(name);
    free(name);
    qDebug() << "deviceName: " << device_name_;
    emit deviceNameChanged();

    plist_t node = nullptr;
    char *value = nullptr;

    for (const QString &key : deviceKeys) {
        if (lockdownd_get_value(client, NULL, key.toStdString().c_str(), &node) != LOCKDOWN_E_SUCCESS)
            continue;

        plist_get_string_val(node, &value);
        datas_.insert(key, value);
        qDebug() << key << value;
    }
}

QString IDevice::deviceName() const
{
    return device_name_;
}
