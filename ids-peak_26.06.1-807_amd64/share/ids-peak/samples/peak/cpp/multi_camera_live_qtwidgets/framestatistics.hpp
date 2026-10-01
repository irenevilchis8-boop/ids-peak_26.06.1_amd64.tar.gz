/*!
* \brief   Frame statistic data type
*
* Copyright (C) 2023 - 2026, IDS Imaging Development Systems GmbH.
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

#ifndef FRAMESTATISTICS_HPP
#define FRAMESTATISTICS_HPP

#include <QObject>

struct FrameStatistics
{
    qint64 frameTime_ms{};
    qint64 conversionTime_ms{};
    quint64 frameCounter{};
    quint64 errorCounter{};
    quint32 incomplete{};
    quint32 dropped{};
    quint32 lost{};
    bool showCustomNodes{};
};

Q_DECLARE_METATYPE(FrameStatistics)

#endif // FRAMESTATISTICS_HPP
