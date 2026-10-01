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

#ifndef ACQUISITIONWORKER_H
#define ACQUISITIONWORKER_H

#include "displaywindow.h"

#include <peak/peak.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak_icv/pipeline/peak_icv_default_pipeline.hpp>

#include <QImage>
#include <QLabel>
#include <QObject>

#include <cstdint>
#include <atomic>

#include "framestatistics.hpp"

class MainWindow;

class AcquisitionWorker : public QObject
{
    Q_OBJECT

public:
    AcquisitionWorker(std::shared_ptr<peak::core::DataStream> dataStream,
        peak::common::PixelFormat pixelFormat, QSize imageSize);
    ~AcquisitionWorker() override = default;

    void Stop();

public slots:
    void Start();

private:
    std::shared_ptr<peak::core::DataStream> m_dataStream;
    peak::common::PixelFormat m_outputPixelFormat;
    std::atomic<bool> m_running{true};
    bool m_customNodesAvailable{false};
    FrameStatistics m_statistics{};
    QSize m_size{};
    peak::pipeline::DefaultPipeline m_pipeline;

signals:
    void ImageReceived(QImage image);
    void UpdateCounters(FrameStatistics statistics);
};

#endif // ACQUISITIONWORKER_H
