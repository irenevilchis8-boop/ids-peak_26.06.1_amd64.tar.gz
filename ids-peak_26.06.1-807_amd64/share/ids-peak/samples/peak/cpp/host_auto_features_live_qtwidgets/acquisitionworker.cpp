/*!
 * \brief   The AcquisitionWorker class is used in a worker thread to capture
 *          images from the device continuously and do an image conversion into
 *          a desired pixel format.
 *
 * Copyright (C) 2021 - 2026, IDS Imaging Development Systems GmbH.
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

#include <peak_ipl/peak_ipl.hpp>

#include <utility>

#include <QDebug>

#include <cmath>
#include <cstring>

// NOTE: Whether to use the `ImageConverter` for conversions.
//       Otherwise the `ConvertTo` function is used, which re-allocates
//       conversion buffers on every call.
//       Using the `ImageConverter` should be preferred for performance.
#define USE_IMAGE_CONVERTER


AcquisitionWorker::AcquisitionWorker(QObject* parent)
    : QObject(parent)
{
    m_imageConverter = std::make_unique<peak::ipl::ImageConverter>();
}

void AcquisitionWorker::Start()
{
    peak::ipl::PixelFormatName inputPixelFormat;
    peak::ipl::PixelFormatName unpackedPixelFormat;

    try
    {
        // Lock critical features to prevent them from changing during acquisition
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("TLParamsLocked")->SetValue(1);

        // Determine RAW buffer size
        m_bufferWidth = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Width")->Value();
        m_bufferHeight = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("Height")->Value();

        // Determine image size
        if (m_nodemapRemoteDevice->HasNode("UsableWidth"))
        {
            m_imageWidth = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("UsableWidth")
                               ->Value();
            m_imageHeight = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("UsableHeight")
                                ->Value();
        }
        else
        {
            m_imageWidth = m_bufferWidth;
            m_imageHeight = m_bufferHeight;
        }

        // Pre-allocate images for conversion that can be used simultaneously
        // This is not mandatory but it can increase the speed of image conversions
        size_t imageCount = 1;
        inputPixelFormat = static_cast<peak::ipl::PixelFormatName>(
            m_nodemapRemoteDevice->FindNode<peak::core::nodes::EnumerationNode>("PixelFormat")
                ->CurrentEntry()
                ->Value());

        switch (inputPixelFormat)
        {
        case peak::ipl::PixelFormatName::BayerRG10g40IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerRG10;
            break;
        case peak::ipl::PixelFormatName::BayerGR10g40IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerGR10;
            break;
        case peak::ipl::PixelFormatName::BayerBG10g40IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerBG10;
            break;
        case peak::ipl::PixelFormatName::BayerGB10g40IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerGB10;
            break;
        case peak::ipl::PixelFormatName::BayerRG12g24IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerRG12;
            break;
        case peak::ipl::PixelFormatName::BayerGR12g24IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerGR12;
            break;
        case peak::ipl::PixelFormatName::BayerBG12g24IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerBG12;
            break;
        case peak::ipl::PixelFormatName::BayerGB12g24IDS:
            unpackedPixelFormat = peak::ipl::PixelFormatName::BayerGB12;
            break;
        default:
            unpackedPixelFormat = inputPixelFormat;
            break;
        }

        if (inputPixelFormat != unpackedPixelFormat)
        {
            m_imageConverter->PreAllocateConversion(
                inputPixelFormat, unpackedPixelFormat, m_bufferWidth, m_bufferHeight, imageCount);
        }

        m_imageConverter->PreAllocateConversion(
            unpackedPixelFormat, peak::ipl::PixelFormatName::BGRa8, m_imageWidth, m_imageHeight, imageCount);

        // Start acquisition
        m_dataStream->StartAcquisition();
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->Execute();
        m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->WaitUntilDone();
    }
    catch (const std::exception& e)
    {
        qDebug() << "Exception: " << e.what();
    }

    while (m_running)
    {
        try
        {
            // Get buffer from device's datastream
            const auto buffer = m_dataStream->WaitForFinishedBuffer(5000);


            auto view = buffer->ToImageView();
            // NOTE: `image` still uses the memory owned by `buffer`.
            auto image = peak::ipl::Image(view);

            if (m_autoFeatures)
            {
                if (inputPixelFormat != unpackedPixelFormat)
                {
                    // We need to unpack the pixel format, since the
                    // IDS peak AFL cannot handle packed formats.
                    //
                    // Using the image converter ...
#ifdef USE_IMAGE_CONVERTER
                    image = m_imageConverter->Convert(
                        image, unpackedPixelFormat);
#else
                    // ... or without image converter
                    // NOTE: The `ConvertTo` function re-allocates conversion buffers on every call
                    //       using the `ImageConverter` should be preferred for performance.
                    image = image.ConvertTo(unpackPixelFormat);
#endif
                }
                // Otherwise the IDS peak AFL does its own conversion.
                // Additionally, it will use its own copy of the image,
                // even if the format matches. So passing `image`,
                // which might still use `buffers`'s memory, is fine.

                m_autoFeatures->ProcessImage(image);
            }

            QImage qImage(static_cast<int>(m_imageWidth), static_cast<int>(m_imageHeight), QImage::Format_RGB32);
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
            auto qImageSize = static_cast<size_t>(qImage.sizeInBytes());
#else
            auto qImageSize = static_cast<size_t>(qImage.byteCount());
#endif
            // Create IDS peak IPL image for debayering and convert it to BGRa8 format
#ifdef USE_IMAGE_CONVERTER
            // Using the image converter ...
            m_imageConverter->Convert(image,
                peak::ipl::PixelFormatName::BGRa8, qImage.bits(), qImageSize);
#else
            // ... or without image converter
            // NOTE: The `ConvertTo` function re-allocates conversion buffers on every call
            //       using the `ImageConverter` should be preferred for performance.
            image.ConvertTo(
                peak::ipl::PixelFormatName::BGRa8, qImage.bits(), qImageSize);
#endif

            // Requeue buffer
            m_dataStream->QueueBuffer(buffer);

            // Emit signal that the image is ready to be displayed
            emit imageReceived(qImage);

            m_frameCounter++;
        }
        catch (const std::exception& e)
        {
            m_errorCounter++;

            qDebug() << "Exception: " << e.what();
        }

        // Send signal with current frame and error counter
        emit counterChanged(m_frameCounter, m_errorCounter);
    }
}

void AcquisitionWorker::Stop()
{
    m_running = false;
}

void AcquisitionWorker::SetDataStream(std::shared_ptr<peak::core::DataStream> dataStream)
{
    m_dataStream = std::move(dataStream);
    m_nodemapRemoteDevice = m_dataStream->ParentDevice()->RemoteDevice()->NodeMaps().at(0);
}

void AcquisitionWorker::SetAutoFeatures(std::shared_ptr<AutoFeatures> autoFeatures)
{
    m_autoFeatures = std::move(autoFeatures);
}

