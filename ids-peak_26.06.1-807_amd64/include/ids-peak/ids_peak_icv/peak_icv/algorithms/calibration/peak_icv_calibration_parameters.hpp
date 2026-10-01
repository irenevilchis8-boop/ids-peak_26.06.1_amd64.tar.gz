/*!
 * \file    peak_icv_calibration_parameters.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_extrinsic_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_parameters.h>
#include <peak_icv_c/binary/peak_icv_binary_validator.h>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Holds a complete set of camera calibration parameters, including both intrinsic and extrinsic data.
 *
 * The CalibrationParameters class represents a minimal dataset
 * derived from a full CalibrationResult.
 * It includes only the essential information
 * required to apply the intrinsic and extrinsic calibration to images or depth maps.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationParameters
{
public:
    /*!
     * \brief Constructs a CalibrationParameters instance by loading data from a JSON file.
     *
     * Allows calibration parameters to be loaded from a file,
     * avoiding the need for recalibration
     * and enabling consistent application of intrinsic and extrinsic camera parameters across sessions.
     *
     * The file may contain either a CalibrationParameters object or a full CalibrationResult.
     * From a full CalibrationResult, only the calibration parameters are extracted as follows:
     * - **Intrinsic parameters**:
     *   Always extracted from the CalibrationResult.
     * - **Extrinsic parameters**:
     *   If the CalibrationResult contains a single calibration view,
     *   the extrinsic parameters from that view are used;
     *   if multiple calibration views are present (e.g., from a camera calibration),
     *   the extrinsic parameters are set to the identity matrix.
     *
     * \param[in] filePath Path to the JSON file containing calibration parameters.
     *
     * \throws IOException        If the given file_path does not exist,
     *                            or the permissions are not sufficient to read it.
     * \throws CorruptedException If the file content is corrupted.
     *
     * \since ids_peak_icv 1.1
     */
    explicit CalibrationParameters(const std::string& filePath);

    /*!
     * \brief Constructs a CalibrationParameters instance from the provided intrinsic and extrinsic parameters.
     *
     * \param[in] intrinsicParameters The intrinsic camera parameters.
     * \param[in] extrinsicParameters The extrinsic camera parameters.
     *
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationParameters(const IntrinsicParameters& intrinsicParameters, const ExtrinsicParameters& extrinsicParameters);

    /*!
     * \brief Constructs a CalibrationParameters instance from binary data
     *        that have been read from the camera memory.
     *
     * \param[in] binaryData The binary data.
     *
     * \throws CorruptedException If the binary data is corrupted.
     *
     * \since ids_peak_icv 1.1
     */

    template <class Container
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename = std::enable_if_t<detail::is_contiguous_container<Container, uint8_t>::value>
        /// @endcond
        >
    explicit CalibrationParameters(const Container& binaryData)
        : CalibrationParameters{ CreateFromBinary(binaryData) }
    {}

    /*!
     * \brief Retrieves the intrinsic camera parameters.
     *
     * \return The intrinsic camera parameters.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD IntrinsicParameters GetIntrinsicParameters() const;

    /*!
     * \brief Retrieves the extrinsic camera parameters.
     *
     * \return The extrinsic camera parameters.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD ExtrinsicParameters GetExtrinsicParameters() const;

    /*!
     * \brief Sets the extrinsic camera parameters.
     *
     * \param[in] extrinsicParameters The extrinsic camera parameters.
     *
     * \since ids_peak_icv 1.2
     */
    void SetExtrinsicParameters(const ExtrinsicParameters& extrinsicParameters);

    /*!
     * \brief Converts CalibrationParameters to binary data that can be written to the camera memory.
     *
     * \return The binary data.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<uint8_t> ToBinary() const;


private:
    friend peak::common::detail::BackendAccessor<CalibrationParameters>;
    friend class CalibrationResult;

    explicit CalibrationParameters(const peak_icv_calibration_parameters& calibrationParameters);
    explicit operator peak_icv_calibration_parameters() const;
    static peak_icv_calibration_parameters LoadFromFile(const std::string& filePath);

    IntrinsicParameters m_intrinsicParameters;
    ExtrinsicParameters m_extrinsicParameters;

    template <class Container, typename = std::enable_if_t<detail::is_contiguous_container<Container, uint8_t>::value>>
    static peak_icv_calibration_parameters CreateFromBinary(const Container& binaryData)
    {
        bool isValid{};
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_ValidateBinary(binaryData.data(), binaryData.size(), &isValid);
        });

        if (!isValid)
        {
            throw CorruptedException("The given binary data is invalid");
        }

        peak_icv_calibration_parameters calibration_parameters{};
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_CalibrationParameters_CreateFromBinary(
                binaryData.data(), binaryData.size(), &calibration_parameters, sizeof(peak_icv_calibration_parameters));
        });

        return calibration_parameters;
    }
};

inline CalibrationParameters::CalibrationParameters(const std::string& filePath)
    : CalibrationParameters(LoadFromFile(filePath))
{}

inline CalibrationParameters::CalibrationParameters(const peak_icv_calibration_parameters& calibrationParameters)
    : m_intrinsicParameters{ peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateInstance(
          calibrationParameters.intrinsic_parameters) }
    , m_extrinsicParameters{ peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateInstance(
          calibrationParameters.extrinsic_parameters) }
{}

inline CalibrationParameters::CalibrationParameters(
    const IntrinsicParameters& intrinsicParameters, const ExtrinsicParameters& extrinsicParameters)
    : m_intrinsicParameters{ intrinsicParameters }
    , m_extrinsicParameters{ extrinsicParameters }
{}

inline CalibrationParameters::operator peak_icv_calibration_parameters() const
{
    return { peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(m_intrinsicParameters),
        peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateCType(m_extrinsicParameters) };
}

inline IntrinsicParameters CalibrationParameters::GetIntrinsicParameters() const
{
    return m_intrinsicParameters;
}

inline ExtrinsicParameters CalibrationParameters::GetExtrinsicParameters() const
{
    return m_extrinsicParameters;
}

inline void CalibrationParameters::SetExtrinsicParameters(const ExtrinsicParameters& extrinsicParameters)
{
    m_extrinsicParameters = extrinsicParameters;
}

inline peak_icv_calibration_parameters CalibrationParameters::LoadFromFile(const std::string& filePath)
{
    peak_icv_calibration_parameters parameters{};

    detail::ExecuteAndMapReturnCodes([&parameters, &filePath] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_CalibrationParameters_CreateFromFile(&parameters, sizeof(parameters), filePath.c_str());
    });

    return parameters;
}

inline std::vector<uint8_t> CalibrationParameters::ToBinary() const
{
    peak_icv_calibration_parameters parameters{ peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(
                                                      m_intrinsicParameters),
        peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateCType(m_extrinsicParameters) };


    size_t binarySize{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes(sizeof(parameters), &binarySize);
    });

    std::vector<uint8_t> binary(binarySize);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_CalibrationParameters_ToBinary(parameters, sizeof(parameters), binary.data(), binarySize);
    });

    return binary;
}

} /* namespace icv */
} /* namespace peak */
