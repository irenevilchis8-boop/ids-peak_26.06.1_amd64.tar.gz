/*!
 * \brief   This application demonstrates how to use the IDS peak genericAPI
 *          combined with a QML GUI to configure a camera with sequencer and
 *          display the image sequence.
 *
 * Copyright (C) 2019 - 2022, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without
 * notice and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for any errors that may appear in this document.
 *
 * This document, or source code, is provided solely as an example
 * of how to utilize IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */

import QtQuick 2.6
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window 2.2
import QtQuick.Layouts

import Sequencer.ImageItem 1.0

ApplicationWindow {
    id: root
    title: "IDS Sequencer Demo"
    visible: true
    width: 600
    minimumWidth: 500
    height: 800
    property variant imageWindow
    property variant sequencerImageWindows: []
    property variant parameterWindow

    property var exposureValues: [1.0, 1.2]

    Connections {
        target: backEnd

        Component.onCompleted: function() {
            console.log("init...")
            backEnd.init()
        }

        function onCameraOpened() {
            // check ROI size on program startup
            roiSizeDialog.visible = true
            roiSizeDialog.update()
        }

        function onStartupFinished() {
            if (!imageWindow) {
                console.log("Creating camera window")
                imageWindow = createWindow("qrc:/qml/Window_Image.qml")
            } else {
                console.log("Focus camera window")
                imageWindow.show()
            }
            // connect the controls to the nodes of the camera
            saveControl.node = backEnd.nodeList.get("SequencerSetSave")
            loadControl.node = backEnd.nodeList.get("SequencerSetLoad")
            exposureControl.node = backEnd.nodeList.get("ExposureTime")
            exposureControl.to = 1 / 25 * 1000000
            gainSelectorControl.node = backEnd.nodeList.get("GainSelector")
            gainControl.node = backEnd.nodeList.get("Gain")
            offsetXControl.node = backEnd.nodeList.get("OffsetX")
            offsetYControl.node = backEnd.nodeList.get("OffsetY")
        }

        function onError(message) {
            errorDialog.text = message
            errorDialog.visible = true
        }

        function onClosing() {
            saveControl.node = null
            loadControl.node = null
            exposureControl.node = null
            gainSelectorControl.node = null
            gainControl.node = null
            offsetXControl.node = null
            offsetYControl.node = null
            if (imageWindow) {
                imageWindow.destroy()
            }
            if (sequencerImageWindows) {
                for (var i = 0; i < sequencerImageWindows.length; ++i) {
                    sequencerImageWindows[i].destroy()
                }
            }
        }
    }

    function createWindow(source) {
        var component = Qt.createComponent(source)
        var newWindow = component.createObject(root)
        if (component.status === Component.Ready)
            newWindow.show()
        else
            component.statusChanged.connect(function () {
                newWindow.show()
            })
        return newWindow
    }

    function showSequencerImageWindows() {
        var i = sequencerImageWindows ? sequencerImageWindows.length : 0
        var delta = 0
        var count = backEnd.sequencerDuration
        for (i; i < count; ++i) {
            sequencerImageWindows.push(createWindow("Window_Image.qml"))
            var imwi = sequencerImageWindows[sequencerImageWindows.length - 1]
            imwi.x = root.x + root.width + 20 + delta
            imwi.y = root.y + 20 + delta
            imwi.title = "Sequence Image " + i
            imwi.imageId = i
            delta += 20
            imwi.visibleOnNewImage = true
        }
        for (i = 0; i < sequencerImageWindows.length; ++i) {
            var window = sequencerImageWindows[i]
            window.enabled = true
            window.visible = true
        }
    }

    function cleanControls() {
        exposureControl.dirty = false
        gainControl.dirty = false
        offsetXControl.dirty = false
        offsetYControl.dirty = false
    }

    Flickable {
        contentWidth: parent.width
        contentHeight: column.height
        anchors.fill: parent

        Column {
            id: column
            width: parent.width
            spacing: 8

            PropertyContainer {
                width: parent.width
                content: [
                    ComboBox {
                        id: spinBox
                        property bool dirty: exposureControl.dirty
                                             || gainControl.dirty
                                             || offsetXControl.dirty
                                             || offsetYControl.dirty
                        model: ["Sequencerset 1", "Sequencerset 2", "Sequencerset 3", "Sequencerset 4"]
                        width: parent.width - 2 * parent.padding
                        onActivated: function(idx) {
                            backEnd.loadSequencerSet(idx)
                            cleanControls()
                        }

                        Component.onCompleted: currentIndex = 0

                    }
                ]
            }
            PropertyContainer {
                width: parent.width
                content: [
                    PropertyControl_FloatSlider {
                        id: exposureControl
                        width: parent.width - 2 * parent.padding
                        decimals: 0
                        decimalFactor: 1
                    },
                    PropertyControl_EnumComboBox {
                        id: gainSelectorControl
                        width: parent.width - 2 * parent.padding
                    },
                    PropertyControl_FloatSlider {
                        id: gainControl
                        width: parent.width - 2 * parent.padding
                        decimals: 2
                        decimalFactor: 1
                    },
                    PropertyControl_FloatSlider {
                        id: offsetXControl
                        width: parent.width - 2 * parent.padding
                        decimals: 0
                        decimalFactor: 1
                    },
                    PropertyControl_FloatSlider {
                        id: offsetYControl
                        width: parent.width - 2 * parent.padding
                        decimals: 0
                        decimalFactor: 1
                    }
                ]
            }
            PropertyContainer {
                width: parent.width
                content: [
                    PropertyControl_CommandButton {
                        id: saveControl
                        autoApply: false
                        width: parent.width - 2 * parent.padding
                        dirty: spinBox.dirty
                        onExecuted: {
                            backEnd.saveSequencerSet(spinBox.value)
                            cleanControls()
                        }
                    },
                    PropertyControl_CommandButton {
                        id: loadControl
                        autoApply: false
                        width: parent.width - 2 * parent.padding
                        onExecuted: {
                            backEnd.loadSequencerSet(spinBox.value)
                            cleanControls()
                        }
                    }
                ]
            }
        }
    }

    function startSequencer() {
        backEnd.switchToSequencerAcquisition()
        if (imageWindow) {
            imageWindow.visible = false
            imageWindow.enabled = false
        }
        triggerDialog.visible = true
        showSequencerImageWindows()
        backEnd.softwareTrigger()
    }

    Dialog_Error {
        id: errorDialog
        modal: true
        onAccepted: {
            Qt.quit()
        }
    }

    Dialog_SaveChanges {
        id: saveChangesDialog
        modal: true
        onAccepted: {
            backEnd.saveSequencerSet(spinBox.value)
            cleanControls()
            startSequencer()
        }
        onDiscarded: {
            saveChangesDialog.visible = false
            backEnd.loadSequencerSet(spinBox.value)
            cleanControls()
            startSequencer()
        }
        onRejected: {
            saveChangesDialog.visible = false
        }
    }

    Dialog_SequencerTrigger {
        id: triggerDialog
        onTriggered: {
            backEnd.softwareTrigger()
        }
        onSaveClicked: {
            folderDialog.visible = true
        }

        onRejected: {
            for (var i = 0; i < sequencerImageWindows.length; ++i) {
                var window = sequencerImageWindows[i]
                window.enabled = false
                window.visible = false
            }
            backEnd.switchToContinuousAcquisition()
            backEnd.loadSequencerSet(spinBox.value)
            if (imageWindow) {
                imageWindow.visible = true
                imageWindow.enabled = true
            }
        }
    }

    Dialog_Folder {
        id: folderDialog
        onAccepted: {
            for (var i = 0; i < sequencerImageWindows.length; ++i) {
                var url = (fileUrl + "/" + sequencerImageWindows[i].title + ".jpg").replace(
                            'file:///', '')
                sequencerImageWindows[i].liveImage.saveSourceImage(url)
            }
            folderDialog.close()
        }
        onRejected: {
            console.log("Canceled")
            folderDialog.close()
        }
    }

    Dialog_RoiSize {
        id: roiSizeDialog
        onAccepted: {
            var roi = Qt.rect(0, 0, roiSizeDialog.imageWidth,
                              roiSizeDialog.imageHeight)
            backEnd.applyRoi(roi)
            backEnd.cameraSettingsStartup()
        }
        onRejected: {
            backEnd.cameraSettingsStartup()
        }
    }

    // Define keyboard shortcuts to show closed windows
    Shortcut {
        sequence: "i"
        onActivated: {
            if (imageWindow) {
                imageWindow.show()
            }
        }
    }

    Button {
        anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.bottom }
        text: "Run Sequencer"
        onClicked: {
            if (spinBox.dirty)
                saveChangesDialog.visible = true
            else
                startSequencer()
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
                text: "This program uses Qt version " + backEnd.QtVersion()
            }
            Text {
                id: aboutQtDialogLink
                text: "Please see <a href=\"https://qt.io/licensing\">qt.io/licensing</a> for an overview of Qt licensing."
                wrapMode: Text.WordWrap
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }

    Text {
        id: aboutQtLink
        width: 70
        text: qsTr("<a href=\"#aboutQt\">About Qt</a>")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors { bottom: parent.bottom; right: parent.right }
        anchors.margins: 4
        onLinkActivated: aboutQtDialog.open()
    }

    Text {
        id: versionText
        width: 200
        text: backEnd.Version()
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors { bottom: parent.bottom; right: aboutQtLink.left }
        anchors.margins: 4
    }
}
