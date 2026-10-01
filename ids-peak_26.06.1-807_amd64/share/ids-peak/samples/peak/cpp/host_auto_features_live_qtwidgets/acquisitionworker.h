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

#ifndef ACQUISITIONWORKER_H
#define ACQUISITIONWORKER_H

#include <peak_ipl/peak_ipl.hpp>
#include <peak/peak.hpp>

#include "autofeatures.h"

#include <QImage>
#include <QObject>

#include <atomic>

class AcquisitionWorker : public QObject
{
    Q_OBJECT

public:
    explicit AcquisitionWorker(QObject* parent = nullptr);
    ~AcquisitionWorker() override = default;

    void Start();
    void Stop();

    void SetDataStream(std::shared_ptr<peak::core::DataStream> dataStream);
    void SetAutoFeatures(std::shared_ptr<AutoFeatures> autoFeatures);

private:
    std::shared_ptr<peak::core::DataStream> m_dataStream;
    std::shared_ptr<peak::core::NodeMap> m_nodemapRemoteDevice;

    std::atomic<bool> m_running{true};

    bool m_hostColorGainsEnabled{false};
    peak::ipl::Gain *m_gainControllerIPL{};

    unsigned int m_frameCounter{};
    unsigned int m_errorCounter{};

    size_t m_imageWidth = 0;
    size_t m_imageHeight = 0;
    size_t m_bufferWidth = 0;
    size_t m_bufferHeight = 0;

    std::unique_ptr<peak::ipl::ImageConverter> m_imageConverter;
    std::shared_ptr<AutoFeatures> m_autoFeatures;

signals:
    void imageReceived(QImage image);
    void counterChanged(unsigned int frameCounter, unsigned int errorCounter);
};

#endif // ACQUISITIONWORKER_H
