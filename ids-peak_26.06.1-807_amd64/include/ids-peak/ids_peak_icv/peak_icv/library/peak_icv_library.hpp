/*!
 * \file    peak_icv_library.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv_c/library/peak_icv_library.h>

namespace peak
{
namespace icv
{
namespace library
{

/*!
 * \ingroup ids_peak_icv_cpp_library
 *
 * \brief Initializes the IDS peak ICV library
 *
 * This function must be called prior to any other function call,
 * otherwise no IDS peak ICV function is operable.
 *
 * The function may be called multiple times from a single client process,
 * but note that for each call there has to be a corresponding call to #Exit
 * when closing the library.
 *
 * \note Calling any other function before #Init
 *       will result in an InvalidConfigurationException.
 *
 * \since ids_peak_icv 1.0
 */
inline void Init();

/*!
 * \ingroup ids_peak_icv_cpp_library
 *
 * \brief Deinitializes the IDS peak ICV library
 *
 * This function should be called when no function of the library is needed anymore.
 * It releases all allocated memory
 * and destroys all handles along with their associated resources.
 *
 * Calls to #Init and #Exit are reference counted,
 * so you have to call #Exit as many times as you have called #Init.
 *
 * After the library has been deinitialized,
 * its functions (except for #Init) will not be operable
 * until #Init is called again.
 *
 * \note Calling any other function (except #Init) after calling #Exit
 *       will result in an InvalidConfigurationException.
 *
 * \throws InvalidConfigurationException if the library is not initialized.
 *
 * \since ids_peak_icv 1.0
 */
inline void Exit();
} // namespace library

namespace library
{
inline void Init()
{
    detail::ExecuteAndMapReturnCodes(PEAK_ICV_C_ABI_PREFIX peak_icv_Init);
}

inline void Exit()
{
    detail::ExecuteAndMapReturnCodes(PEAK_ICV_C_ABI_PREFIX peak_icv_Exit);
}

} // namespace library

} /* namespace icv */
} /* namespace peak */
