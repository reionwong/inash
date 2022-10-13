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

Window {
    width: 900
    height: 550
    visible: true
    title: "iNash"

    DeviceManager {
        id: deviceManager
    }

    ListView {
        id: sideBarView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        width: 260
        currentIndex: -1

        spacing: 10

        model: deviceManager.model

        delegate: SideBarItem {
            width: ListView.view.width - 10
            height: 70
        }
    }

    DevicePage {
        id: devicePage
        anchors.left: sideBarView.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        model: deviceManager.model
        index: sideBarView.currentIndex
    }
}
