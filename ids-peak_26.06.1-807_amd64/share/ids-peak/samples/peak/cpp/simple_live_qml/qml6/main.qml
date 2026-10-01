/*!
 * \file    main.qml
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   1.0.0
 *
 * \brief   This application demonstrates how to use the IDS peak genericAPI
 *          combined with a QML GUI to display images from Genicam
 *          compatible device.
 *
 * \version 1.1.0
 *
 * Copyright (C) 2019 - 2022, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without notice
 * and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility for any errors
 * that may appear in this document.
 *
 * This document, or source code, is provided solely as an example of how to utilize
 * IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */

import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts

import BackEnd
import ImageItem

Window {
    id:window
    visible: true
    width: 640
    height: 480
    title: qsTr("simple_live_qml")

    BackEnd {
        id: backend
        onImageReceived: function(image) {
            cameraLiveImage.setImage(image)
        }
        onCounterChanged: function(frameCounter, errorCounter) {
            counterText.text = "Acquired: " + frameCounter + ", errors: " + errorCounter
        }
        onMessageBoxTrigger: function(messageTitle, messageText, critical) {
            if(critical)
            {
                criticalMessageBox.title = messageTitle
                criticalMessageBox.text = messageText
                criticalMessageBox.open()
            }
            else
            {
                messageBox.title = messageTitle
                messageBox.text = messageText
                messageBox.open()
            }
        }
        Component.onCompleted: {
            versionText.text = "simple_live_qml v" + Version()
            backend.OpenDevice()
        }
    }
    
    Dialog {
        id: aboutQtDialog
        title: "About Qt"
        standardButtons: Dialog.Ok
        anchors.centerIn: Overlay.overlay

        ColumnLayout {
            anchors.fill: parent

            Text {
                id: aboutQtDialogVersion
                text: "This program uses Qt version " + backend.QtVersion()
            }
            Text {
                id: aboutQtDialogLink
                text: "Please see <a href=\"https://qt.io/licensing\">qt.io/licensing</a> for an overview of Qt licensing."
                wrapMode: Text.WordWrap
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }

    Rectangle {
        id: rectangle
        color: "#e4e4e4"
        anchors { top: parent.top; bottom: parent.bottom; left: parent.left; right: parent.right }
        anchors { topMargin: 0; bottomMargin: 24; leftMargin: 0; rightMargin: 0 }

        ImageItem {
            id: cameraLiveImage
            anchors.fill: parent
        }
    }

    Text {
        id: counterText
        text: qsTr("Acquired: -, errors: -")
        anchors.rightMargin: 4
        verticalAlignment: Text.AlignVCenter
        anchors { top: rectangle.bottom; bottom: parent.bottom; left: parent.left; right: versionText.left }
        anchors.margins: 4
    }

    Text {
        id: aboutQtLink
        width: 70
        text: qsTr("<a href=\"#aboutQt\">About Qt</a>")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors { top: rectangle.bottom; bottom: parent.bottom; right: parent.right }
        anchors.margins: 4
        onLinkActivated: aboutQtDialog.open()
    }

    Text {
        id: versionText
        width: 200
        text: qsTr("Acquired: -, errors: -")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors { top: rectangle.bottom; bottom: parent.bottom; right: aboutQtLink.left }
        anchors.margins: 4
    }

    MessageDialog {
        id: messageBox
    }

    MessageDialog {
        id: criticalMessageBox
        onAccepted: {
            Qt.quit()
        }
    }
}
