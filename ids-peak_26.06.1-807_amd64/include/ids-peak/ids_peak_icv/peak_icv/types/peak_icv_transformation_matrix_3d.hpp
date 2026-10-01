/*!
 * \file    peak_icv_transformation_matrix_3d.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-03-06
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_matrix.hpp>

namespace peak
{
namespace icv
{


/*!
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief A transformation matrix is a square matrix that, when multiplied by the coordinates of a geometric object, changes the position, orientation, or size of the object.
 *
 * \since ids_peak_icv 1.1
 */
class TransformationMatrix3D : public Matrix<float, 4, 4>
{
public:
    using Matrix<float, 4, 4>::Matrix; // NOLINT
};

} /* namespace icv */
} /* namespace peak */
