/*!
 * \file    acquisitionworker.cpp
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

#include "acquisitionworker.h"

#include <ids_peak_comfort_c/ids_peak_comfort_c.h>

#include <QDebug>
#include <QPixelFormat>
#include <QThread>

#include <cmath>
#include <cstring>


AcquisitionWorker::AcquisitionWorker(QObject* parent) : QObject(parent)
{}

void AcquisitionWorker::Start()
{
    peak_roi roi = { { 0, 0 }, { 0, 0 } };

    if (PEAK_STATUS_SUCCESS == peak_ROI_Get(m_hCam, &roi))
    {
        m_running = true;

        emit Started();

        while (m_running)
        {
            peak_buffer bufferRaw;
            peak_buffer buffer;
            peak_frame_handle frame = PEAK_INVALID_HANDLE;

            auto status = peak_Acquisition_WaitForFrame(m_hCam, 5000, &frame);
            if (PEAK_STATUS_ABORTED == status)
            {
                if (!m_running)
                {
                    emit Stopped();
                    return;
                }
            }
            else if (PEAK_STATUS_SUCCESS == status)
            {
                if (PEAK_STATUS_SUCCESS == peak_Frame_Buffer_Get(frame, &bufferRaw))
                {
                    peak_frame_handle convertedFrame;
                    if (PEAK_STATUS_SUCCESS == peak_IPL_ProcessFrame(m_hCam, frame, &convertedFrame))
                    {
                        if (PEAK_STATUS_SUCCESS == peak_Frame_Buffer_Get(convertedFrame, &buffer))
                        {
                            QImage::Format imageFormat = QImage::Format_RGB888;
                            QImage qImage(static_cast<int>(roi.size.width), static_cast<int>(roi.size.height), imageFormat);
                            memcpy(qImage.bits(), static_cast<unsigned char*>(buffer.memoryAddress), static_cast<int>(roi.size.width * roi.size.height * 3));

                            emit ImageReceived(m_numDisplay++, qImage);
                            if (m_numDisplay > NUMBER_OF_DISPLAYS - 1)
                            {
                                m_numDisplay = 0;
                                emit SequenceFinished();
                            }

                            m_frameCounter++;

                            peak_Frame_Release(m_hCam, convertedFrame);
                        }

                        peak_Frame_Release(m_hCam, frame);
                    }
                }
            }
            else if (PEAK_STATUS_TIMEOUT == status)
            {
                // This is no error
                QThread::msleep(100);
            }
            else
            {
                m_errorCounter++;

                QThread::msleep(100);
            }

            emit CounterUpdated(m_frameCounter, m_errorCounter);
        }
    }

    emit Stopped();
}

void AcquisitionWorker::Stop()
{
    m_running = false;
}
