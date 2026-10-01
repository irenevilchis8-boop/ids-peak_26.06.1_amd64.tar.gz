/*!
 * \file    peak_icv_calibration_parameters_writer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
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
 * \brief Class for writing calibration parameters to file.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationParametersWriter
{
public:
    /*!
     * \brief Saves calibration parameters to a JSON file for later use.
     *
     * \param[in] filePath                    An existing file path to save the calibration parameters to.
     * \param[in] calibrationParameters       The calibration parameters to be saved.
     *
     * \throws IOException If the specified file path is invalid or you lack the necessary permissions.
     *
     * \since ids_peak_icv 1.1
     */
    void Write(const std::string& filePath, const CalibrationParameters& calibrationParameters) const;
};

inline void CalibrationParametersWriter::Write(const std::string& filePath, const CalibrationParameters& calibrationParameters) const
{
    const auto data = peak::common::detail::BackendAccessor<CalibrationParameters>::CreateCType(calibrationParameters);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_CalibrationParameters_SaveToFile(data, sizeof(data), filePath.c_str(), {});
    });
}


} /* namespace icv */
} /* namespace peak */
