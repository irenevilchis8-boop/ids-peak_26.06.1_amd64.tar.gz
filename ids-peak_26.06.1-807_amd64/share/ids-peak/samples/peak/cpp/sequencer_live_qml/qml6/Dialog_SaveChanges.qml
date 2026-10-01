/*!
 * \brief   Prototype for dialog to let the user save or discard changes
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
import QtQuick.Controls

Dialog {
    id: dialogSaveChanges
    title: "Save Changes"
    anchors.centerIn: Overlay.overlay

    Text {
        id: name
        text: "There are unsaved changes. \n"
              + "Save sequencer set before proceeding or discard changes?"
    }
    standardButtons: Dialog.Cancel | Dialog.Discard | Dialog.Save
}
