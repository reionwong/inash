/*
    SPDX-FileCopyrightText: 2022 Reion Wong <reionwong@gmail.com>
    SPDX-FileContributor:
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import org.iNash 1.0

Item {
    id: control

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.05
        radius: 10
    }

    MouseArea {
        anchors.fill: parent
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Label {
            text: model.deviceName
        }
    }
}
