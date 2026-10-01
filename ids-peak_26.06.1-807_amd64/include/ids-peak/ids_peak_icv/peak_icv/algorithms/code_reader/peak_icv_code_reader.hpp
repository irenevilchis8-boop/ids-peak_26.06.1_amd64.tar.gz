/*!
 * \file    peak_icv_code_reader.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-12-22
 * \since   1.2
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once
#include <peak_icv/algorithms/code_reader/peak_icv_code_reader_result.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/code_reader/peak_icv_code_reader.h>
#include <algorithm>

namespace peak
{
namespace icv
{
namespace experimental
{

/*!
 * \ingroup ids_peak_icv_cpp_code_reader
 *
 * \brief Class to read codes from an image
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
class CodeReader
{
public:
    /*!
     * \brief Creates an instance of a code reader
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReader();
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    ~CodeReader();

    CodeReader(const CodeReader& other) = delete;
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReader(CodeReader&& other) noexcept;
    CodeReader& operator=(const CodeReader& other) = delete;
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReader& operator=(CodeReader&& other) noexcept;

    /*!
     * \brief Retrieves the number of configured code types.
     *
     * When no explicit code types are set via \ref setCodeTypesToDetect,
     * the implementation-defined default set is active.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    PEAK_COMMON_NO_DISCARD std::vector<CodeType> GetCodeTypesToDetect() const;

    /*!
     * \brief Sets the allowed code types for detection and decoding.
     *
     * Restricts the Code Reader to the provided list of \ref CodeType values.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    void setCodeTypesToDetect(const std::vector<CodeType>& codeTypesToDetect) const;

    /*!
     * \brief Detects and decodes codes in an input image.
     *
     * Attempts to find codes of the configured types in \p image and decodes their payload.
     *
     * \return The found and decoded Codes in a \ref CodeReaderResult
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    PEAK_COMMON_NO_DISCARD std::vector<CodeReaderResult> DetectAndDecode(const Image& image) const;

    /*!
     * \brief Sets the maximum number of codes to detect per call.
     *
     * Limits how many codes the detector will return for a single invocation of
     * \ref DetectAndDecode. This can be used to cap runtime and memory usage in scenarios with many codes present.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    void SetMaximumNumberOfCodesToDetect(size_t count) const;
    /*!
     * \brief Retrieves the maximum number of codes to detect per call.
     *
     * Returns the current limit configured via \ref SetMaximumNumberOfCodesToDetect.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    PEAK_COMMON_NO_DISCARD size_t GetMaximumNumberOfCodesToDetect() const;

private:
    peak_icv_code_reader_handle m_handle;

    static peak_icv_code_reader_handle CreateFromHandle();
};

inline CodeReader::CodeReader(CodeReader&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
}

inline CodeReader& CodeReader::operator=(CodeReader&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
    }

    return *this;
}

inline peak_icv_code_reader_handle CodeReader::CreateFromHandle()
{
    peak_icv_code_reader_handle handle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_Create(&handle);
    });
    return handle;
}

inline CodeReader::CodeReader()
    : m_handle{ CreateFromHandle() }
{}

inline CodeReader::~CodeReader()
{
    std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_Destroy(m_handle);
}

inline std::vector<CodeType> CodeReader::GetCodeTypesToDetect() const
{
    size_t codeTypesCount{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_GetCodeTypesGetCount(m_handle, &codeTypesCount);
    });

    std::vector<peak_icv_code_type> cTypes(codeTypesCount);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_GetCodeTypes(m_handle, cTypes.data(), codeTypesCount);
    });

    std::vector<CodeType> result;
    result.reserve(cTypes.size());
    std::transform(cTypes.begin(), cTypes.end(), std::back_inserter(result), [](const auto& cType) {
        return static_cast<CodeType>(cType);
    });
    return result;
}

inline void CodeReader::setCodeTypesToDetect(const std::vector<CodeType>& codeTypesToDetect) const
{
    std::vector<peak_icv_code_type> cTypes;
    cTypes.reserve(codeTypesToDetect.size());
    std::transform(codeTypesToDetect.begin(), codeTypesToDetect.end(), std::back_inserter(cTypes), [](const auto& cType) {
        return static_cast<peak_icv_code_type>(cType);
    });

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_SetCodeTypes(m_handle, cTypes.data(), cTypes.size());
    });
}

inline std::vector<CodeReaderResult> CodeReader::DetectAndDecode(const Image& image) const
{
    std::vector<peak_icv_code_reader_result_handle> result_handles(GetMaximumNumberOfCodesToDetect(), PEAK_ICV_INVALID_HANDLE);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Array_Create(result_handles.data(), result_handles.size());
    });
    try
    {
        size_t found_count{};
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_DetectAndDecode(m_handle,
                peak::common::detail::BackendAccessor<Image>::BackendHandle(image), result_handles.data(), result_handles.size(),
                &found_count);
        });
        for (size_t i = found_count; i < result_handles.size(); ++i)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Destroy(result_handles[i]);
            });
        }
        result_handles.resize(found_count);
    }
    catch (const std::exception&)
    {
        for (auto& result_handle : result_handles)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Destroy(result_handle);
            });
        }
        throw;
    }
    return peak::common::detail::BackendAccessor<CodeReaderResult>::CreateInstances(result_handles);
}

inline void CodeReader::SetMaximumNumberOfCodesToDetect(size_t count) const
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect(m_handle, count);
    });
}

inline size_t CodeReader::GetMaximumNumberOfCodesToDetect() const
{
    size_t count{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect(m_handle, &count);
    });
    return count;
}

} // namespace experimental
} // namespace icv 
} // namespace peak
