/*!
 * \file    peak_icv_undistortion.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-12-11
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/algorithms/transformations/peak_icv_interpolation.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv/types/peak_icv_undistorted_image.hpp>
#include <peak_icv_c/algorithms/transformations/peak_icv_undistortion.h>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_transformations
 *
 * \brief Represents an undistortion transformation for images.
 *
 * Provides geometric correction
 * to remove lens distortion using intrinsic calibration parameters.
 * The intrinsic parameters can be obtained using `CameraCalibration::Process()`.
 *
 * This class also supports undistorting images with binning factors
 * that differ from those used during calibration,
 * as long as the image metadata includes valid binning information.
 * The binning factor of the image to be undistorted
 * must be greater than or equal
 * to the binning factor of the calibration images.
 *
 * \note
 *   If the metadata of the images to be undistorted
 *   differs from the metadata used during calibration (e.g. due to different binning),
 *   internal parameters may need to be reinitialized.
 *   In such cases, the first call to `Process()` may take longer.
 *   To avoid this,
 *   use a constructor that accepts both calibration parameters and metadata.
 *   When using those constructors,
 *   the provided metadata must match the images to be undistorted.
 *
 * ### Limitations
 * - In-place undistortion is not supported.
 * - Maximum supported image size is 32767 × 32767 pixels.
 *
 * \since ids_peak_icv 1.1
 */
class Undistortion : detail::IBackendAccessible<Undistortion>
{
public:
    /*!
     * \brief Constructs an undistortion using intrinsic parameters.
     *
     * \param[in] intrinsicParameters Intrinsic calibration parameters.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Undistortion(const IntrinsicParameters& intrinsicParameters);

    /*!
     * \brief Constructs an undistortion using intrinsic parameters and metadata.
     *
     * \param[in] intrinsicParameters Intrinsic calibration parameters.
     * \param[in] metadata            Metadata describing capture characteristics.
     *
     * \since ids_peak_icv 1.1
     */
    Undistortion(const IntrinsicParameters& intrinsicParameters, const peak::common::Metadata& metadata);

    /*!
     * \brief Constructs an undistortion using calibration parameters.
     *
     * \param[in] calibrationParameters Calibration parameters.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Undistortion(const CalibrationParameters& calibrationParameters);

    /*!
     * \brief Constructs an undistortion using calibration parameters and metadata.
     *
     * \param[in] calibrationParameters Calibration parameters.
     * \param[in] metadata              Metadata describing capture characteristics.
     *
     * \since ids_peak_icv 1.1
     */
    Undistortion(const CalibrationParameters& calibrationParameters, const peak::common::Metadata& metadata);

    /*!
     * \brief Constructs an undistortion using a calibration result.
     *
     * \param[in] calibrationResult Calibration result.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Undistortion(const CalibrationResult& calibrationResult);

    /*!
     * \brief Constructs an undistortion using a calibration result and metadata.
     *
     * \param[in] calibrationResult Calibration result.
     * \param[in] metadata          Metadata describing capture characteristics.
     *
     * \since ids_peak_icv 1.1
     */
    Undistortion(const CalibrationResult& calibrationResult, const peak::common::Metadata& metadata);

    Undistortion(const Undistortion& other);

    Undistortion(Undistortion&& other) noexcept;

    ~Undistortion() override;

    Undistortion& operator=(const Undistortion& other);

    Undistortion& operator=(Undistortion&& other) noexcept;

    /*!
     * \brief Applies undistortion to the specified image.
     *
     * This function undistorts the image
     * and returns an `UndistortedImage` that includes updated intrinsic parameters.
     *
     * The returned image has the same size and pixel format as the input image.
     *
     * The image region is also undistorted.
     *
     * \note
     *   In the rare case that the Metadata ROI (peak::common::MetadataKey::Roi) is set
     *   such that the principal point of the calibration parameters lies outside the ROI,
     *   invalid data may appear at the image border.
     *   The image region is therefore restricted to points within the valid area.
     *
     * \param[in] image The image to be undistorted.
     *
     * \supportedPixelformats{Undistortion}
     *
     * \return An undistorted image with updated intrinsic parameters.
     *
     * \throws NotPossibleException The image binning factor is too small
     *                              for the undistortion configuration.
     * \throws MismatchException    The input image size or capture information
     *                              does not match the undistortion configuration.
     *
     * \return The undistorted image.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD UndistortedImage Process(const Image& image) const;

    /*!
     * \return The current \ref Interpolation "interpolation method" used by the undistortion.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Interpolation GetInterpolation() const;

    /*!
     * \brief Sets the \ref Interpolation "Interpolation method" used for undistortion.
     *
     * \param[in] interpolation \ref Interpolation "interpolation method" to use.
     *
     * \since ids_peak_icv 1.1
     */
    void SetInterpolation(Interpolation interpolation);

private:
    friend peak::common::detail::BackendAccessor<Undistortion>;

    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Undistortion> GetHandle() const override;

    peak_icv_undistortion_handle m_handle{};
    peak_icv_intrinsic_parameters m_newIntrinsicParameters{};
};

inline Undistortion::Undistortion(const IntrinsicParameters& intrinsicParameters)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Create(&m_handle,
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(intrinsicParameters),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const IntrinsicParameters& intrinsicParameters, const peak::common::Metadata& metadata)
{
    auto metadataGuard = detail::MetadataAdapter::createMetadataHandleGuardFromMetadata(metadata);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_CreateWithImageMetadata(&m_handle, metadataGuard.GetHandle(),
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(intrinsicParameters),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const CalibrationParameters& calibrationParameters)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Create(&m_handle,
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(calibrationParameters.GetIntrinsicParameters()),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const CalibrationParameters& calibrationParameters, const peak::common::Metadata& metadata)
{
    auto metadataGuard = detail::MetadataAdapter::createMetadataHandleGuardFromMetadata(metadata);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_CreateWithImageMetadata(&m_handle, metadataGuard.GetHandle(),
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(calibrationParameters.GetIntrinsicParameters()),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const CalibrationResult& calibrationResult)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Create(&m_handle,
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(
                calibrationResult.GetCalibrationParameters().GetIntrinsicParameters()),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const CalibrationResult& calibrationResult, const peak::common::Metadata& metadata)
{
    auto metadataGuard = detail::MetadataAdapter::createMetadataHandleGuardFromMetadata(metadata);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_CreateWithImageMetadata(&m_handle, metadataGuard.GetHandle(),
            peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(
                calibrationResult.GetCalibrationParameters().GetIntrinsicParameters()),
            sizeof(peak_icv_intrinsic_parameters), &m_newIntrinsicParameters);
    });
}

inline Undistortion::Undistortion(const Undistortion& other)
{
    if (m_handle != other.m_handle)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
        m_newIntrinsicParameters = other.m_newIntrinsicParameters;
    }
}

inline Undistortion::Undistortion(Undistortion&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        m_handle = other.m_handle;
        other.m_handle = nullptr;

        m_newIntrinsicParameters = other.m_newIntrinsicParameters;
    }
}

inline Undistortion::~Undistortion()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Destroy(m_handle);
    }
}

inline Undistortion& Undistortion::operator=(const Undistortion& other)
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Destroy(m_handle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
        m_newIntrinsicParameters = other.m_newIntrinsicParameters;
    }

    return *this;
}

inline Undistortion& Undistortion::operator=(Undistortion&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Destroy(m_handle);
            });
        }

        m_handle = other.m_handle;
        other.m_handle = nullptr;

        m_newIntrinsicParameters = other.m_newIntrinsicParameters;
    }

    return *this;
}

inline UndistortedImage Undistortion::Process(const Image& image) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);

    Image outputImage = peak::common::detail::BackendAccessor<Image>::CreateInstance(image.GetPixelFormat(), image.GetSize(), false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_Process(m_handle, inputImageHandle, outputImageHandle);
    });

    return { outputImage, peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateInstance(m_newIntrinsicParameters) };
}

inline Interpolation Undistortion::GetInterpolation() const
{
    peak_icv_interpolation interpolation;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_GetInterpolation(m_handle, &interpolation);
    });

    return static_cast<Interpolation>(interpolation);
}

inline void Undistortion::SetInterpolation(Interpolation interpolation)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_Undistortion_SetInterpolation(
            m_handle, static_cast<peak_icv_interpolation>(interpolation));
    });
}

inline detail::handle_of_t<Undistortion> Undistortion::GetHandle() const
{
    return m_handle;
}

} /* namespace icv */
} /* namespace peak */
