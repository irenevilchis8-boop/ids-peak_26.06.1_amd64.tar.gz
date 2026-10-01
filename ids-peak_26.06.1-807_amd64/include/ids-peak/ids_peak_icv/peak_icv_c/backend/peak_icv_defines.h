/*!
 * \file    peak_icv_defines.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#ifdef __cplusplus
/*!
 * \ingroup ids_peak_icv_cpp
 * \brief Use PEAK_ICV_INVALID_HANDLE to initialize handles.
 */
#    define PEAK_ICV_INVALID_HANDLE nullptr

#else
/*!
 * \ingroup ids_peak_icv_c
 * \brief Use PEAK_ICV_INVALID_HANDLE to initialize handles.
 */
#    define PEAK_ICV_INVALID_HANDLE NULL
#endif

/* Function declaration modifiers */
#if defined(_WIN32)
#    ifndef PEAK_ICV_NO_DECLSPEC_STATEMENTS
#        ifdef PEAK_ICV_EXPORTING
#            define PEAK_ICV_EXPORT __declspec(dllexport)
#        else
#            define PEAK_ICV_EXPORT __declspec(dllimport)
#        endif
#    else
#        define PEAK_ICV_EXPORT
#    endif
#else
#    ifdef PEAK_ICV_EXPORTING
#        define PEAK_ICV_EXPORT __attribute__((visibility("default")))
#    else
#        define PEAK_ICV_EXPORT
#    endif
#endif

// note: The order matters. clang-cl does not compile, when PEAK_COMMON_NO_DISCARD is after PEAK_ICV_EXPORT
#define PEAK_ICV_API_STATUS PEAK_COMMON_NO_DISCARD PEAK_ICV_EXPORT peak_icv_status
#define PEAK_ICV_API_STATUS_DEPRECATED(MESSAGE) \
    PEAK_COMMON_DEPRECATED_MSG(MESSAGE) PEAK_COMMON_NO_DISCARD PEAK_ICV_EXPORT peak_icv_status
