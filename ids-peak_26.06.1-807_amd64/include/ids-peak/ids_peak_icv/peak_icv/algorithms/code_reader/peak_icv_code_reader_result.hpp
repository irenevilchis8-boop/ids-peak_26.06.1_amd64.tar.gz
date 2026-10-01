/*!
 * \file    peak_icv_code_reader_result.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-12-22
 * \since   1.2
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once
#include <peak_icv/algorithms/code_reader/peak_icv_code_types.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/code_reader/peak_icv_code_reader.h>
#include <string>
#include <vector>

namespace peak
{
namespace icv
{
namespace experimental
{
/*!
 * \ingroup ids_peak_icv_cpp_code_reader
 *
 * \brief Class that represents a code that was found in an image
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
class CodeReaderResult : public detail::IBackendAccessible<CodeReaderResult>
{
public:
    /*!
     * \brief Creates an empty instance of a code result
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReaderResult();
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    ~CodeReaderResult() override;

    CodeReaderResult(const CodeReaderResult& other) = delete;
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReaderResult(CodeReaderResult&& other) noexcept;
    CodeReaderResult& operator=(const CodeReaderResult& other) = delete;
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    CodeReaderResult& operator=(CodeReaderResult&& other) noexcept;

    /*!
     * \brief Provides the decoded text of the code
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    PEAK_COMMON_NO_DISCARD std::string GetText() const;

    /*!
     * \brief Provides the type of the code
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    PEAK_COMMON_NO_DISCARD CodeType GetType() const;

private:
    friend peak::common::detail::BackendAccessor<CodeReaderResult>;
    explicit CodeReaderResult(peak_icv_code_reader_result_handle handle);

    PEAK_COMMON_NO_DISCARD peak_icv_code_reader_result_handle GetHandle() const override;
    static peak_icv_code_reader_result_handle createHandle();
    peak_icv_code_reader_result_handle m_handle;
};

inline CodeReaderResult::CodeReaderResult(CodeReaderResult&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
}

inline CodeReaderResult& CodeReaderResult::operator=(CodeReaderResult&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
    }

    return *this;
}

inline CodeReaderResult::CodeReaderResult(peak_icv_code_reader_result_handle handle)
    : m_handle{ handle }
{}

inline peak_icv_code_reader_result_handle CodeReaderResult::GetHandle() const
{
    return m_handle;
}

inline peak_icv_code_reader_result_handle CodeReaderResult::createHandle()
{
    peak_icv_code_reader_result_handle handle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Create(&handle);
    });
    return handle;
}

inline CodeReaderResult::CodeReaderResult()
    : m_handle{ createHandle() }
{}

inline CodeReaderResult::~CodeReaderResult()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_Destroy(m_handle);
    }
}

inline std::string CodeReaderResult::GetText() const
{
    size_t text_size_in_bytes{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes(m_handle, &text_size_in_bytes);
    });

    std::vector<char> data(text_size_in_bytes);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_GetText(m_handle, data.data(), data.size());
    });

    return { data.begin(), data.end() - 1 };
}

inline CodeType CodeReaderResult::GetType() const
{
    peak_icv_code_type cType{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_BarcodeReaderResult_GetType(m_handle, &cType);
    });

    return static_cast<CodeType>(cType);
}

} // namespace experimental
} // namespace icv 
} // namespace peak
