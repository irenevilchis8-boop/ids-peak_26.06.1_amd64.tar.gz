/*!
 * \file    peak_icv_extrinsic_parameters.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-26
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/types/peak_icv_transformation_matrix_3d.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h>

namespace peak
{
namespace icv
{


/*!
 * \class ExtrinsicParameters
 * \ingroup ids_peak_icv_cpp_calibration
 * \brief This class stores and provides access to the extrinsic parameters, which include
 *  the translation, rotation, and transformation matrix.
 *
 *  It is a result of the camera calibration or the workspace calibration.
 *
 *  The extrinsic camera parameters describe the transformation between the camera's coordinate system and the world coordinate system.
 *  They can be used to convert points from the world coordinate system into the camera coordinate system.
 *
 * \since ids_peak_icv 1.1
 */
class ExtrinsicParameters
{
public:
    /*!
     * \brief Constructs ExtrinsicParameters from a rotation and a translation vector.
     *
     * \param[in] rotation A rotation vector.
     * \param[in] translation A translation vector.
     * \since ids_peak_icv 1.1
     */
    explicit ExtrinsicParameters(const PointXYZ& rotation, const PointXYZ& translation);

    /*!
     * \brief Provides the translation
     *
     * \return Returns the translation.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD PointXYZ GetTranslation() const;

    /*!
     * \brief Provides the rotation
     *
     * \return Returns the rotation.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD PointXYZ GetRotation() const;


    /*!
     * \brief Calculates the transformation matrix based on rotation and translation
     *
     * \return Returns the transformation matrix.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD TransformationMatrix3D GetTransformationMatrix() const;


private:
    friend peak::common::detail::BackendAccessor<ExtrinsicParameters>;

    explicit ExtrinsicParameters(const peak_icv_extrinsic_parameters& extrinsicParameters);
    explicit operator peak_icv_extrinsic_parameters() const;

    peak_icv_extrinsic_parameters m_extrinsicParameters;
};

inline ExtrinsicParameters::ExtrinsicParameters(const PointXYZ& rotation, const PointXYZ& translation)
    : m_extrinsicParameters{ { rotation.GetX(), rotation.GetY(), rotation.GetZ(), {} },
        { translation.GetX(), translation.GetY(), translation.GetZ(), {} } }
{}

inline ExtrinsicParameters::ExtrinsicParameters(const peak_icv_extrinsic_parameters& extrinsicParameters)
    : m_extrinsicParameters{ extrinsicParameters }
{}

inline PointXYZ ExtrinsicParameters::GetTranslation() const
{
    return peak::common::detail::BackendAccessor<PointXYZ>::CreateInstance(m_extrinsicParameters.translation);
}

inline PointXYZ ExtrinsicParameters::GetRotation() const
{
    return peak::common::detail::BackendAccessor<PointXYZ>::CreateInstance(m_extrinsicParameters.rotation);
}

inline ExtrinsicParameters::operator peak_icv_extrinsic_parameters() const
{
    return m_extrinsicParameters;
}

inline TransformationMatrix3D ExtrinsicParameters::GetTransformationMatrix() const
{
    peak_icv_transformation_matrix_3d transformationMatrixC{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix(
            m_extrinsicParameters, sizeof(m_extrinsicParameters), &transformationMatrixC);
    });

    TransformationMatrix3D transformationMatrixCpp;
    const auto* cArrayBegin = &transformationMatrixC[0][0];
    const auto* cArrayEnd = (&transformationMatrixC[3][3]) + 1;
    std::copy(cArrayBegin, cArrayEnd, transformationMatrixCpp.begin());

    return transformationMatrixCpp;
}

} /* namespace icv */
} /* namespace peak */
