/*!
 * \file    peak_icv_calibration_plate.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-12-10
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_plate.h>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Calibration plate representation
 *        holding the world coordinates of the reference points on a calibration plate.
 *
 * These coordinates are essential for accurate camera calibration.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationPlate : private detail::IBackendAccessible<CalibrationPlate>
{
public:
    /*!
     * \brief Initializes the object by loading world coordinates from a description file.
     *
     * The description file contains the world coordinates of the reference points
     * on a specific calibration plate.
     *
     * Ensure that the description file corresponds to the physical calibration plate
     * used in the setup.
     *
     * \param[in] filePath An existing file path to a calibration plate JSON file.
     *
     * \throws IOException        If the given file_path does not exist,
     *                            or the permissions are not sufficient to read it.
     * \throws CorruptedException If the file cannot be read.
     *
     * \since ids_peak_icv 1.1
     */
    explicit CalibrationPlate(const std::string& filePath);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationPlate(const CalibrationPlate& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationPlate(CalibrationPlate&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationPlate& operator=(const CalibrationPlate& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationPlate& operator=(CalibrationPlate&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    ~CalibrationPlate() override;

private:
    friend peak::common::detail::BackendAccessor<CalibrationPlate>;

    PEAK_COMMON_NO_DISCARD peak_icv_calibration_plate_handle GetHandle() const override;

    peak_icv_calibration_plate_handle m_handle{};
};

inline CalibrationPlate::CalibrationPlate(const std::string& filePath)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_CreateFromFile(&m_handle, filePath.c_str());
    });
}

inline CalibrationPlate::CalibrationPlate(const CalibrationPlate& other)
    : m_handle(other.m_handle)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_IncreaseUseCount(other.m_handle);
    });
}

inline CalibrationPlate::CalibrationPlate(CalibrationPlate&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
}

inline CalibrationPlate& CalibrationPlate::operator=(const CalibrationPlate& other)
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_Destroy(m_handle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
    }
    return *this;
}

inline CalibrationPlate& CalibrationPlate::operator=(CalibrationPlate&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
    }

    return *this;
}

inline CalibrationPlate::~CalibrationPlate()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Plate_Destroy(m_handle);
    }
}

inline peak_icv_calibration_plate_handle CalibrationPlate::GetHandle() const
{
    return m_handle;
}

} /* namespace icv */
} /* namespace peak */
