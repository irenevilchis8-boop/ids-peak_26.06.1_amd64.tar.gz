/*!
 * \file    peak_icv_point_cloud_writer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-30
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_point_cloud_xyz.hpp>
#include <peak_icv/types/peak_icv_point_cloud_xyzi.hpp>

#include <string>

namespace peak
{
namespace icv
{


/*!
 * \ingroup ids_peak_icv_cpp_io
 *
 * \brief Provides functionality to write point clouds to file.
 *
 * \since ids_peak_icv 1.1
 */
class PointCloudWriter
{
public:
    /*!
     * \brief Saves the specified point cloud to a PLY file.
     *
     * The file format is determined
     * by the specified file extension of the file name.
     * Only binary PLY (.ply) is supported.
     *
     * If no extension is provided, `.ply` is appended automatically.
     *
     * \note If a point cloud does not contain any points it cannot be written to file.
     *
     * \param[in] filePath The path of the file to write to, as a UTF-8 encoded string.
     * \param[in] cloud    The point cloud to save.
     *
     * \throws NotSupportedException The specified file extension or point type is not supported or the point cloud is empty.
     * \throws IOException           The specified file path is invalid or lacks write permissions.
     *
     * \since ids_peak_icv 1.1
     */
    template <typename PointCloud>
    void Write(const std::string& filePath, const PointCloud& cloud) const;
};

template <typename PointCloudType>
void PointCloudWriter::Write(const std::string& filePath, const PointCloudType& cloud) const
{
    static_assert(detail::is_pointcloud_v<PointCloudType>, "Write must be called on PointCloud types!");

    auto pointCloudHandle = peak::common::detail::BackendAccessor<PointCloudType>::BackendHandle(cloud);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_SaveToFile(pointCloudHandle, filePath.c_str(), {});
    });
}


} /* namespace icv */
} /* namespace peak */
