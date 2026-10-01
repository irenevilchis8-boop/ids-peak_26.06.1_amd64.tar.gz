/*!
 * \file    peak_icv_response_curve.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-14
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */
#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv_c/algorithms/hdr/peak_icv_response_curve.h>
#include <peak_icv_c/backend/peak_icv_dll_defines.h>

#include <string>
#include <tuple>

namespace peak
{
namespace icv
{

/*!
 * A Camera Response Curve defines the mathematical relationship between the
 * true physical scene radiance (light intensity) and the digital pixel values
 * captured by the camera sensor. Because most sensors apply a non-linear
 * transformation to compress dynamic range, this curve must be explicitly known
 * or estimated to linearize the image data before combining multiple exposures
 * into a High Dynamic Range (HDR) image.
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_cpp_hdr
 */
class ResponseCurve
    : detail::IBackendAccessible<ResponseCurve>
    , detail::IBackendExchangeable<ResponseCurve>
{
public:
    /*!
     * \param filename
     *      Path to an existing response curve JSON file.
     *
     * \throws InvalidConfigurationException
     * \throws IOException
     * \throws CorruptedException
     *
     * \since ids_peak_icv 1.4
     */
    explicit ResponseCurve(const std::string& filename);

    /*!
     * \since ids_peak_icv 1.4
     */
    ResponseCurve(const ResponseCurve& other);

    /*!
     * \since ids_peak_icv 1.4
     */
    ResponseCurve(ResponseCurve&& other) noexcept;

    /*!
     * \since ids_peak_icv 1.4
     */
    ResponseCurve& operator=(const ResponseCurve& other);

    /*!
     * \since ids_peak_icv 1.4
     */
    ResponseCurve& operator=(ResponseCurve&& other) noexcept;

    /*!
     * \since ids_peak_icv 1.4
     */
    bool operator==(const ResponseCurve& other) const;

    /*!
     * \since ids_peak_icv 1.4
     */
    ~ResponseCurve() override;

private:
    friend peak::common::detail::BackendAccessor<ResponseCurve>;

    ResponseCurve();
    explicit ResponseCurve(peak_icv_hdr_response_curve_handle regionHandle) noexcept;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<ResponseCurve> GetHandle() const override;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<ResponseCurve>* GetHandleAddress() override;

    peak_icv_hdr_response_curve_handle m_handle{};
};

inline ResponseCurve::ResponseCurve(const std::string& filename)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_CreateFromFile(&m_handle, filename.c_str());
    });
}

inline ResponseCurve::ResponseCurve(const ResponseCurve& other)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_IncreaseUseCount(other.m_handle);
    });
    m_handle = other.m_handle;
}

inline ResponseCurve::ResponseCurve(ResponseCurve&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;
}

inline ResponseCurve& ResponseCurve::operator=(const ResponseCurve& other)
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_Destroy(m_handle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
    }

    return *this;
}

inline ResponseCurve& ResponseCurve::operator=(ResponseCurve&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_Destroy(m_handle);
            });
        }

        m_handle = other.m_handle;
        other.m_handle = nullptr;
    }

    return *this;
}

inline bool ResponseCurve::operator==(const ResponseCurve& other) const
{
    bool isEqual{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_Compare(m_handle, other.m_handle, &isEqual);
    });

    return isEqual;
}

inline detail::handle_of_t<ResponseCurve> ResponseCurve::GetHandle() const
{
    return m_handle;
}

inline detail::handle_of_t<ResponseCurve>* ResponseCurve::GetHandleAddress()
{
    return &m_handle;
}

inline ResponseCurve::~ResponseCurve()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_Destroy(m_handle);
    }
}

inline ResponseCurve::ResponseCurve()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_Create(&m_handle);
    });
}

inline ResponseCurve::ResponseCurve(const peak_icv_hdr_response_curve_handle regionHandle) noexcept
    : m_handle(regionHandle)
{}

} // namespace icv 
} // namespace peak
