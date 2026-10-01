/*!
 * \brief   The ImageConverter class is used in a worker thread to convert
 *          buffers received from the datastream to images that can be displayed.
 *
 * Copyright (C) 2020 - 2026, IDS Imaging Development Systems GmbH.
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

#include "imageconverterworker.h"

#include <peak/device/peak_device.hpp>
#include <peak/node_map/peak_node_map.hpp>

#include <QDebug>

void ImageConverterWorker::setDataStream(const std::shared_ptr<peak::core::DataStream>& dataStream)
{
    m_dataStream = dataStream;
    m_nodemapRemoteDevice = m_dataStream->ParentDevice()->RemoteDevice()->NodeMaps().at(0);

    try
    {
        // Determine image size
        m_imageWidth = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Width")->Value();
        m_imageHeight = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Height")->Value();

        m_pipeline.SetOutputPixelFormat(peak::common::PixelFormat::RGB8);
    }
    catch (const std::exception& e)
    {
        qDebug() << "[ImageConverterWorker::setDataStream] EXCEPTION: " << e.what();
    }
}

void ImageConverterWorker::setImageCount(const unsigned int imageCount)
{
    m_imageCount = imageCount;
}

void ImageConverterWorker::convert(const std::shared_ptr<peak::core::Buffer>& buffer)
{
    if (!buffer)
        return;

    try
    {
        if (buffer->IsIncomplete())
        {
            qDebug() << "[ImageConverterWorker::convert] Buffer incomplete";
        }

        std::int64_t chunkInfo = -1;
        unsigned long long timestamp_us = 0;

        // if the buffer has chunks retrieve information about the current sequencer set from it
        if (buffer->HasChunks())
        {
            // update the chunk nodes of the node map of the remote device
            m_nodemapRemoteDevice->UpdateChunkNodes(buffer);

            // read the current sequencer set from chunk
            chunkInfo = static_cast<int>(
                m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("ChunkSequencerSetActive")
                    ->Value());

            try
            {
                // for IDS cameras, try using the ChunkTimestamp value
                // for other cameras, don't use that, because the value might not be ns
                const auto vendorName = m_nodemapRemoteDevice
                                            ->FindNode<peak::core::nodes::StringNode>("DeviceVendorName")
                                            ->Value();
                if (vendorName.find("IDS") != std::string::npos)
                {
                    timestamp_us = m_nodemapRemoteDevice
                                       ->FindNode<peak::core::nodes::IntegerNode>("ChunkTimestamp")
                                       ->Value()
                        / 1000;
                }
            }
            catch (const peak::core::Exception&)
            { /* ignore, use Timestamp_ns() below */
            }
        }

        if (timestamp_us == 0)
        {
            // read the timestamp of the current image from the buffer info
            try
            {
                timestamp_us = buffer->Timestamp_ns() / 1000;
            }
            catch (const peak::core::InternalErrorException&)
            { /* ignore, keep timestamp_us at 0 */
            }
        }

        // Use the DefaultPipeline to automatically debayer and convert the
        // image to the requested output pixel format from an image view.

        auto image = m_pipeline.Process(buffer->ToImageView());


        // convert IDS peak ICV image to QImage and store it in a vector
        auto index = m_converterCounter++ % m_imageCount;

        // While the pipeline.Process() function guarantees making a copy,
        // we still copy over the image data into the QImage so we
        // we can release `image` while only keeping the `qImage`.
        auto qImage = QImage(static_cast<int>(image.GetSize().GetWidth()),
            static_cast<int>(image.GetSize().GetHeight()), QImage::Format_RGB888);
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        auto qImageSize = static_cast<size_t>(qImage.sizeInBytes());
#else
        auto qImageSize = static_cast<size_t>(qImage.byteCount());
#endif

        memcpy(qImage.bits(), image.GetData(), qImageSize);

        // queue buffer so that it can be used again
        m_dataStream->QueueBuffer(buffer);

        // emit signal that the image is ready to be displayed
        if (chunkInfo == -1)
        {
            emit imageReceived(
                qImage, index % (m_imageCount / 2), timestamp_us, timestamp_us - m_timestamp_previous_us);
        }
        else
        {
            emit imageReceived(qImage, chunkInfo, timestamp_us, timestamp_us - m_timestamp_previous_us);
        }

        m_timestamp_previous_us = timestamp_us;
    }
    catch (const std::exception& e)
    {
        qDebug() << "[ImageConverterWorker::convert] EXCEPTION: " << e.what();

        // try to queue buffer
        try
        {
            if (!buffer->IsQueued())
            {
                m_dataStream->QueueBuffer(buffer);
            }
        }
        catch (const std::exception& exc)
        {
            qDebug() << "[ImageConverterWorker::convert] EXCEPTION: " << exc.what();
        }
        return;
    }
}

void ImageConverterWorker::resetCounter()
{
    m_converterCounter = 0;
}
