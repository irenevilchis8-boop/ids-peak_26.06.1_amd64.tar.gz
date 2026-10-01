/*!
 * \file    peak_icv_response_curve_writer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-14
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */
#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_icv/algorithms/hdr/peak_icv_response_curve.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv_c/algorithms/hdr/peak_icv_response_curve.h>
#include <peak_icv_c/backend/peak_icv_dll_defines.h>

#include <string>

namespace peak
{
namespace icv
{

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_cpp_io
 */
class ResponseCurveWriter
{
public:
    /*!
     * \param filePath
     *     Destination file path for the response curve JSON file.
     *     The .json file extension is automatically added if not provided.
     *
     * \throws InvalidConfigurationException
     * \throws IOException
     *
     * \since ids_peak_icv 1.4
     */
    void Write(const std::string& filePath, const ResponseCurve& responseCurve) const;
};

inline void ResponseCurveWriter::Write(const std::string& filePath, const ResponseCurve& responseCurve) const
{
    const auto curveHandle = peak::common::detail::BackendAccessor<ResponseCurve>::BackendHandle(responseCurve);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_ResponseCurve_SaveToFile(curveHandle, filePath.c_str());
    });
}


} // namespace icv 
} // namespace peak
