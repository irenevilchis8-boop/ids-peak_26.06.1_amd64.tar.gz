/*!
 * \file    peak_icv_calibration_result_writer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>

#include <string>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_io
 * \brief Class for writing a calibration result to file.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationResultWriter
{
public:
    /*!
     * \brief Saves calibration result to a JSON file for later use.
     *
     * \param[in] filePath          An existing file path to save the calibration result to.
     * \param[in] calibrationResult The calibration result to be saved.
     *
     * \throws IOException If the specified file path is invalid or you lack the necessary permissions.
     *
     * \since ids_peak_icv 1.1
     */
    void Write(const std::string& filePath, const CalibrationResult& calibrationResult) const;
};

inline void CalibrationResultWriter::Write(const std::string& filePath, const CalibrationResult& calibrationResult) const
{
    auto* handle = peak::common::detail::BackendAccessor<CalibrationResult>::BackendHandle(calibrationResult);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_SaveToFile(handle, filePath.c_str(), {});
    });
}
} /* namespace icv */
} /* namespace peak */
