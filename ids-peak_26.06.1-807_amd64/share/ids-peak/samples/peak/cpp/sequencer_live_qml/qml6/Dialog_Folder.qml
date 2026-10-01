/*!
 * \brief   Prototype for folder dialog
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
import QtCore

FolderDialog {
    id: dialogFolder
    title: "Please choose a folder"
    currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
    signal userAccepted(string path)

    onAccepted: {
        userAccepted(fileUrl)
    }

    onRejected: {
        console.log("Canceled")
        fileDialog.close()
    }
}
