/*!
 * \brief   The AcquisitionWorker class is used in a worker thread to capture
 *          images from the device continuously and do an image conversion into
 *          a desired pixel format.
 *
 * Copyright (C) 2020 - 2026, IDS Imaging Development Systems GmbH.
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

#include <QDebug>
#include <cmath>

#include <utility>
#include <peak/peak.hpp>

AcquisitionWorker::AcquisitionWorker(QObject* parent) : QObject(parent)
{
}

void AcquisitionWorker::start()
{
    try
    {
        // Lock critical features to prevent them from changing during acquisition
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("TLParamsLocked")->SetValue(1);

        // Determine image size
        m_imageWidth = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Width")->Value();
        m_imageHeight = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Height")->Value();
        m_size = static_cast<const size_t>(m_imageWidth * m_imageHeight * m_bytesPerPixel);

        m_pipeline.SetOutputPixelFormat(peak::common::PixelFormat::BGRa8);

        // Start acquisition
        m_dataStream->StartAcquisition();
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->Execute();
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->WaitUntilDone();
    }
    catch (const std::exception& e)
    {
        qDebug() << "Exception: " << e.what();
        emit messageBoxTrigger("Exception", e.what());
    }

    while (m_running)
    {
        try
        {
            // Get buffer from device's datastream
            const auto buffer = m_dataStream->WaitForFinishedBuffer(5000);

            double chunkDataExposureTime_ms = -1;
            if (buffer->HasChunks() && m_enableChunks)
            {
                m_nodemapRemoteDevice->UpdateChunkNodes(buffer);

                // Get the value of the exposure time chunk
                const auto chunkData = m_nodemapRemoteDevice->FindNode<peak::core::nodes::FloatNode>("ChunkExposureTime")->Value();
                chunkDataExposureTime_ms = round(chunkData) / 1000.0;
            }

            QImage qImage(static_cast<int>(m_imageWidth), static_cast<int>(m_imageHeight), QImage::Format_RGB32);
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
            auto qImageSize = static_cast<size_t>(qImage.sizeInBytes());
#else
            auto qImageSize = static_cast<size_t>(qImage.byteCount());
#endif
            // Use the DefaultPipeline to automatically debayer and convert the
            // image to the requested output pixel format from an image view.

            auto image = m_pipeline.Process(buffer->ToImageView());
            // While the pipeline.Process() function guarantees making a copy,
            // we still copy over the image data into the QImage so we
            // we can release `image` while only keeping the `qImage`.
            memcpy(qImage.bits(), image.GetData(), qImageSize);

            // Queue buffer so that it can be used again
            m_dataStream->QueueBuffer(buffer);

            // Emit signal that the image is ready to be displayed
            emit imageReceived(qImage, chunkDataExposureTime_ms);

            m_frameCounter++;
        }
        catch (const std::exception& e)
        {
            m_errorCounter++;

            qDebug() << "Exception: " << e.what();
            emit messageBoxTrigger("Exception", e.what());
        }

        // Send signal with current frame and error counter
        emit counterChanged(m_frameCounter, m_errorCounter);
    }
}

void AcquisitionWorker::setDataStream(std::shared_ptr<peak::core::DataStream> dataStream)
{
    m_dataStream = std::move(dataStream);
}

void AcquisitionWorker::setNodemapRemoteDevice(std::shared_ptr<peak::core::NodeMap> nodeMap)
{
    m_nodemapRemoteDevice = std::move(nodeMap);
}

void AcquisitionWorker::stop()
{
    m_running = false;
}

int AcquisitionWorker::getImageWidth() const
{
    return static_cast<int>(m_imageWidth);
}

int AcquisitionWorker::getImageHeight() const
{
    return static_cast<int>(m_imageHeight);
}

void AcquisitionWorker::setEnableChunks(bool enable)
{
    m_enableChunks = enable;
}
