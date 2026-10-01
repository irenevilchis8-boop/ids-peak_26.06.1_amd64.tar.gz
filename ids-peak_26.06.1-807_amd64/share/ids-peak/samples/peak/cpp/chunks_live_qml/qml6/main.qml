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
    title: qsTr("chunks_live_qml")

    BackEnd {
        id: backend
        onImageReceived: function(image, chunkDataExposureTime_ms) {
            cameraLiveImage.setImage(image)

            if (chunkDataExposureTime_ms < 0)
            {
                chunkInfo.text = "Exposure time: not available"
            }
            else
            {
                chunkInfo.text = "Exposure time: " + chunkDataExposureTime_ms + " ms"
            }
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
            versionText.text = "chunks_live_qml v" + Version()
            if (!backend.start())
            {
                window.close()
            }
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

            Text {
                id: chunkInfo
                color: "red"
                font.pixelSize: Math.sqrt(window.width * window.height) / 30
            }
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
