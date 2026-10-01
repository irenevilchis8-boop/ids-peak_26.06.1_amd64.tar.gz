/*!
 * \file    peak_common_defines.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-11-13
 * \since   ids_peak_common 1.1
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

// clang-format off
#define PEAK_COMMON_CPP_STANDARD_14 201402L
#define PEAK_COMMON_CPP_STANDARD_17 201702L
// clang-format on

#ifdef __has_c_attribute
#    define PEAK_COMMON_has_c_attribute(x) __has_c_attribute(x)
#else
#    define PEAK_COMMON_has_c_attribute(x) 0
#endif

#if defined(__cplusplus)
#    define PEAK_COMMON_CPP_STANDARD __cplusplus
#elif defined(_MSVC_LANG)
#    define PEAK_COMMON_CPP_STANDARD _MSVC_LANG
#endif

#if defined(_MSC_VER)
#    define PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 4'996))
#    define PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS   __pragma(warning(pop))
#elif defined(__clang__) || defined(__GNUC__)
#    define PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS \
        _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#    define PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS _Pragma("GCC diagnostic pop")
#else
#    define PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS
#    define PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS
#endif

#if !defined(PEAK_COMMON_NO_WARN_DEPRECATED)                                                                   \
    && ((defined(PEAK_COMMON_CPP_STANDARD) && PEAK_COMMON_CPP_STANDARD >= PEAK_COMMON_CPP_STANDARD_14) \
        || PEAK_COMMON_has_c_attribute(deprecated))
/*!
 * \ingroup ids_peak_common_detail
 * \brief Compatability macro for the deprecated attribute
 *
 * On C++ 14 / C23 or newer this will evaluate to [[deprecated]],
 * which will warn when compiling a function, that is annotated with this define.
 * \param MESSAGE Helpful message to explain deprecation.
 */
#    define PEAK_COMMON_DEPRECATED_MSG(MESSAGE) [[deprecated(MESSAGE)]]
#elif !defined(PEAK_COMMON_NO_WARN_DEPRECATED) && (defined(__clang__) || defined(__GNUC__) || defined(__GNUG__))
#    define PEAK_COMMON_DEPRECATED_MSG(MESSAGE) __attribute__((deprecated(MESSAGE)))
#else
#    define PEAK_COMMON_DEPRECATED_MSG(MESSAGE)
#endif

#if !defined(PEAK_COMMON_NO_WARN_DEPRECATED) && defined(PEAK_COMMON_CPP_STANDARD) \
    && PEAK_COMMON_CPP_STANDARD >= PEAK_COMMON_CPP_STANDARD_17
/*!
 * \ingroup ids_peak_common_detail
 * \brief Compatability macro for the deprecated attribute
 *
 * On C++ 17 / C23 or newer this will evaluate to [[deprecated]],
 * which will warn when compiling a function, that is annotated with this define.
 * \param MESSAGE Helpful message to explain deprecation.
 */
#    define PEAK_COMMON_DEPRECATED_ENUM_MSG(MESSAGE) [[deprecated(MESSAGE)]]
#elif !defined(PEAK_COMMON_NO_WARN_DEPRECATED) && (defined(__clang__) || defined(__GNUC__) || defined(__GNUG__))
#    define PEAK_COMMON_DEPRECATED_ENUM_MSG(MESSAGE) __attribute__((deprecated(MESSAGE)))
#else
#    define PEAK_COMMON_DEPRECATED_ENUM_MSG(MESSAGE)
#endif

#if (defined(PEAK_COMMON_CPP_STANDARD) && PEAK_COMMON_CPP_STANDARD >= PEAK_COMMON_CPP_STANDARD_17) \
    || PEAK_COMMON_has_c_attribute(nodiscard)
/*!
 * \ingroup ids_peak_common_detail
 * \brief Compatability macro for the nodiscard attribute
 *
 * On C++ 17 / C23 or newer, this will evaluate to `[[nodiscard]]`.
 * For older versions, it will use a compiler-specific equivalent if supported,
 * otherwise it will evaluate to nothing.
 */
#    define PEAK_COMMON_NO_DISCARD [[nodiscard]]
#elif defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#    define PEAK_COMMON_NO_DISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
#    include <sal.h>
#    define PEAK_COMMON_NO_DISCARD _Check_return_
#else
#    define PEAK_COMMON_NO_DISCARD
#endif

#if (defined(PEAK_COMMON_CPP_STANDARD) && PEAK_COMMON_CPP_STANDARD >= PEAK_COMMON_CPP_STANDARD_17) \
    || PEAK_COMMON_has_c_attribute(maybe_unused)
/*!
 * \ingroup ids_peak_common_detail
 * \brief Compatability macro for the maybe_unused attribute
 *
 * On C++ 17 / C23 or newer, this will evaluate to `[[maybe_unused]]`.
 * For older versions, it will use a compiler-specific equivalent if supported,
 * otherwise it will evaluate to nothing.
 */
#    define PEAK_COMMON_MAYBE_UNUSED [[maybe_unused]]
#elif defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#    define PEAK_COMMON_MAYBE_UNUSED __attribute__((unused))
#else
#    define PEAK_COMMON_MAYBE_UNUSED
#endif
