/*!
 * \file    peak_icv_dll_defines.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-07-23
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#ifndef PEAK_ICV_C_ABI_PREFIX
#    ifdef PEAK_ICV_DYNAMIC_LOADING
#        include <peak_icv/detail/peak_icv_dynamic_loader.h>
#        define PEAK_ICV_C_ABI_PREFIX peak::icv::dynamic::DynamicLoader::
#    else
#        define PEAK_ICV_C_ABI_PREFIX // we could also set ::
#    endif
#endif
