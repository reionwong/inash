/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import org.iNash 1.0

Item {
    id: control

    property var model: null
    property int index: -1

    Rectangle {
        anchors.fill: parent
        color: "#F3F4F9"
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Software Version: " + control.model.getData(control.index).value("ProductVersion", qsTr("Unknown"))
        }

        Label {
            text: "Type: " + control.model.getData(control.index).value("DeviceClass", qsTr("Unknown"))
        }
    }
}
