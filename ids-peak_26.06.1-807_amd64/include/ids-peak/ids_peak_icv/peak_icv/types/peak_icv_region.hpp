/*!
 * \file    peak_icv_region.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_icv/algorithms/transformations/peak_icv_interpolation.hpp>
#include <peak_icv/painting/peak_icv_drawable.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief Represents a region defined by a set of points in the image plane.
 *
 * The Region class models a geometric area within an image,
 * represented as a collection of discrete points in 2D image coordinates.
 * It serves as a logical grouping of image locations,
 * which may be used for selection, analysis, or rendering purposes.
 *
 * \anchor Region_painting
 * ### Painting Behavior
 *
 * The Region class implements its own drawing logic via the IDrawable interface.
 * When triggered by the Painter, it paints itself onto the target image by
 * rendering only the points that fall within the image bounds.
 *
 * - Points inside the image are painted.
 * - Points outside the image boundaries are silently ignored.
 * - If the Region is empty (i.e., contains no points),
 *   the image remains unmodified,
 *   and the paint operation completes successfully without any effect.
 *
 * \see \ref concept_type_region "Concept: Region",
 *      which defines the structure and properties of a region.
 *
 * \since ids_peak_icv 1.1
 */
class Region final
    : public IDrawable
    , private detail::IBackendAccessible<Region>
    , private detail::IBackendExchangeable<Region>
{
public:
    /*!
     * \brief Creates an empty Region
     *
     * \since ids_peak_icv 1.1
     */
    Region();

    /*!
     * \brief Creates a region from a collection of points
     *
     * \since ids_peak_icv 1.1
     */
    explicit Region(const std::vector<peak::common::Point>& points);

    /*!
     * \brief Creates a region from a Rectangle
     *
     * \since ids_peak_icv 1.1
     */
    explicit Region(const peak::common::Rectangle& rect);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    ~Region() override;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Region(const Region& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Region(Region&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Region& operator=(const Region& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Region& operator=(Region&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    bool operator==(const Region& rhs) const;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    bool operator!=(const Region& rhs) const;

    /*!
     * \brief Returns the points from a region.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<peak::common::Point> GetPoints() const;

    /*!
     * \brief Calculates the connected components of the region.
     *
     * The 8-neighborhood is used to determine the components.
     *
     * \see \ref concept_region_connected-components
     *
     * \return Returns the connected components of the region as a region vector.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<Region> GetConnectedComponents() const;

    /*!
     * \brief Calculates the area of a region. The area is the number of pixels in the region.
     *
     * \return Returns the area of a region.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD size_t GetArea() const;

    /*!
     * \brief Calculates the center of gravity of a region.
     *
     * \return Returns the center of gravity as a floating point.
     *
     * \throws MathErrorException The center of gravity could not be calculated.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::PointF GetCenterOfGravity() const;

    /*!
     * \brief Calculates the intersection of two regions.
     *
     * \see \ref guide_region_intersection
     *
     * \return Returns the intersection of two regions.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Intersection(const Region& other) const;

    /*!
     * \brief Calculates the difference of two regions.
     *
     * \see \ref guide_region_difference
     *
     * \return Returns the difference of two regions.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Difference(const Region& other) const;

    /*!
     * \brief Calculates the union of two regions.
     *
     * \see \ref guide_region_union
     *
     * \return Returns the united region.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Union(const Region& other) const;

    /*!
     * \brief Performs morphological dilation on the input region using the specified structuring element.
     *
     * The reference point of the structuring element is at (0, 0).
     *
     * \return Returns the dilated region.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Dilation(const Region& structuringElement) const;

    /*!
     * \brief Performs morphological erosion on the input region using the specified structuring element.
     *
     * The reference point of the structuring element is at (0, 0).
     *
     * \return Returns the eroded region.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Erosion(const Region& structuringElement) const;

    /*!
     * \brief Returns a scaled region.
     *
     * The \p inputSize typically refers to the dimensions of the original image in pixels
     * from which the region was derived (e.g. during segmentation).
     * This is the coordinate space in which the region was initially defined.
     * The size must be at least as large as the extent of the region.
     *
     * The \p outputSize represents the dimensions of the target image in pixels
     * where the region will be mapped or rendered after scaling or transformation.
     *
     * Ensure that any coordinate or size transformations account for the difference
     * between input and output dimensions to maintain spatial consistency.
     *
     * \param inputSize     The size in pixels based on the original image.
     * \param outputSize    The size in pixels of a corresponding image to which the original region is scaled.
     * \param interpolation The interpolation method used to scale the image.
     *
     * \return The scaled region.
     *
     * \throws NotPossibleException The region extent is greater than the given inputSize
     *                              or the given outputSize is empty (i.e. width × height == 0).
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region Scale(const peak::common::Size& inputSize, const peak::common::Size& outputSize,
        const Interpolation& interpolation = Interpolation::NearestNeighbor) const;

protected:
    void Draw(Image& image, const detail::DrawingOptions& options) const override;

private:
    friend peak::common::detail::BackendAccessor<Region>;

    explicit Region(peak_icv_region_handle regionHandle) noexcept;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Region> GetHandle() const override;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Region>* GetHandleAddress() override;

    peak_icv_region_handle m_regionHandle{};
};

} /* namespace icv */
} /* namespace peak */

#include <peak_icv/types/detail/peak_icv_region.ipp>
