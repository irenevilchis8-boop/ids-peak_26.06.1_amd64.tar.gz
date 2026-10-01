/*!
 * \file    acquisitionworker.h
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \brief   The AcquisitionWorker class is used in a worker thread to capture
 *          images from the device continuously and do an image conversion into
 *          a desired pixel format. The image with an explicit number is sent
 *          to the corresponding display.
 *
 * \version 1.0.0
 *
 * Copyright (C) 2024 - 2026, IDS Imaging Development Systems GmbH.
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

#ifndef ACQUISITIONWORKER_H
#define ACQUISITIONWORKER_H

#include <ids_peak_comfort_c/ids_peak_comfort_c.h>

#include <QImage>
#include <QObject>

#define NUMBER_OF_DISPLAYS  4 // Maximum depends on camera capabilities


class AcquisitionWorker : public QObject
{
    Q_OBJECT

public:

    explicit AcquisitionWorker(QObject* parent = nullptr);
    peak_camera_handle m_hCam{};

private:

    int m_numDisplay{0};

    bool m_running{ false };

    unsigned int m_frameCounter{0};
    unsigned int m_errorCounter{0};

public slots:

    void Start();
    void Stop();

signals:

    void Started();
    void Stopped();
    void ImageReceived(int numDisplay, QImage image);
    void SequenceFinished();
    void CounterUpdated(unsigned int frameCounter, unsigned int errorCounter);
    void Error(QString message);
};

#endif // ACQUISITIONWORKER_H
