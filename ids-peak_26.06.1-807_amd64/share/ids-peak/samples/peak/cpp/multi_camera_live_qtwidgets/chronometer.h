/*!
 * \brief   The Chronometer class is used to simplify time measurement.
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

#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <chrono>


class Chronometer
{

public:
    Chronometer();
    ~Chronometer();

    void Start();
    double GetTimeSinceStart_ms();

private:
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_end;
    std::chrono::duration<double> m_diff;
};

#endif // CHRONOMETER_H
