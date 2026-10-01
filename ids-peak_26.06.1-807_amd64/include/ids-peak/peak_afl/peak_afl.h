/*!
 * \file    peak_afl.h
 *
 * \brief   C API interface for automatic camera feature control
 *
 * This header provides the complete C API for the auto feature library, enabling
 * automatic control of camera parameters such as brightness, focus, and white balance.
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-11-15
 * \since   1.0
 *
 * Copyright (c) 2022 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 *
 * \see peak_afl.hpp for C++ API
 */

#pragma once

#include <peak_ipl/backend/peak_ipl_backend.h>
#include <peak/backend/peak_backend.h>

/* Function declaration modifiers */
#if defined(_WIN32)
#    ifndef PEAK_AFL_NO_DECLSPEC_STATEMENTS
#        ifdef PEAK_AFL_EXPORTING
#            define PEAK_AFL_EXPORT __declspec(dllexport)
#        else
#            define PEAK_AFL_EXPORT __declspec(dllimport)
#        endif
#    else
#        define PEAK_AFL_EXPORT
#    endif
#    if defined(_M_IX86) || defined(__i386__)
#        define PEAK_AFL_CALLCONV __cdecl
#    else
#        define PEAK_AFL_CALLCONV
#    endif
#else
#    define PEAK_AFL_EXPORT
#    define PEAK_AFL_CALLCONV
#endif

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>

extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

#if !defined(PEAK_AFL_NO_WARN_DEPRECATED)
#    if defined(__cplusplus) && __cplusplus >= 201402L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
        || (defined(_MSVC_LANG) && _MSVC_LANG >= 201402L)
#        define PEAK_AFL_DEPRECATED_ATTR [[deprecated]]
#        define PEAK_AFL_DEPRECATED_ATTR_MSG(X) [[deprecated(X)]]
#        define PEAK_AFL_DEPRECATED(X) X PEAK_AFL_DEPRECATED_ATTR
#        define PEAK_AFL_DEPRECATED_MSG(X, Y) X [[deprecated(Y)]]
#    elif defined(__GNUC__)
#        define PEAK_AFL_DEPRECATED_ATTR __attribute__((deprecated))
#        define PEAK_AFL_DEPRECATED_ATTR_MSG(X) __attribute__((deprecated(X)))
#        define PEAK_AFL_DEPRECATED(X) X PEAK_AFL_DEPRECATED_ATTR
#        define PEAK_AFL_DEPRECATED_MSG(X, Y) X __attribute__((deprecated(Y)))
#    else
#        define PEAK_AFL_DEPRECATED_ATTR
#        define PEAK_AFL_DEPRECATED_ATTR_MSG(X)
#        define PEAK_AFL_DEPRECATED(X) X
#        define PEAK_AFL_DEPRECATED_MSG(X, Y) X
#    endif
#    if defined(__cplusplus) && __cplusplus >= 201703L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
        || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#        define PEAK_AFL_DEPRECATED_ENUM_ATTR [[deprecated]]
#    elif defined(__GNUC__)
#        define PEAK_AFL_DEPRECATED_ENUM_ATTR __attribute__((deprecated))
#    else
#        define PEAK_AFL_DEPRECATED_ENUM_ATTR
#    endif
#else
#    define PEAK_AFL_DEPRECATED_ATTR
#    define PEAK_AFL_DEPRECATED_ENUM_ATTR
#    define PEAK_AFL_DEPRECATED_ATTR_MSG(X)
#    define PEAK_AFL_DEPRECATED(X) X
#    define PEAK_AFL_DEPRECATED_MSG(X, Y) X
#endif

#if defined(_MSC_VER)
#    define PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 4996))
#    define PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS __pragma(warning(pop))
#elif defined(__clang__)
#    define PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS \
        _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#    define PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
#    define PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS \
        _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#    define PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS _Pragma("GCC diagnostic pop")
#else
#    define PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
#    define PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
#endif

#define PEAK_AFL_VERSION_CODE(major, minor, subminor, patch) (((major) << 24) + ((minor) << 16) + ((subminor) << 8) + (patch))
#define PEAK_AFL_API_STATUS PEAK_AFL_EXPORT peak_afl_status PEAK_AFL_CALLCONV

/*!
 * \defgroup ids_peak_afl_c C
 * \ingroup ids_peak_afl
 *
 * \brief The C interface for the IDS peak AFL library.
 */

/*!
 * \defgroup ids_peak_afl_c_library Library
 * \brief Library level functions and types and more.
 * \ingroup ids_peak_afl_c
 */

/*!
 * \defgroup ids_peak_afl_c_status Status types and values
 * \brief Definitions on status types and values.
 * \ingroup ids_peak_afl_c
 */

/*!
 * \defgroup ids_peak_afl_c_types Types
 * \brief Definitions of types
 * \ingroup ids_peak_afl_c
 */

/*!
 * \defgroup ids_peak_afl_c_automanager AutoManager
 * \brief Auto manager that can apply multiple auto features to an image by registering one or more controllers.
 * \ingroup ids_peak_afl_c
 */

/*!
 * \defgroup ids_peak_afl_c_autocontroller AutoController
 * \brief Specific controllers that represent automatic control functionality for camera features.
 * \ingroup ids_peak_afl_c
 */

/*!
 * \defgroup ids_peak_afl_c_focus Auto focus
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Automatic focus control for lens focus positioning and sharpness optimization.
 */

/*!
 * \defgroup ids_peak_afl_c_whitebalance Auto whitebalance
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Automatic white balance control for color correction and temperature adjustment.
 */

/*!
 * \defgroup ids_peak_afl_c_brightness Auto brightness
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Automatic brightness control through exposure and gain adjustment.
 */

/*!
 * \defgroup ids_peak_afl_c_controller_settings Controller settings
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Common configuration settings and parameters for auto feature controllers.
 */

/*!
 * \defgroup ids_peak_afl_c_skip_frames Skip frames
 * \brief Frame processing optimization by skipping frames to reduce computational load.
 * \include{doc} descriptions/skip_frames.txt
 * \ingroup ids_peak_afl_c_whitebalance
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_focus
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_auto_target Auto target
 * \brief Target brightness value configuration for automatic adjustment.
 * \include{doc} descriptions/target.txt
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_auto_tolerance Auto tolerance
 * \brief Acceptable deviation from target brightness settings.
 * \include{doc} descriptions/tolerance.txt
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_auto_percentile Auto percentile
 * \brief Percentile-based brightness analysis configuration.
 * \include{doc} descriptions/percentile.txt
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_hysteresis Hysteresis
 * \brief Focus stability control to prevent hunting and oscillation.
 * \include{doc} descriptions/hysteresis.txt
 * \ingroup ids_peak_afl_c_focus
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_focus_limit Limit
 * \brief Focus position range limits and boundaries.
 * \include{doc} descriptions/focus_limit.txt
 * \ingroup ids_peak_afl_c_focus
 * \ingroup ids_peak_afl_c_controller_settings
 */

/*!
 * \defgroup ids_peak_afl_c_brightness_limit Limit
 * \brief Brightness control range limits and boundaries.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness
 */

/*!
 * \defgroup ids_peak_afl_c_exposure_limit Exposure limit
 * \brief Exposure time range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_gain_limit Gain limit
 * \brief General gain range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_gain_analog_limit Gain analog limit
 * \brief Analog gain range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_gain_combined_limit Gain combined limit
 * \brief Combined gain range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_gain_digital_limit Gain digital limit
 * \brief Digital gain range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_gain_host_limit Gain host limit
 * \brief Host-side gain range limits for brightness control.
 * \include{doc} descriptions/brightness_limit.txt
 * \ingroup ids_peak_afl_c_brightness_limit
 */

/*!
 * \defgroup ids_peak_afl_c_weighted_roi Weighted region of interest
 * \brief Multi-region focus evaluation with configurable weights.
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_roi Region of interest
 * \brief Analysis area configuration for automatic control operations.
 * \include{doc} descriptions/roi.txt
 * \ingroup ids_peak_afl_c_controller_settings
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_whitebalance
 */

/*!
 * \defgroup ids_peak_afl_c_roi_preset Region of interest presets
 * \brief Predefined region of interest configurations for focus control.
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_sharpness_algorithm Sharpness algorithm
 * \brief Sharpness measurement algorithms for focus evaluation.
 * \include{doc} descriptions/sharpness_algorithm.txt
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_controller_mode Mode
 * \brief Operation mode configuration for automatic control functionality.
 * \include{doc} descriptions/mode.txt
 * \ingroup ids_peak_afl_c_controller_settings
 * \ingroup ids_peak_afl_c_whitebalance
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_focus_algorithm Peak search algorithm
 * \brief Focus search algorithms for optimal focus positioning.
 * \include{doc} descriptions/focus_algorithm.txt
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_callback Callbacks
 * \brief Event notification callbacks for automatic control operations.
 * \include{doc} descriptions/callback.txt
 * \ingroup ids_peak_afl_c_controller_settings
 * \ingroup ids_peak_afl_c_whitebalance
 * \ingroup ids_peak_afl_c_brightness
 * \ingroup ids_peak_afl_c_focus
 */

/*!
 * \defgroup ids_peak_afl_c_brightness_algorithm Algorithm
 * \brief Brightness analysis algorithms for automatic exposure and gain control.
 * \include{doc} descriptions/brightness_algorithm.txt
 * \ingroup ids_peak_afl_c_brightness
 */

/*!
 * \defgroup ids_peak_afl_c_brightness_component Component
 * \brief Individual brightness control components for granular parameter adjustment.
 * \ingroup ids_peak_afl_c_brightness
 */

/*!
 * \defgroup ids_peak_afl_c_brightness_mode Mode
 * \brief Operation mode configuration for brightness control components.
 * \include{doc} descriptions/mode.txt
 * \ingroup ids_peak_afl_c_brightness_component
 */

/*!
 * \defgroup ids_peak_afl_c_brightness_callback Callback
 * \brief Event notification callbacks for brightness control component operations.
 * \ingroup ids_peak_afl_c_brightness_component
 * \include{doc} descriptions/callback.txt
 */

/*!
 * \brief Opaque handle for auto feature controllers
 *
 * This handle represents an instance of an automatic feature controller (brightness,
 * focus, or white balance). Controllers are created through manager instances and
 * should be treated as opaque pointers.
 *
 * \warning Never cast or manipulate this handle directly
 * \see peak_afl_AutoFeatureManager_AddController()
 */
typedef void* peak_afl_controller_handle;

/*!
 * \brief Opaque handle for auto feature managers
 *
 * This handle represents an instance of an automatic feature manager that coordinates
 * multiple controllers and processes images. Managers maintain the processing pipeline
 * and handle communication with camera devices.
 *
 * \warning Never cast or manipulate this handle directly
 * \see peak_afl_AutoFeatureManager_Create()
 */
typedef void* peak_afl_manager_handle;

/*!
 * \ingroup ids_peak_afl_c_status
 * \brief Auto feature library status codes
 *
 * All auto feature library functions return one of these status codes to indicate
 * success or the specific type of error that occurred. Applications should always
 * check return values and handle errors appropriately.
 *
 * \note Use peak_afl_GetLastError() to get detailed error descriptions
 * \see peak_afl_GetLastError()
 */
typedef enum peak_afl_status
{
    /*!
     * \brief Operation completed successfully
     *
     * The function executed without any errors and completed the requested operation.
     */
    PEAK_AFL_STATUS_SUCCESS = 0,

    /*!
     * \brief General error occurred
     *
     * An unspecified error occurred during function execution. Use peak_afl_GetLastError()
     * to get detailed information about the specific error.
     *
     * \see peak_afl_GetLastError()
     */
    PEAK_AFL_STATUS_ERROR = 1,

    /*!
     * \brief Library not initialized
     *
     * The auto feature library has not been initialized. Call peak_afl_Init()
     * before using any other library functions.
     *
     * \see peak_afl_Init()
     */
    PEAK_AFL_STATUS_NOT_INITIALIZED = 2,

    /*!
     * \brief Invalid parameter provided
     *
     * One or more function parameters are invalid (e.g., NULL pointers where valid
     * pointers are required, out-of-range values, invalid handles).
     *
     * \note Check parameter documentation for valid ranges and requirements
     */
    PEAK_AFL_STATUS_INVALID_PARAMETER = 3,

    /*!
     * \brief Access denied to resource
     *
     * The requested operation could not be performed due to insufficient permissions
     * or the resource being locked by another process.
     */
    PEAK_AFL_STATUS_ACCESS_DENIED = 4,

    /*!
     * \brief Resource is busy
     *
     * The requested resource (manager, controller, or device) is currently busy
     * processing another operation. Try again later or check the status.
     *
     * \see peak_afl_AutoFeatureManager_Status()
     */
    PEAK_AFL_STATUS_BUSY = 5,

    /*!
     * \brief Provided buffer is too small
     *
     * The buffer provided for output data is smaller than required. Use the
     * two-stage query pattern to determine the required buffer size.
     *
     * \see \ref principle_two_stage_query
     */
    PEAK_AFL_STATUS_BUFFER_TOO_SMALL = 6,

    /*!
     * \brief Invalid or unsupported image format
     *
     * The provided image format is not supported by the auto feature algorithms
     * or the format parameters are invalid.
     *
     * \note Check supported pixel formats in the documentation
     */
    PEAK_AFL_STATUS_INVALID_IMAGE_FORMAT = 7,

    /*!
     * \brief Feature or operation not supported
     *
     * The requested feature or operation is not supported by the current device
     * or configuration. Check feature availability before use.
     */
    PEAK_AFL_STATUS_NOT_SUPPORTED = 8,

    /*!
     * \brief Parameter value was adjusted
     *
     * The operation succeeded, but one or more parameter values were automatically
     * adjusted to fit within valid ranges. Check current values after the operation.
     *
     * \note This is not an error condition
     */
    PEAK_AFL_STATUS_VALUE_ADJUSTED = 9
} peak_afl_status;

/*!
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Auto feature controller types
 *
 * Defines the available types of automatic feature controllers that can be created
 * and managed by the auto feature system. Each controller type specializes in
 * controlling specific camera parameters.
 *
 * \see peak_afl_AutoController_Create()
 */
typedef enum peak_afl_controllerType
{
    /*!
     * \brief Invalid or uninitialized controller type
     *
     * This value indicates an invalid controller type and should not be used
     * for controller creation.
     */
    PEAK_AFL_CONTROLLER_TYPE_INVALID = 0,

    /*!
     * \brief Automatic brightness exposure/gain controller
     *
     * Controls camera exposure time, gain settings, and other parameters to
     * maintain optimal image brightness. Can work with multiple gain types
     * (analog, digital, combined, host) and exposure settings.
     *
     * \see \ref ids_peak_afl_c_brightness
     */
    PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS = 1,

    /*!
     * \brief Automatic white balance controller
     *
     * Adjusts color channel gains to correct for different lighting conditions
     * and maintain accurate color reproduction. Supports various white balance
     * algorithms and manual/automatic operation modes.
     *
     * \see \ref ids_peak_afl_c_whitebalance
     */
    PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE = 2,

    /*!
     * \brief Automatic focus controller
     *
     * Automatically adjusts camera focus to achieve maximum image sharpness
     * using various focus algorithms and search strategies. Supports both
     * continuous and single-shot focus operations.
     *
     * \see \ref ids_peak_afl_c_focus
     */
    PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS = 5
} peak_afl_controllerType;

/*!
 * \ingroup ids_peak_afl_c_controller_mode
 * \brief Auto feature controller operation modes
 *
 * Defines how an auto feature controller operates when processing images.
 * The mode determines when and how often the controller adjusts camera parameters.
 *
 * \see peak_afl_AutoController_Mode_Set()
 * \see peak_afl_AutoController_Mode_Get()
 */
typedef enum peak_afl_controller_automode
{
    /*!
     * \brief Auto feature disabled
     *
     * The controller is disabled and will not process images or adjust camera
     * parameters. Use this mode to temporarily disable auto features without
     * destroying the controller.
     */
    PEAK_AFL_CONTROLLER_AUTOMODE_OFF,

    /*!
     * \brief Continuous automatic adjustment
     *
     * The controller continuously processes incoming images and adjusts camera
     * parameters as needed. This mode provides real-time adaptation to changing
     * conditions but may cause visible parameter changes during operation.
     *
     * \note Best for applications where conditions change frequently
     */
    PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS,

    /*!
     * \brief Single adjustment operation
     *
     * The controller processes images and adjusts parameters once, then automatically
     * switches to OFF mode. Use this for one-time calibration or when you want
     * manual control over when adjustments occur.
     *
     * \note Controller will automatically switch to OFF after completion
     */
    PEAK_AFL_CONTROLLER_AUTOMODE_ONCE
} peak_afl_controller_automode;


/*!
 * \ingroup ids_peak_afl_c_status
 * \brief Controller operational status
 *
 * Defines the current operational state of an auto feature controller.
 * The status indicates what the controller is currently doing and whether
 * it is available for new operations.
 *
 * \see peak_afl_AutoController_Status()
 * \see peak_afl_AutoFeatureManager_Status()
 */
typedef enum peak_afl_controller_status
{
    /*! \brief Controller status undefined */
    PEAK_AFL_CONTROLLER_STATUS_UNDEFINED,

    /*!
     * \brief Controller is disabled or inactive
     *
     * The controller is in OFF mode and not processing images.
     * No automatic adjustments will be made until the controller
     * is set to CONTINUOUS or ONCE mode.
     *
     * \note This is the initial state after controller creation
     * \see PEAK_AFL_CONTROLLER_AUTOMODE_OFF
     */
    PEAK_AFL_CONTROLLER_STATUS_OFF,

    /*!
     * \brief Controller is actively processing
     *
     * The controller is currently in the middle of processing an image
     * or executing an algorithm. This indicates ongoing work that has
     * not yet completed.
     *
     * \note Different from BUSY - indicates active algorithm execution
     * \note Processing time varies by algorithm complexity
     */
    PEAK_AFL_CONTROLLER_STATUS_IN_PROGRESS,

    /*!
     * \brief Controller completed its operation successfully
     *
     * The controller has finished processing and reached its target
     * or completed the requested operation. In ONCE mode, the controller
     * automatically transitions to OFF after reaching this state.
     *
     * \note In CONTINUOUS mode, this state is brief before next processing
     * \note In ONCE mode, controller switches to OFF after finishing
     */
    PEAK_AFL_CONTROLLER_STATUS_FINISHED,

    /*!
     * \brief Controller is busy and cannot accept new requests
     *
     * The controller is currently occupied and cannot process new images
     * or requests. This typically occurs when the controller is already
     * processing an image or waiting for camera parameter adjustments.
     *
     * \note Check this status before submitting new images
     * \note Different from IN_PROGRESS - indicates resource unavailability
     */
    PEAK_AFL_CONTROLLER_STATUS_BUSY,

    /*!
     * \brief Controller operation was canceled
     *
     * The current operation was canceled before completion, either by
     * user request or due to changing conditions. The controller is
     * available for new operations.
     *
     * \note Controller can accept new operations after cancellation
     * \note May occur when switching modes or stopping operations
     */
    PEAK_AFL_CONTROLLER_STATUS_CANCELED,

    /*!
     * \brief Controller encountered an error
     *
     * An error occurred during processing or parameter adjustment.
     * The controller may need to be reset or reconfigured.
     * Use peak_afl_GetLastError() for detailed error information.
     *
     * \note Controller may remain in this state until error is resolved
     * \note Check error details with peak_afl_GetLastError()
     * \see peak_afl_GetLastError()
     */
    PEAK_AFL_CONTROLLER_STATUS_ERROR,

    /*!
     * \brief Controller skipped processing this frame
     *
     * The controller deliberately skipped processing the current frame,
     * typically due to skip frames configuration or because the frame
     * did not meet processing criteria.
     *
     * \note This is normal behavior when skip frames is configured
     * \note Not an error condition - controller remains operational
     * \see peak_afl_AutoController_SkipFrames_Set()
     */
    PEAK_AFL_CONTROLLER_STATUS_SKIPPED
} peak_afl_controller_status;


/*!
 * \ingroup ids_peak_afl_c_focus_algorithm
 * \brief Focus search algorithms
 *
 * Defines the search algorithms used by auto focus controllers to find
 * the optimal focus position. Different algorithms offer trade-offs between
 * speed, accuracy, and reliability in various conditions.
 *
 * \note Algorithm availability may depend on camera capabilities
 * \see peak_afl_AutoController_Algorithm_Set()
 * \see peak_afl_AutoController_Algorithm_Get()
 * \see peak_afl_AutoController_Algorithm_IsSupported()
 */
typedef enum peak_afl_controller_algorithm
{
    /*!
     * \brief Automatic algorithm selection
     *
     * \deprecated This value is deprecated. The automatic selection always defaults to
     *             the Golden Ratio algorithm. Use
     *             \ref PEAK_AFL_CONTROLLER_ALGORITHM_GOLDEN_RATIO_SEARCH instead.
     */
    PEAK_AFL_CONTROLLER_ALGORITHM_AUTO PEAK_AFL_DEPRECATED_ENUM_ATTR,

    /*!
     * \brief Golden ratio search algorithm
     *
     * Uses golden section search to efficiently find the focus peak.
     * Provides fast convergence with good accuracy for most scenes.
     * Requires fewer focus steps than full scan methods.
     *
     * \note Fast convergence (typically 8-12 steps)
     * \note Good for real-time applications
     * \note May struggle with multiple focus peaks or low contrast scenes
     */
    PEAK_AFL_CONTROLLER_ALGORITHM_GOLDEN_RATIO_SEARCH,

    /*!
     * \brief Hill climbing search algorithm
     *
     * Iteratively moves focus position toward increasing sharpness values.
     * Good for fine-tuning focus around the optimal position.
     * May get trapped in local maxima with complex scenes.
     *
     * \note Good for fine focus adjustments
     * \note Fast for small focus corrections
     * \note May fail with multiple focus peaks or noisy sharpness curves
     */
    PEAK_AFL_CONTROLLER_ALGORITHM_HILL_CLIMBING_SEARCH,

    /*!
     * \brief Global search algorithm
     *
     * Performs a comprehensive search across the focus range to find
     * the global optimum. More robust against local maxima but slower
     * than other methods. Best accuracy for complex scenes.
     *
     * \note Highest accuracy and reliability
     * \note Handles multiple focus peaks well
     * \note Slower than other algorithms (moderate speed)
     * \note Best for critical applications where accuracy is paramount
     */
    PEAK_AFL_CONTROLLER_ALGORITHM_GLOBAL_SEARCH,

    /*!
     * \brief Full range scan algorithm
     *
     * Scans the entire focus range systematically to build a complete
     * focus curve. Provides maximum accuracy but requires the most time.
     * Ideal for laboratory, calibration, or non-real-time applications.
     *
     * \note Maximum accuracy possible
     * \note Complete focus characterization across full range
     * \note Slowest algorithm (full range scan)
     * \note Best for laboratory, calibration, or quality control applications
     */
    PEAK_AFL_CONTROLLER_ALGORITHM_FULL_SCAN
} peak_afl_controller_algorithm;

/*!
 * \ingroup ids_peak_afl_c_brightness_algorithm
 * \brief Brightness calculation algorithms
 *
 * Defines the mathematical algorithms used to calculate representative brightness
 * values from image data. Different algorithms may be more suitable for different
 * image content and lighting conditions.
 *
 * \see peak_afl_AutoController_BrightnessAlgorithm_Set()
 * \see peak_afl_AutoController_BrightnessAlgorithm_Get()
 */
typedef enum peak_afl_controller_brightness_algorithm
{
    /*!
     * \brief Median-based brightness calculation
     *
     * Uses the median value of pixel intensities in the analysis region.
     * More robust against outliers and extreme values, providing stable
     * brightness measurements in scenes with high contrast or noise.
     *
     * \note Recommended for scenes with varying lighting or high contrast
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEDIAN,

    /*!
     * \brief Mean-based brightness calculation
     *
     * Uses the arithmetic mean (average) of pixel intensities in the analysis
     * region. Provides faster computation and smooth brightness transitions
     * but may be affected by extreme pixel values.
     *
     * \note Recommended for evenly lit scenes with consistent lighting
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEAN,
} peak_afl_controller_brightness_algorithm;

/*!
 * \ingroup ids_peak_afl_c_sharpness_algorithm
 * \brief Focus sharpness calculation algorithms
 *
 * Defines the mathematical algorithms used to calculate image sharpness for
 * automatic focus control. Different algorithms have varying sensitivity to
 * different types of image content and noise conditions.
 *
 * \see peak_afl_AutoController_SharpnessAlgorithm_Set()
 * \see peak_afl_AutoController_SharpnessAlgorithm_Get()
 */
typedef enum peak_afl_controller_sharpness_algorithm
{
    /*!
     * \brief Automatic algorithm selection
     *
     * Default sharpness algorithm.
     *
     * \deprecated This value is deprecated. The automatic selection always defaults to
     *             the Tenengrad algorithm. Use
     *             \ref PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_TENENGRAD instead.
     */
    PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_AUTO PEAK_AFL_DEPRECATED_ENUM_ATTR,

    /*!
     * \brief Tenengrad gradient-based algorithm
     *
     * Uses gradient magnitude calculations to measure image sharpness.
     * Effective for images with clear edges and high contrast features.
     * Computationally efficient and works well in most lighting conditions.
     *
     * \note Good for high-contrast scenes with clear edges
     */
    PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_TENENGRAD,

    /*!
     * \brief Sobel edge detection algorithm
     *
     * Uses Sobel edge detection operators to measure sharpness based on
     * edge strength. Particularly effective for images with fine details
     * and textures. More sensitive to noise than Tenengrad.
     *
     * \note Best for detailed textures and fine patterns
     */
    PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_SOBEL,

    /*!
     * \brief Mean score algorithm
     *
     * Calculates sharpness based on statistical measures of image content.
     * Provides stable measurements but may be less sensitive to fine details.
     * Good for consistent performance across varying image content.
     *
     * \note Stable performance, less sensitive to noise
     */
    PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_MEAN_SCORE,

    /*!
     * \brief Histogram variance algorithm
     *
     * Uses histogram analysis to measure image sharpness based on intensity
     * distribution variance. Effective for images with good contrast but
     * may be affected by lighting variations.
     *
     * \note Good for well-lit scenes with good contrast
     */
    PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_HISTOGRAM_VARIANCE
} peak_afl_controller_sharpness_algorithm;

/*!
 * \ingroup ids_peak_afl_c_brightness_component
 * \brief Brightness control components
 *
 * Defines the different camera parameters that can be adjusted by the brightness
 * controller to achieve target brightness levels. Each component affects image
 * brightness differently and may have different performance characteristics.
 *
 * \note Component availability depends on camera capabilities
 * \see peak_afl_AutoController_BrightnessComponent_IsSupported()
 */
typedef enum peak_afl_controller_brightness_component
{
    /*!
     * \brief Invalid or uninitialized component
     *
     * This value indicates an invalid component type and should not be used
     * for component operations.
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_INVALID = 0x00,

    /*!
     * \brief Camera exposure time control
     *
     * Adjusts the camera's exposure time (shutter speed) to control brightness.
     * Longer exposures increase brightness but may introduce motion blur.
     * Generally the preferred method for brightness control when motion is not critical.
     *
     * \note May affect motion blur and frame rate
     * \see \ref ids_peak_afl_c_exposure_limit
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE = 0x01,

    /*!
     * \brief Generic gain control
     *
     * Adjusts the camera's gain setting using the default gain control.
     * The specific type of gain (analog/digital/combined/host) depends on camera implementation
     * or support.
     *
     * \deprecated Use specific gain types for better control
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_GAIN PEAK_AFL_DEPRECATED_ENUM_ATTR = 0x02,

    /*!
     * \brief Analog gain control
     *
     * Adjusts the sensor's analog gain before digitization. Provides good
     * signal-to-noise ratio but may be limited in range. Preferred over
     * digital gain when available.
     *
     * \note Better noise characteristics than digital gain
     * \see \ref ids_peak_afl_c_gain_analog_limit
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_ANALOG_GAIN = 0x03,

    /*!
     * \brief Digital gain control
     *
     * Adjusts gain in the digital domain after sensor readout. Wider range
     * than analog gain but may amplify noise. Use when analog gain is
     * insufficient or unavailable.
     *
     * \note May amplify sensor noise
     * \see \ref ids_peak_afl_c_gain_digital_limit
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_DIGITAL_GAIN = 0x04,

    /*!
     * \brief Combined analog and digital gain
     *
     * Automatically manages both analog and digital gain (combined) for optimal
     * signal-to-noise ratio. Typically uses analog gain first, then
     * digital gain for extended range.
     *
     * \note Recommended for best overall performance
     * \see \ref ids_peak_afl_c_gain_combined_limit
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_COMBINED_GAIN = 0x05,

    /*!
     * \brief Host-based software gain
     *
     * Applies gain in software on the host computer after image acquisition.
     * Provides unlimited range but processes images after capture, potentially
     * affecting real-time performance.
     *
     * \note Applied in software, may affect performance
     * \see \ref ids_peak_afl_c_gain_host_limit
     */
    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_HOST_GAIN = 0x06,

} peak_afl_controller_brightness_component;

/*!
 * \ingroup ids_peak_afl_c_whitebalance
 * \brief White balance control components
 *
 * Defines the different camera parameters that can be adjusted by the white balance
 * controller to achieve accurate color reproduction. Each component affects color
 * balance differently and may have different performance characteristics.
 *
 * \note Component availability depends on camera capabilities
 * \see peak_afl_AutoController_WhiteBalanceComponent_IsSupported()
 */
typedef enum peak_afl_controller_whitebalance_component
{
    /*!
     * \brief Invalid or uninitialized component
     *
     * This value indicates an invalid component type and should not be used
     * for component operations.
     */
    PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_INVALID = 0x00,

    /*!
     * \brief Analog gain white balance control
     *
     * Adjusts individual color channel analog gains before digitization.
     * Provides the best signal-to-noise ratio for white balance correction
     * but may have limited adjustment range.
     *
     * \note Best noise performance, preferred when available
     */
    PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_ANALOG_GAIN = 0x03,

    /*!
     * \brief Digital gain white balance control
     *
     * Adjusts individual color channel gains in the digital domain after
     * sensor readout. Wider adjustment range than analog gain but may
     * amplify noise, especially in darker regions.
     *
     * \note Wider range but may amplify noise
     */
    PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_DIGITAL_GAIN = 0x04,

    /*!
     * \brief Combined analog and digital gain control (combined)
     *
     * Automatically manages both analog and digital gains for each color
     * channel to achieve optimal white balance with best signal-to-noise
     * ratio. Uses analog gain first, then digital gain for extended range.
     *
     * \note Recommended for best overall performance
     */
    PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_COMBINED_GAIN = 0x05,

    /*!
     * \brief Host-based software white balance
     *
     * Applies white balance correction in software on the host computer
     * after image acquisition. Provides unlimited adjustment range but
     * processes images after capture.
     *
     * \note Applied in software, may affect performance
     */
    PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_HOST_GAIN = 0x06,

} peak_afl_controller_whitebalance_component;

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief ROI weight values for focus control
 *
 * Defines the relative importance weights that can be assigned to regions
 * of interest for focus analysis. Higher weights give more influence to
 * a region's focus metrics in the overall focus calculation.
 *
 * \see peak_afl_weighted_rectangle
 * \see peak_afl_AutoController_Weighted_ROI_Set()
 */
typedef enum peak_afl_roi_weight
{
    /*!
     * \brief Low importance weight
     *
     * This region has minimal influence on focus calculations.
     * Use for background areas or regions of lesser importance.
     */
    PEAK_AFL_CONTROLLER_ROI_WEIGHT_WEAK = 0x0021,

    /*!
     * \brief Medium importance weight
     *
     * This region has moderate influence on focus calculations.
     * Use for areas of average importance in the scene.
     */
    PEAK_AFL_CONTROLLER_ROI_WEIGHT_MEDIUM = 0x0042,

    /*!
     * \brief High importance weight
     *
     * This region has strong influence on focus calculations.
     * Use for critical areas that must be in sharp focus.
     */
    PEAK_AFL_CONTROLLER_ROI_WEIGHT_STRONG = 0x0063
} peak_afl_roi_weight;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Controller callback types
 *
 * Defines the types of callbacks that can be registered with controllers
 * to receive notifications about processing events and completion status.
 *
 * \see peak_afl_AutoController_Callback_Set()
 * \see PEAK_AFL_CALLBACK_FINISHED_FUNC
 * \see PEAK_AFL_CALLBACK_PROCESSING_FUNC
 */
typedef enum peak_afl_callback_type
{
    /*!
     * \brief Controller operation finished callback
     *
     * Called when the controller completes an operation and reaches
     * its target or finishes processing. Particularly useful in ONCE mode
     * to detect when the controller has finished its adjustment.
     *
     * \see PEAK_AFL_CALLBACK_FINISHED_FUNC
     */
    PEAK_AFL_CONTROLLER_CALLBACK_FINISHED,

    /*!
     * \brief Legacy processing data callback
     *
     * \deprecated Use PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING instead
     *
     * Legacy callback type for processing data. Provides limited information
     * compared to the newer processing callback.
     *
     * \note only available for \ref ids_peak_afl_c_focus
     *
     * \see PEAK_AFL_CALLBACK_PROCESSING_DATA_FUNC
     */
    PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING_DATA PEAK_AFL_DEPRECATED_ENUM_ATTR,

    /*!
     * \brief Enhanced processing callback
     *
     * Called during image processing to provide real-time access to
     * processing data and intermediate results. Provides comprehensive
     * information about the current processing state.
     *
     * \see PEAK_AFL_CALLBACK_PROCESSING_FUNC
     */
    PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING
} peak_afl_callback_type;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Generic process data structure
 *
 * Base structure for all processing callback data. This structure contains
 * common information available for all controller types during processing.
 * Specific controller types provide extended structures with additional data.
 *
 * \note This is the base structure - cast to specific types for detailed data
 * \see peak_afl_process_data_brightness
 * \see peak_afl_process_data_focus
 * \see peak_afl_process_data_whitebalance
 * \see PEAK_AFL_CALLBACK_PROCESSING_FUNC
 */
typedef struct
{
    /*!
     * \brief Current controller status
     *
     * The operational status of the controller at the time of processing.
     * Indicates whether the controller is actively processing, finished,
     * or encountered an error.
     *
     * \see peak_afl_controller_status
     */
    peak_afl_controller_status controller_status;

    /*!
     * \brief Type of controller generating this data
     *
     * Identifies which type of controller (brightness, focus, white balance)
     * is providing this processing data. Use this to determine the appropriate
     * cast for accessing extended data.
     *
     * \see peak_afl_controllerType
     */
    peak_afl_controllerType controller_type;

    /*!
     * \brief Reserved space for future extensions
     *
     * Reserved bytes for future API extensions. Do not access or modify.
     */
    char reserved[32];

} peak_afl_process_data;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Brightness controller process data
 *
 * Extended process data structure for brightness controllers. Contains
 * brightness-specific information including the current brightness component
 * being processed and the calculated mean brightness value from the image
 * analysis.
 *
 * \note Cast from peak_afl_process_data when controller_type is BRIGHTNESS
 * \see peak_afl_process_data
 * \see PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS
 */
typedef struct
{
    /*!
     * \brief Current controller status
     *
     * The operational status of the brightness controller at the time of processing.
     *
     * \see peak_afl_controller_status
     */
    peak_afl_controller_status controller_status;

    /*!
     * \brief Controller type (always BRIGHTNESS)
     *
     * Will always be PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS for this structure.
     *
     * \see peak_afl_controllerType
     */
    peak_afl_controllerType controller_type;

    /*!
     * \brief Current brightness component being processed
     *
     * Indicates which brightness adjustment mechanism (exposure, analog gain,
     * digital gain, etc.) is currently being processed by the controller.
     *
     * \see peak_afl_controller_brightness_component
     */
    peak_afl_controller_brightness_component controller_component;

    /*!
     * \brief Calculated mean brightness value
     *
     * The mean brightness value calculated from the current image analysis.
     * This value is used by the controller to determine appropriate brightness
     * adjustments. The scale and interpretation depend on the image format
     * and controller configuration.
     */
    int mean;

    /*!
     * \brief Reserved space for future extensions
     *
     * Reserved bytes for future API extensions. Do not access or modify.
     */
    char reserved[64];

} peak_afl_process_data_brightness;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief White balance controller process data
 *
 * Extended process data structure for white balance controllers. Contains
 * white balance-specific information including the calculated mean values
 * for each color channel (RGB) and the current white balance component
 * being processed.
 *
 * \note Cast from peak_afl_process_data when controller_type is WHITE_BALANCE
 * \see peak_afl_process_data
 * \see PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE
 */
typedef struct
{
    /*!
     * \brief Current controller status
     *
     * The operational status of the white balance controller at the time of processing.
     *
     * \see peak_afl_controller_status
     */
    peak_afl_controller_status controller_status;

    /*!
     * \brief Controller type (always WHITE_BALANCE)
     *
     * Will always be PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE for this structure.
     *
     * \see peak_afl_controllerType
     */
    peak_afl_controllerType controller_type;

    /*!
     * \brief Calculated mean red channel value
     *
     * The mean brightness value for the red color channel calculated from
     * the current image analysis. Used for white balance calculations.
     */
    int mean_r;

    /*!
     * \brief Calculated mean green channel value
     *
     * The mean brightness value for the green color channel calculated from
     * the current image analysis. Used for white balance calculations.
     */
    int mean_g;

    /*!
     * \brief Calculated mean blue channel value
     *
     * The mean brightness value for the blue color channel calculated from
     * the current image analysis. Used for white balance calculations.
     */
    int mean_b;

    /*!
     * \brief Current white balance component being processed
     *
     * Indicates which white balance adjustment mechanism (analog gain,
     * digital gain, combined gain, etc.) is currently being processed.
     *
     * \see peak_afl_controller_whitebalance_component
     */
    peak_afl_controller_whitebalance_component controller_component;

    /*!
     * \brief Reserved space for future extensions
     *
     * Reserved bytes for future API extensions. Do not access or modify.
     */
    char reserved[64 - sizeof(peak_afl_controller_whitebalance_component)];

} peak_afl_process_data_whitebalance;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Focus controller process data
 *
 * Extended process data structure for focus controllers. Contains
 * focus-specific information including current focus position and
 * sharpness measurements from the focus algorithm.
 *
 * \note Cast from peak_afl_process_data when controller_type is AUTOFOCUS
 * \see peak_afl_process_data
 * \see PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS
 */
typedef struct
{
    /*!
     * \brief Current controller status
     *
     * The operational status of the focus controller at the time of processing.
     *
     * \see peak_afl_controller_status
     */
    peak_afl_controller_status controller_status;

    /*!
     * \brief Controller type (always AUTOFOCUS)
     *
     * Will always be PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS for this structure.
     *
     * \see peak_afl_controllerType
     */
    peak_afl_controllerType controller_type;

    /*!
     * \brief Current focus position
     *
     * The current focus position of the camera lens. Units and range
     * depend on the camera/lens system. This value represents the
     * physical position being evaluated by the focus algorithm.
     */
    int focus_value;

    /*!
     * \brief Current sharpness measurement
     *
     * The sharpness value calculated from the current image using the
     * configured sharpness algorithm. Higher values typically indicate
     * sharper images. The scale and range depend on the algorithm used.
     *
     * \see peak_afl_controller_sharpness_algorithm
     */
    int sharpness_value;

    /*!
     * \brief Reserved space for future extensions
     *
     * Reserved bytes for future API extensions. Do not access or modify.
     */
    char reserved[64];
} peak_afl_process_data_focus;

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Callback function type definition for #PEAK_AFL_CONTROLLER_CALLBACK_FINISHED
 *
 * \param context User context data
 *
 * \since 1.0
 */
typedef void(PEAK_AFL_CALLCONV* PEAK_AFL_CALLBACK_FINISHED_FUNC)(void* context);

/*!
 * \ingroup ids_peak_afl_c_callback
 *
 * \brief Callback function type definition for #PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING
 *
 * \param data Processing data
 * \param context User context data
 *
 * \since 1.7
 */
typedef void(PEAK_AFL_CALLCONV* PEAK_AFL_CALLBACK_PROCESSING_FUNC)(peak_afl_process_data* data, void* context);

/*!
 * \internal
 * \ingroup ids_peak_afl_c_callback
 *
 * \brief Callback function type definition for #PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING_DATA
 *
 * \param focusValue Focus value
 * \param sharpnessValue Sharpness value
 * \param context User context data
 *
 * \deprecated use #PEAK_AFL_CALLBACK_PROCESSING_FUNC instead
 *
 * \since 1.0
 */
PEAK_AFL_DEPRECATED_ATTR typedef void(PEAK_AFL_CALLCONV* PEAK_AFL_CALLBACK_PROCESSING_DATA_FUNC)(
    int focusValue, int sharpnessValue, void* context);

/*!
 * \ingroup ids_peak_afl_c_roi_preset
 * \brief Predefined ROI preset configurations
 *
 * Defines commonly used ROI configurations that can be quickly applied
 * to controllers without manually specifying coordinates. These presets
 * automatically adapt to the current image size.
 *
 * \see peak_afl_AutoController_ROI_Preset_Set()
 * \see peak_afl_AutoController_ROI_Set()
 */
typedef enum peak_afl_roi_preset
{
    /*!
     * \brief Center region preset
     *
     * Sets the ROI to a centered region within the image.
     * The exact size depends on the implementation but typically
     * covers the center 25-50% of the image area.
     *
     * \note Automatically adapts to current image dimensions
     */
    PEAK_AFL_CONTROLLER_ROI_PRESET_CENTER
} peak_afl_roi_preset;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief 2D size structure
 *
 * Defines dimensions in a 2-dimensional coordinate space. Used throughout
 * the API to specify image dimensions, region sizes, and other 2D measurements.
 * All values are in pixels unless otherwise specified.
 *
 * \note Both width and height must be greater than 0 for valid sizes
 * \see peak_afl_rectangle, peak_afl_position
 */
typedef struct
{
    /*!
     * \brief Width dimension in pixels
     *
     * The horizontal extent of the size. Must be greater than 0 for valid sizes.
     *
     * \note Maximum value depends on camera and system capabilities
     */
    uint32_t width;

    /*!
     * \brief Height dimension in pixels
     *
     * The vertical extent of the size. Must be greater than 0 for valid sizes.
     *
     * \note Maximum value depends on camera and system capabilities
     */
    uint32_t height;
} peak_afl_size;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief 2D position structure
 *
 * Defines a position in a 2-dimensional coordinate space. Used to specify
 * coordinates within images or other 2D coordinate systems.
 *
 * \note Coordinates are zero-based with origin at top-left corner
 * \see peak_afl_rectangle, peak_afl_size
 */
typedef struct
{
    /*!
     * \brief X-coordinate (horizontal position)
     *
     * The horizontal position in pixels from the left edge.
     * Zero represents the leftmost position.
     */
    uint32_t x;

    /*!
     * \brief Y-coordinate (vertical position)
     *
     * The vertical position in pixels from the top edge.
     * Zero represents the topmost position.
     */
    uint32_t y;
} peak_afl_position;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief 2D rectangle structure
 *
 * Defines a rectangular region in a 2-dimensional coordinate space.
 * Used throughout the API to specify regions of interest, image areas,
 * and other rectangular regions.
 *
 * \note Coordinates are zero-based with origin at top-left corner
 * \note Width and height must be greater than 0 for valid rectangles
 * \see peak_afl_position, peak_afl_size
 */
typedef struct
{
    /*!
     * \brief X-coordinate of top-left corner
     *
     * The horizontal position of the rectangle's left edge in pixels.
     */
    uint32_t x;

    /*!
     * \brief Y-coordinate of top-left corner
     *
     * The vertical position of the rectangle's top edge in pixels.
     */
    uint32_t y;

    /*!
     * \brief Width of rectangle in pixels
     *
     * The horizontal extent of the rectangle. Must be greater than 0.
     */
    uint32_t width;

    /*!
     * \brief Height of rectangle in pixels
     *
     * The vertical extent of the rectangle. Must be greater than 0.
     */
    uint32_t height;
} peak_afl_rectangle;

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief Weighted region of interest for focus control
 *
 * Defines a rectangular region with an associated weight for focus analysis.
 * The weight determines the relative importance of this region compared to
 * other regions when calculating focus metrics.
 *
 * \see peak_afl_roi_weight
 * \see peak_afl_rectangle
 */
typedef struct
{
    /*!
     * \brief Rectangular region definition
     *
     * The rectangular area within the image where focus analysis will be performed.
     * Must be within the image boundaries.
     */
    peak_afl_rectangle roi;

    /*!
     * \brief Weight of this region
     *
     * The relative importance of this region for focus calculations.
     * Higher weights give more influence to this region's focus metrics.
     */
    peak_afl_roi_weight weight;
} peak_afl_weighted_rectangle;

/*!
 * \ingroup ids_peak_afl_c_focus_limit
 * \brief Controller parameter limit range
 *
 * Defines the minimum and maximum limits for controller parameters such as
 * focus position, exposure time, or gain values. Used to constrain automatic
 * adjustments within acceptable ranges.
 *
 * \note Minimum value must be less than or equal to maximum value
 * \see peak_afl_double_limit for floating-point limits
 */
typedef struct
{
    /*!
     * \brief Minimum allowed value
     *
     * The lower bound for the parameter. The controller will not set
     * values below this limit.
     */
    int min;

    /*!
     * \brief Maximum allowed value
     *
     * The upper bound for the parameter. The controller will not set
     * values above this limit.
     */
    int max;
} peak_afl_controller_limit;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief Floating-point parameter limit range
 *
 * Defines the minimum and maximum limits for floating-point controller parameters
 * such as percentile values, tolerance settings, or other continuous parameters.
 * Used to constrain automatic adjustments within acceptable ranges.
 *
 * \note Minimum value must be less than or equal to maximum value
 * \see peak_afl_controller_limit for integer limits
 */
typedef struct
{
    /*!
     * \brief Minimum allowed value
     *
     * The lower bound for the parameter. The controller will not set
     * values below this limit.
     */
    double min;

    /*!
     * \brief Maximum allowed value
     *
     * The upper bound for the parameter. The controller will not set
     * values above this limit.
     */
    double max;
} peak_afl_double_limit;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief Custom 8-bit boolean type
 *
 * A boolean type that uses 8 bits for storage. Used throughout the API
 * for boolean parameters and return values to ensure consistent size
 * across different platforms and compilers.
 *
 * \note Use PEAK_AFL_TRUE and PEAK_AFL_FALSE constants
 * \see PEAK_AFL_TRUE, PEAK_AFL_FALSE
 */
typedef uint8_t peak_afl_BOOL8;

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief Boolean true value
 *
 * Represents the true value for peak_afl_BOOL8 type.
 * Always use this constant instead of literal values.
 */
#define PEAK_AFL_TRUE 1

/*!
 * \ingroup ids_peak_afl_c_types
 * \brief Boolean false value
 *
 * Represents the false value for peak_afl_BOOL8 type.
 * Always use this constant instead of literal values.
 */
#define PEAK_AFL_FALSE 0

/*!
 * \ingroup ids_peak_afl_c_library
 * \brief Init the peak_afl auto feature library
 *
 * Initializes the internal library status.
 *
 * This function must be called prior to any other function call.\n
 * The function may be called multiple times from a single client process.
 * For each call, there must be a corresponding call to #peak_afl_Exit
 * to ensure proper deinitialization of the library status.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_ERROR   An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_Init(void);

/*!
 * \ingroup ids_peak_afl_c_library
 * \brief Exit the peak_afl auto feature library
 *
 * Deinitializes the internal library status.
 *
 * For each call to #peak_afl_Init there must be a corresponding call to this function
 * to ensure proper deinitialization of the library status. \n
 * After the library has been exited, its functions (besides #peak_afl_Init) will not be operable
 * until #peak_afl_Init has been called again.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_AFL_STATUS_ERROR           An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_Exit(void);

/*!
 * \ingroup ids_peak_afl_c_library
 * \brief Get the last error message
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[out] lastErrorCode            The error code of the last error. NULL if not required.
 * \param[out] lastErrorMessage         Pointer to a user allocated C string buffer to receive the last error text.
 *                                      If this parameter is NULL, \p lastErrorMessageSize will contain the needed size
 *                                      of \p lastErrorMessage in bytes. The size includes the terminating 0.
 * \param[in,out] lastErrorMessageSize  Size of \p lastErrorMessage:<br>
 *                                      \li \p lastErrorMessage equal NULL: <br>
 *                                          out: minimal size of \p lastErrorMessage in bytes to hold all information <br>
 *                                      \li \p lastErrorMessage unequal NULL: <br>
 *                                          in: size of the provided \p lastErrorMessage in bytes <br>
 *                                          out: number of bytes filled by the function
 *
 * \return #PEAK_AFL_STATUS_SUCCESS          Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_AFL_STATUS_BUFFER_TOO_SMALL The supplied buffer is too small.
 * \return #PEAK_AFL_STATUS_ERROR            An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_GetLastError(peak_afl_status* lastErrorCode, char* lastErrorMessage, size_t* lastErrorMessageSize);

/*!
 * \ingroup ids_peak_afl_c_library
 * \brief Query the library version
 *
 * Provides the version of the library divided in major, minor, subminor and patch, in that order of magnitude.
 *
 * It is allowed to pass NULL for parts not needed.
 *
 * \param[out] majorVersion      Major Version. NULL if not required.
 * \param[out] minorVersion      Minor Version. NULL if not required.
 * \param[out] subminorVersion   Subminor Version. NULL if not required.
 * \param[out] patchVersion      Patch Version. NULL if not required.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS  Operation was successful; no error occurred.
 *
 * \note This function can be used even if the library is not initialized.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_GetVersion(
    uint32_t* majorVersion, uint32_t* minorVersion, uint32_t* subminorVersion, uint32_t* patchVersion);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Create an automanager instance
 *
 * Creates a new auto feature manager instance that coordinates multiple automatic feature controllers
 * for image processing and camera parameter adjustment. The manager serves as a central hub for
 * processing images through various controllers like brightness, white balance, and autofocus.
 *
 * The auto feature manager requires a valid device node map to access camera parameters and settings.
 * The PEAK_NODE_MAP_HANDLE can be acquired by calling Handle() from std::shared_ptr<peak::core::NodeMap>.
 * This node map provides the interface to the camera's GenICam-compliant parameter structure.
 *
 * \param[out] handle        Pointer to receive the new auto feature manager handle. Must not be NULL.
 *                          The handle will be set to a valid manager instance on success.
 * \param[in]  nodeMapHandle Handle to the device node map from the vision API. This provides access
 *                          to camera parameters and must remain valid for the lifetime of the manager.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS         Manager created successfully and handle is valid
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED The library is not initialized - call peak_afl_Init() first
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid handle pointer or node map handle
 * \return #PEAK_AFL_STATUS_ERROR           An unexpected internal error occurred during creation
 *
 * \note The created manager must be destroyed with peak_afl_AutoFeatureManager_Destroy()
 * \note The node map handle must remain valid for the lifetime of the manager
 * \note Multiple managers can be created for different devices or configurations
 * \note Controllers must be added to the manager before image processing can begin
 *
 * \see peak_afl_AutoFeatureManager_Destroy()
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_AutoFeatureManager_AddController()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_Create(peak_afl_manager_handle* handle, PEAK_NODE_MAP_HANDLE nodeMapHandle);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Destroy an automanager instance
 *
 * Destroys an auto feature manager instance and releases all associated resources.
 * This function will automatically remove and destroy all controllers that have been
 * added to the manager. After successful destruction, the manager handle becomes invalid
 * and must not be used in any subsequent function calls.
 *
 * \param[in] handle Auto feature manager handle to destroy. Must be a valid handle
 *                  obtained from peak_afl_AutoFeatureManager_Create().
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Manager destroyed successfully; handle is now invalid
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle or handle is NULL
 * \return #PEAK_AFL_STATUS_BUSY             Manager is currently processing an image
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \warning After this operation, the manager handle becomes invalid and must not be used
 * \warning All controller handles associated with this manager also become invalid
 * \warning Ensure no image processing is in progress before calling this function
 *
 * \note This function automatically destroys all controllers added to the manager
 * \note To preserve controllers for use with other managers, remove them first with
 *       peak_afl_AutoFeatureManager_RemoveController()
 * \note Check manager status with peak_afl_AutoFeatureManager_Status() before destruction
 *
 * \see peak_afl_AutoFeatureManager_Create()
 * \see peak_afl_AutoFeatureManager_Status()
 * \see peak_afl_AutoFeatureManager_RemoveController()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_Destroy(peak_afl_manager_handle handle);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Add a controller to an auto manager instance
 *
 * Adds an existing automatic feature controller to the specified auto feature manager.
 * This allows the controller to participate in coordinated image processing operations
 * managed by the auto feature manager. Each controller can only be associated with one
 * manager at a time, and each manager can only contain one controller of each type.
 *
 * Controllers must be created separately using peak_afl_AutoController_Create() before
 * being added to a manager. Alternatively, use the convenience function
 * peak_afl_AutoFeatureManager_CreateController() to create and add in one operation.
 *
 * \param[in] handle     Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[in] controller Controller handle from peak_afl_AutoController_Create() that is not
 *                      currently associated with any manager
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller added successfully to the manager
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager or controller handle
 * \return #PEAK_AFL_STATUS_ACCESS_DENIED     Controller is already associated with another manager
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Controllers can only be added to one manager at a time
 * \note Each manager can only contain one controller of each type
 * \note The controller becomes available for image processing once added
 * \note Remove controllers with peak_afl_AutoFeatureManager_RemoveController() before adding to another manager
 *
 * \see peak_afl_AutoController_Create()
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_AutoFeatureManager_RemoveController()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_AddController(
    peak_afl_manager_handle handle, peak_afl_controller_handle controller);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Remove a controller from an auto feature manager instance
 *
 * Removes a controller from the manager without destroying the controller object.
 * The controller can be added to another manager or destroyed separately.
 * For a function that removes and destroys the controller in one call,
 * see peak_afl_AutoFeatureManager_DestroyController().
 *
 * \param[in] handle     Auto feature manager handle
 * \param[in] controller Controller handle to remove from the manager
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller removed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager or controller handle
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note The controller object remains valid after removal
 * \note To destroy the controller, call peak_afl_AutoController_Destroy() afterward
 * \note To add to another manager, call peak_afl_AutoFeatureManager_AddController()
 *
 * \see peak_afl_AutoFeatureManager_AddController()
 * \see peak_afl_AutoFeatureManager_DestroyController()
 * \see peak_afl_AutoController_Destroy()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_RemoveController(
    peak_afl_manager_handle handle, peak_afl_controller_handle controller);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Process an image through the auto feature pipeline
 *
 * Processes an image through all registered controllers in the auto feature manager.
 * The image is analyzed by each controller according to their configuration and mode
 * settings. Controllers may adjust camera parameters based on the analysis results.
 *
 * \param[in] handle      Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[in] imageHandle Image handle from the imaging library. Obtain this handle by calling
 *                        ImageBackendAccessor::BackendHandle(img) where img is a peak::ipl::Image.
 *                        The image must be in a supported pixel format.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS              Image processed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED      Library not initialized - call peak_afl_Init() first
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER    Invalid manager or image handle
 * \return #PEAK_AFL_STATUS_INVALID_IMAGE_FORMAT Unsupported image pixel format
 * \return #PEAK_AFL_STATUS_BUSY                 Manager is currently processing another image
 * \return #PEAK_AFL_STATUS_ERROR                Internal processing error occurred
 *
 * \note Check manager status with peak_afl_AutoFeatureManager_Status() before calling
 * \note Processing is asynchronous - use callbacks to detect completion
 * \note Only one image can be processed at a time per manager
 * \note Image must remain valid until processing completes
 * \note Controllers in OFF mode will not process the image
 *
 * \par Example:
 * ```c
 * // Check if manager is ready for processing
 * peak_afl_BOOL8 isRunning = PEAK_AFL_FALSE;
 * peak_afl_status status = peak_afl_AutoFeatureManager_Status(manager, &isRunning);
 *
 * if (status == PEAK_AFL_STATUS_SUCCESS && !isRunning) {
 *     // Manager is idle, safe to process new image
 *     status = peak_afl_AutoFeatureManager_Process(manager, imageHandle);
 *     if (status == PEAK_AFL_STATUS_SUCCESS) {
 *         printf("Image processing started\n");
 *     } else if (status == PEAK_AFL_STATUS_BUSY) {
 *         printf("Manager is busy, try again later\n");
 *     }
 * }
 * ```
 *
 * \see peak_afl_AutoFeatureManager_Status()
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_AutoController_Mode_Set()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_Process(peak_afl_manager_handle handle, PEAK_IPL_IMAGE_HANDLE imageHandle);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Create a controller and append it to Manager
 *
 * Convenience function that creates a new automatic feature controller of the specified type
 * and immediately adds it to the manager. This combines the functionality of
 * peak_afl_AutoController_Create() and peak_afl_AutoFeatureManager_AddController()
 * into a single operation for simplified workflow.
 *
 * Each manager can only contain one controller of each type. Attempting to add a second
 * controller of the same type will result in an error. The created controller is automatically
 * configured with default settings and can be further customized using the controller-specific
 * configuration functions.
 *
 * \param[in]  handle         Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[out] controller     Pointer to receive the new controller handle. Must not be NULL.
 *                           The handle will be set to a valid controller instance on success.
 * \param[in]  controllerType Type of controller to create and add:
 *                           - PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS: Automatic brightness/exposure control
 *                           - PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE: Automatic white balance control
 *                           - PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS: Automatic focus control
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller created and added successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle, controller pointer, or controller type
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The specified controller type is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note The created controller is automatically added to the manager and ready for use
 * \note Controllers are created with default configuration settings
 * \note Use controller-specific functions to customize behavior after creation
 * \note The controller will be destroyed automatically when the manager is destroyed
 * \note Check controller support with peak_afl_AutoFeatureManager_Controller_IsSupported() first
 *
 * \see peak_afl_AutoController_Create()
 * \see peak_afl_AutoFeatureManager_AddController()
 * \see peak_afl_AutoFeatureManager_Controller_IsSupported()
 * \see peak_afl_controllerType
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_CreateController(
    peak_afl_manager_handle handle, peak_afl_controller_handle* controller, peak_afl_controllerType controllerType);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Destroy all controllers associated with a manager
 *
 * Removes and destroys all controllers that have been added to the specified manager.
 * This is a convenience function for cleanup when shutting down the manager.
 *
 * \param[in] handle Manager handle
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           All controllers destroyed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \warning After this operation, all controller handles associated with the manager become invalid
 * \warning Do not use any controller handles after calling this function
 *
 * \note This function is typically called before destroying the manager
 * \note Individual controllers can be destroyed with peak_afl_AutoFeatureManager_DestroyController()
 *
 * \see peak_afl_AutoFeatureManager_DestroyController()
 * \see peak_afl_AutoFeatureManager_Destroy()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_DestroyAllController(peak_afl_manager_handle handle);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Destroy a controller from a manager
 *
 * Removes and destroys a specific controller from the auto feature manager.
 * This function combines the removal and destruction operations, making it a
 * convenient way to permanently remove a controller from the manager.
 * After successful destruction, the controller handle becomes invalid and
 * must not be used in any subsequent function calls.
 *
 * \param[in] handle     Auto feature manager handle containing the controller
 * \param[in] controller Controller handle to remove and destroy. Must be a controller
 *                      that was previously added to this specific manager.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller removed and destroyed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager or controller handle
 * \return #PEAK_AFL_STATUS_BUSY              Manager is currently processing an image
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \warning After this operation, the controller handle becomes invalid and must not be used
 * \warning Ensure the manager is not processing images before destroying controllers
 *
 * \note This function both removes the controller from the manager and destroys it
 * \note To remove without destroying, use peak_afl_AutoFeatureManager_RemoveController()
 * \note Check manager status with peak_afl_AutoFeatureManager_Status() before calling
 * \note Controllers can be recreated later if needed using peak_afl_AutoFeatureManager_CreateController()
 *
 * \see peak_afl_AutoFeatureManager_RemoveController()
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_AutoFeatureManager_Status()
 * \see peak_afl_AutoController_Destroy()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_DestroyController(
    peak_afl_manager_handle handle, peak_afl_controller_handle controller);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Set the IPL Gain for image processing
 *
 * Configures the Image Processing Library (IPL) gain settings for the auto feature manager.
 * The IPL gain is applied during image processing operations and affects how controllers
 * analyze and process images. This gain setting is separate from camera hardware gain
 * and is used for software-based image enhancement during automatic feature processing.
 *
 * The gain handle must be obtained from the imaging library using the appropriate
 * backend accessor. To get the handle for the gain, call GainBackendAccessor::BackendHandle(gain)
 * with gain being a peak::ipl::Gain object from the imaging library.
 *
 * \param[in] handle        Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[in] gainHandle    Handle to the IPL gain object from the imaging library.
 *                         Must be a valid gain handle obtained through GainBackendAccessor.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS         IPL gain configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle or gain handle
 * \return #PEAK_AFL_STATUS_ERROR           An unexpected internal error occurred
 *
 * \note The IPL gain affects software-based image processing, not camera hardware gain
 * \note The gain handle must remain valid while the manager is in use
 * \note This setting applies to all controllers within the manager
 * \note Changes take effect for subsequent image processing operations
 * \note IPL gain is applied before controllers analyze the image
 *
 * \see peak_afl_AutoFeatureManager_Process()
 * \see peak_afl_AutoFeatureManager_SetCCM()
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_SetGainIPL(peak_afl_manager_handle handle, PEAK_IPL_GAIN_HANDLE gainHandle);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Set the Color Correction Matrix (CCM)
 *
 * Configures a 3x3 Color Correction Matrix (CCM) for the auto feature manager.
 * The CCM is currently used exclusively by the Auto White Balance (AWB) controller.
 *
 * Internally, the inverse of the configured CCM is computed and used by the AWB
 * regulation algorithm so that the control loop operates on the original,
 * uncorrected image data. Therefore, the CCM must be configured if the input
 * image has already been processed using a Color Correction Matrix prior to
 * Auto White Balance.
 *
 * If no CCM is configured, an identity matrix is used as default.
 *
 * The matrix must be invertible. If the inverse matrix cannot be computed,
 * processing the image fails and an error is returned within the \link 
 * #PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING processing callback\endlink.
 *
 * The matrix must be provided as a flat array of 9 float values in row-major order:
 * [R->R, R->G, R->B, G->R, G->G, G->B, B->R, B->G, B->B], where each element represents
 * the contribution of the input color channel to the output color channel.
 *
 * \param[in] handle  Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[in] ccm     Pointer to an array of exactly 9 float values representing the 3x3 CCM.
 *                    Must not be NULL.
 * \param[in] ccmSize Size of the CCM array. Must be exactly 9 for a valid 3x3 matrix.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           CCM configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle, NULL CCM pointer,
 *                                                ccmSize not equal to 9
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note The CCM is used only by the Auto White Balance controller
 * \note The inverse CCM is applied internally for AWB regulation
 * \note Changes take effect for subsequent image processing operations
 * \note Use the identity matrix [1,0,0,0,1,0,0,0,1] if no prior color correction
 *       has been applied to the input image
 *
 * \see peak_afl_AutoFeatureManager_Process()
 * \see peak_afl_AutoFeatureManager_SetGainIPL()
 *
 * \since 1.8
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_SetCCM(peak_afl_manager_handle handle, float* ccm, size_t ccmSize);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Get the processing status of an auto feature manager
 *
 * Retrieves the current processing status of the auto feature manager to determine
 * whether it is currently processing an image or is idle and ready to accept new
 * image processing requests. This function is essential for coordinating image
 * processing operations and avoiding conflicts when multiple threads or processes
 * need to use the same manager.
 *
 * \param[in]  handle  Auto feature manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[out] running Pointer to receive the manager status:
 *                    - PEAK_AFL_TRUE: Manager is currently processing an image
 *                    - PEAK_AFL_FALSE: Manager is idle and ready for new processing
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Status retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid manager handle or NULL running pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before calling peak_afl_AutoFeatureManager_Process()
 * \note Only one image can be processed at a time per manager
 * \note This function is thread-safe and can be called from multiple threads
 * \note Use this for synchronization when sharing managers between threads
 *
 * \see peak_afl_AutoFeatureManager_Process()
 * \see peak_afl_AutoFeatureManager_Destroy()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_Status(peak_afl_manager_handle handle, peak_afl_BOOL8* running);

/*!
 * \ingroup ids_peak_afl_c_automanager
 * \brief Check if a controller type is supported by the manager
 *
 * Determines whether the specified controller type can be created and used
 * with this manager instance. Support may depend on the camera capabilities
 * and the current configuration.
 *
 * \param[in]  handle         Manager handle from peak_afl_AutoFeatureManager_Create()
 * \param[in]  controllerType Controller type to check for support
 * \param[out] supported      Pointer to receive support status:
 *                            - PEAK_AFL_TRUE: Controller type is supported
 *                            - PEAK_AFL_FALSE: Controller type is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid handle, controller type, or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \note Check support before attempting to create controllers
 * \note Support may vary between different camera models and configurations
 *
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_controllerType
 *
 * \since 1.11
 */
PEAK_AFL_API_STATUS peak_afl_AutoFeatureManager_Controller_IsSupported(
    peak_afl_manager_handle handle, peak_afl_controllerType controllerType, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Create a new auto feature controller
 *
 * Creates a new automatic feature controller of the specified type. Controllers
 * are responsible for analyzing images and adjusting specific camera parameters
 * to achieve optimal results. The created controller can be added to managers
 * for coordinated processing.
 *
 * \param[out] controller     Pointer to receive the new controller handle. Must not be NULL.
 *                           The handle will be set to a valid controller instance on success.
 * \param[in]  controllerType Type of controller to create:
 *                           - PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS: Automatic brightness/exposure control
 *                           - PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE: Automatic white balance control
 *                           - PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS: Automatic focus control
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller created successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   Library not initialized - call peak_afl_Init() first
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller pointer or unsupported controller type
 * \return #PEAK_AFL_STATUS_ERROR             Internal error during controller creation
 *
 * \note The created controller must be destroyed with peak_afl_AutoController_Destroy()
 * \note Controllers are initially configured with default settings
 * \note Controllers must be added to a manager before they can process images
 * \note Multiple controllers of the same type can be created for different configurations
 *
 * \par Example:
 * ```c
 * // Create a brightness controller
 * peak_afl_controller_handle brightnessCtrl = NULL;
 * peak_afl_status status = peak_afl_AutoController_Create(&brightnessCtrl,
 *                                                            PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS);
 * if (status == PEAK_AFL_STATUS_SUCCESS) {
 *     // Configure controller
 *     peak_afl_AutoController_Mode_Set(brightnessCtrl, PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS);
 *     peak_afl_AutoController_AutoTarget_Set(brightnessCtrl, 128);
 *
 *     // Add to manager for processing
 *     peak_afl_AutoFeatureManager_CreateController(manager, &brightnessCtrl,
 *                                                    PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS);
 *
 *     // Clean up when done
 *     peak_afl_AutoController_Destroy(brightnessCtrl);
 * }
 * ```
 *
 * \see peak_afl_AutoController_Destroy()
 * \see peak_afl_AutoFeatureManager_CreateController()
 * \see peak_afl_controllerType
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Create(
    peak_afl_controller_handle* controller, peak_afl_controllerType controllerType);

/*!
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Destroy a standalone controller
 *
 * Destroys an automatic feature controller that is not currently associated with any manager.
 * This function releases all resources allocated for the controller and invalidates the handle.
 * Controllers that are currently added to a manager cannot be destroyed directly and must
 * first be removed from the manager using peak_afl_AutoFeatureManager_RemoveController().
 *
 * \param[in] controller Controller handle to destroy. Must be a valid controller handle
 *                      obtained from peak_afl_AutoController_Create() and not currently
 *                      associated with any auto feature manager.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Controller destroyed successfully; handle is now invalid
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or handle is NULL
 * \return #PEAK_AFL_STATUS_ACCESS_DENIED     Controller is currently associated with a manager;
 *                                               remove it from the manager first
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \warning After this operation, the controller handle becomes invalid and must not be used
 * \warning Controllers associated with managers cannot be destroyed directly
 *
 * \note Controllers must be removed from managers before they can be destroyed independently
 * \note Use peak_afl_AutoFeatureManager_DestroyController() to remove and destroy in one operation
 * \note Controllers are automatically destroyed when their associated manager is destroyed
 * \note This function is primarily used for controllers that were created but never added to a manager
 *
 * \see peak_afl_AutoController_Create()
 * \see peak_afl_AutoFeatureManager_RemoveController()
 * \see peak_afl_AutoFeatureManager_DestroyController()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Destroy(peak_afl_controller_handle controller);

/*!
 * \ingroup ids_peak_afl_c_skip_frames
 * \brief Check if skip frames feature is supported for a controller
 *
 * Determines whether the specified controller supports the skip frames feature.
 * Skip frames allows controllers to process only every N-th image instead of
 * every image, which can be useful for performance and stabilization optimization or when full
 * frame rate processing is not required. Not all controller types support
 * this feature, and support may vary based on the specific implementation.
 *
 * \param[in]  controller Controller handle to check for skip frames support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: Skip frames feature is supported
 *                       - PEAK_AFL_FALSE: Skip frames feature is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to use skip frames functionality
 * \note Support may vary between different controller types
 * \note Even if supported, there may be limits on the skip frame count range
 *
 * \see peak_afl_AutoController_SkipFrames_Set()
 * \see peak_afl_AutoController_SkipFrames_Get()
 * \see peak_afl_AutoController_SkipFrames_GetRange()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SkipFrames_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_skip_frames
 * \brief Set number of frames to skip for a controller
 *
 * Configures the skip frames behavior for the specified controller. When skip frames
 * is enabled, the controller will only process every N-th image, where N is determined
 * by the count parameter. For example, setting count to 2 means the controller will
 * process every 2nd image (skipping 1 frame between processed frames). This feature
 * can be used to reduce computational load or when full frame rate processing is not required.
 *
 * \param[in] controller Controller handle for which to set skip frames behavior
 * \param[in] count      Number of frames to skip between processed frames.
 *                      - 0: Process every frame (no skipping)
 *                      - 1: Process every other frame (skip 1 frame)
 *                      - 2: Process every 3rd frame (skip 2 frames)
 *                      - etc.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Skip frames count set successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or count value out of range
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Skip frames feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_SkipFrames_IsSupported() before using
 * \note Use peak_afl_AutoController_SkipFrames_GetRange() to determine valid count values
 * \note Setting count to 0 disables frame skipping (processes every frame)
 * \note Changes take effect for subsequent image processing operations
 * \note Skip frames behavior is independent for each controller
 *
 * \see peak_afl_AutoController_SkipFrames_IsSupported()
 * \see peak_afl_AutoController_SkipFrames_Get()
 * \see peak_afl_AutoController_SkipFrames_GetRange()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SkipFrames_Set(peak_afl_controller_handle controller, uint32_t count);

/*!
 * \ingroup ids_peak_afl_c_skip_frames
 * \brief Get the current skip frames count for a controller
 *
 * Retrieves the current skip frames configuration for the specified controller.
 * This value determines how many frames the controller skips between processed frames.
 * For example, a count of 2 means the controller processes every 3rd frame (skipping 2 frames).
 * A count of 0 means no frames are skipped (every frame is processed).
 *
 * \param[in]  controller Controller handle to query for skip frames count
 * \param[out] count      Pointer to receive the current number of frames skipped between processed frames.
 *                       - 0: Process every frame (no skipping)
 *                       - 1: Process every other frame (skip 1 frame)
 *                       - 2: Process every 3rd frame (skip 2 frames)
 *                       - etc.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Skip frames count retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL count pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Skip frames feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_SkipFrames_IsSupported() before calling
 * \note Use peak_afl_AutoController_SkipFrames_GetRange() to determine valid count values
 * \note This function returns the current setting, not the number of frames actually skipped
 *
 * \see peak_afl_AutoController_SkipFrames_IsSupported()
 * \see peak_afl_AutoController_SkipFrames_Set()
 * \see peak_afl_AutoController_SkipFrames_GetRange()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SkipFrames_Get(peak_afl_controller_handle controller, uint32_t* count);

/*!
 * \ingroup ids_peak_afl_c_skip_frames
 * \brief Get the valid range for skip frames count
 *
 * Retrieves the minimum, maximum, and increment values for the skip frames count
 * that are supported by the specified controller. This information is essential
 * for determining valid values to use with peak_afl_AutoController_SkipFrames_Set().
 * The range may vary between different controller types and implementations.
 *
 * \param[in]  controller Controller handle to query for skip frames range
 * \param[out] min        Pointer to receive minimum number of frames that can be skipped.
 *                       Typically 0 (no skipping). May be NULL if not needed.
 * \param[out] max        Pointer to receive maximum number of frames that can be skipped.
 *                       May be NULL if not needed.
 * \param[out] inc        Pointer to receive increment step for skip frames count.
 *                       Usually 1, meaning any integer value in the range is valid.
 *                       May be NULL if not needed.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Range information retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Skip frames feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_SkipFrames_IsSupported() before calling
 * \note Any of the output parameters can be NULL if that information is not needed
 * \note Use this function to validate skip frames values before setting them
 * \note The increment value indicates the step size for valid skip frame counts
 *
 * \see peak_afl_AutoController_SkipFrames_IsSupported()
 * \see peak_afl_AutoController_SkipFrames_Set()
 * \see peak_afl_AutoController_SkipFrames_Get()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SkipFrames_GetRange(
    peak_afl_controller_handle controller, uint32_t* min, uint32_t* max, uint32_t* inc);

/*!
 * \ingroup ids_peak_afl_c_roi
 * \brief Check if region of interest (ROI) feature is supported for a controller
 *
 * Determines whether the specified controller supports the region of interest feature.
 * ROI allows controllers to focus their analysis on specific rectangular areas of the image
 * rather than processing the entire image. This can improve performance and accuracy by
 * excluding irrelevant areas from automatic feature processing. Not all controller types
 * support ROI functionality, and support may vary based on the specific implementation.
 *
 * \param[in]  controller Controller handle to check for ROI support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: ROI feature is supported
 *                       - PEAK_AFL_FALSE: ROI feature is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to use ROI functionality
 * \note Support may vary between different controller types
 * \note ROI can significantly improve processing performance for specific use cases
 *
 * \see peak_afl_AutoController_ROI_Set()
 * \see peak_afl_AutoController_ROI_Get()
 * \see peak_afl_AutoController_ROI_Preset_Set()
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ROI_IsSupported(peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_roi
 * \brief Set the region of interest for automatic feature processing
 *
 * Configures a rectangular region of interest (ROI) that limits the area of the image
 * where the controller performs its analysis. This allows focusing automatic features
 * on specific parts of the image, which can improve performance and accuracy by
 * excluding irrelevant areas from processing. If no ROI is set, the controller
 * evaluates the complete image.
 *
 * \param[in] controller Controller handle for which to set the ROI
 * \param[in] roi        Rectangle defining the region of interest with coordinates
 *                      relative to the image. To reset/disable ROI, set all values to 0.
 *                      The rectangle should be within the image boundaries.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           ROI configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or ROI coordinates
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     ROI feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_ROI_IsSupported() before using
 * \note ROI coordinates are relative to the processed image dimensions
 * \note Setting all ROI values to 0 disables ROI and processes the entire image
 * \note ROI changes take effect for subsequent image processing operations
 * \note Each controller can have its own independent ROI setting
 * \note ROI must be within valid image boundaries to avoid processing errors
 *
 * \see peak_afl_AutoController_ROI_IsSupported()
 * \see peak_afl_AutoController_ROI_Get()
 * \see peak_afl_AutoController_ROI_Preset_Set()
 * \see peak_afl_rectangle
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ROI_Set(peak_afl_controller_handle controller, peak_afl_rectangle roi);

/*!
 * \ingroup ids_peak_afl_c_roi
 * \brief Get the current region of interest for a controller
 *
 * Retrieves the current region of interest (ROI) configuration for the specified controller.
 * The ROI defines the rectangular area of the image where the controller performs its analysis.
 * If no ROI has been set, the returned rectangle will have all values set to 0, indicating
 * that the controller processes the entire image.
 *
 * \param[in] controller Controller handle to query for ROI configuration
 * \param[out] roi       Pointer to receive the current region of interest rectangle.
 *                      If no ROI is set, all rectangle values (x, y, width, height) will be 0.
 *                      Coordinates are relative to the image dimensions.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           ROI retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL roi pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     ROI feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_ROI_IsSupported() before calling
 * \note All zero values indicate no ROI is set (entire image is processed)
 * \note ROI coordinates are relative to the processed image dimensions
 * \note The returned ROI reflects the current active configuration
 *
 * \see peak_afl_AutoController_ROI_IsSupported()
 * \see peak_afl_AutoController_ROI_Set()
 * \see peak_afl_rectangle
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ROI_Get(peak_afl_controller_handle controller, peak_afl_rectangle* roi);

/*!
 * \ingroup ids_peak_afl_c_roi_preset
 * \brief Check if ROI preset feature is supported for a controller
 *
 * Determines whether the specified controller supports predefined region of interest presets.
 * ROI presets provide convenient, predefined rectangular regions that are commonly used
 * for automatic feature processing, such as center regions, corner regions, or specific
 * aspect ratio areas. This feature simplifies ROI configuration by offering standard
 * options instead of requiring manual coordinate specification.
 *
 * \param[in]  controller Controller handle to check for ROI preset support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: ROI preset feature is supported
 *                       - PEAK_AFL_FALSE: ROI preset feature is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to use ROI preset functionality
 * \note ROI preset support is independent of basic ROI support
 * \note Presets provide convenient alternatives to manual ROI coordinate specification
 * \note Available presets may vary between different controller implementations
 *
 * \see peak_afl_AutoController_ROI_Preset_Set()
 * \see peak_afl_AutoController_ROI_Set()
 * \see peak_afl_roi_preset
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ROI_Preset_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_roi_preset
 * \brief Set a predefined region of interest preset for a controller
 *
 * Configures the controller to use a predefined region of interest preset instead of
 * manually specified coordinates. ROI presets provide convenient, standardized rectangular
 * regions that are commonly used for automatic feature processing. This simplifies
 * configuration by offering well-tested region definitions without requiring manual
 * coordinate calculation.
 *
 * \param[in] controller Controller handle for which to set the ROI preset
 * \param[in] roiPreset  Predefined region of interest preset to apply. Available presets
 *                      may include center regions, corner areas, or specific aspect ratios.
 *                      See peak_afl_roi_preset for available options.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           ROI preset configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or unsupported preset value
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     ROI preset feature is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_ROI_Preset_IsSupported() before using
 * \note ROI presets override any manually set ROI coordinates
 * \note Preset regions are automatically scaled to match image dimensions
 * \note Changes take effect for subsequent image processing operations
 * \note Use peak_afl_AutoController_ROI_Set() for custom coordinate-based ROI
 *
 * \see peak_afl_AutoController_ROI_Preset_IsSupported()
 * \see peak_afl_AutoController_ROI_Set()
 * \see peak_afl_AutoController_ROI_Get()
 * \see peak_afl_roi_preset
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ROI_Preset_Set(peak_afl_controller_handle controller, peak_afl_roi_preset roiPreset);

/*!
 * \ingroup ids_peak_afl_c_controller_mode
 * \brief Check if automatic mode configuration is supported for a controller
 *
 * Determines whether the specified controller supports automatic mode configuration.
 * Automatic modes control how and when the controller processes images and adjusts
 * camera parameters. Different modes include continuous processing, one-shot operation,
 * or disabled state. Not all controller types support mode configuration, and available
 * modes may vary between different controller implementations.
 *
 * \param[in]  controller Controller handle to check for automatic mode support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: Automatic mode configuration is supported
 *                       - PEAK_AFL_FALSE: Automatic mode configuration is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to configure controller modes
 * \note Mode support may vary between different controller types
 * \note Available modes are defined in peak_afl_controller_automode
 *
 * \see peak_afl_AutoController_Mode_Set()
 * \see peak_afl_AutoController_Mode_Get()
 * \see peak_afl_controller_automode
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Mode_IsSupported(peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_controller_mode
 * \brief Set the automatic processing mode for a controller
 *
 * Configures how the controller processes images and adjusts camera parameters.
 * The automatic mode determines the controller's behavior during image processing,
 * such as whether it operates continuously, performs one-shot adjustments, or
 * remains disabled. Different modes provide different levels of automation and
 * control over when parameter adjustments occur.
 *
 * \param[in] controller Controller handle for which to set the automatic mode
 * \param[in] mode       Automatic processing mode to configure. Available modes include:
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_OFF: Controller is disabled
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_ONCE: One-shot processing
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS: Continuous processing
 *                      See peak_afl_controller_automode for complete list.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Automatic mode configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or unsupported mode value
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Mode configuration is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_Mode_IsSupported() before using
 * \note Mode changes take effect for subsequent image processing operations
 * \note OFF mode disables all automatic adjustments by the controller
 * \note CONTINUOUS mode processes every image (subject to skip frames settings)
 * \note ONCE mode processes a single image then switches to OFF mode
 *
 * \see peak_afl_AutoController_Mode_IsSupported()
 * \see peak_afl_AutoController_Mode_Get()
 * \see peak_afl_controller_automode
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Mode_Set(peak_afl_controller_handle controller, peak_afl_controller_automode mode);

/*!
 * \ingroup ids_peak_afl_c_controller_mode
 * \brief Get the current automatic processing mode for a controller
 *
 * Retrieves the current automatic processing mode configuration for the specified controller.
 * The mode determines how the controller behaves during image processing operations,
 * including whether it actively processes images, performs one-shot adjustments, or
 * remains disabled. This information is useful for understanding the controller's
 * current operational state and for debugging processing behavior.
 *
 * \param[in]  controller Controller handle to query for automatic mode
 * \param[out] mode       Pointer to receive the current automatic processing mode:
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_OFF: Controller is disabled
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_ONCE: One-shot processing mode
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS: Continuous processing mode
 *                       See peak_afl_controller_automode for all possible values.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Automatic mode retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL mode pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Mode configuration is not supported by this controller
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_Mode_IsSupported() before calling
 * \note The returned mode reflects the current active configuration
 * \note ONCE mode may automatically change to OFF after processing one image
 * \note Use this function to verify mode settings after configuration
 *
 * \see peak_afl_AutoController_Mode_IsSupported()
 * \see peak_afl_AutoController_Mode_Set()
 * \see peak_afl_controller_automode
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Mode_Get(peak_afl_controller_handle controller, peak_afl_controller_automode* mode);

/*!
 * \ingroup ids_peak_afl_c_brightness_algorithm
 * \brief Set the brightness analysis algorithm for a controller
 *
 * Configures the algorithm used by the brightness controller to analyze image brightness
 * and determine appropriate exposure or gain adjustments. Different algorithms use various
 * statistical methods to evaluate image brightness, such as mean calculation, percentile
 * analysis, or weighted averaging. The choice of algorithm affects how the controller
 * responds to different lighting conditions and image content.
 *
 * \param[in] controller Controller handle for which to set the brightness algorithm
 * \param[in] algorithm  Brightness analysis algorithm to use. Available algorithms include
 *                      different statistical methods for brightness evaluation.
 *                      See peak_afl_controller_brightness_algorithm for available options.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness algorithm configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or unsupported algorithm
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Brightness algorithm configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_BrightnessAlgorithm_IsSupported() before using
 * \note Algorithm changes take effect for subsequent image processing operations
 * \note Different algorithms may perform better under different lighting conditions
 * \note The algorithm affects how target brightness values are interpreted
 * \note This setting applies only to brightness-type controllers
 *
 * \see peak_afl_AutoController_BrightnessAlgorithm_IsSupported()
 * \see peak_afl_AutoController_BrightnessAlgorithm_Get()
 * \see peak_afl_controller_brightness_algorithm
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessAlgorithm_Set(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_algorithm algorithm);

/*!
 * \ingroup ids_peak_afl_c_brightness_algorithm
 * \brief Get the current brightness analysis algorithm for a controller
 *
 * Retrieves the current brightness analysis algorithm configuration for the specified
 * brightness controller. The algorithm determines how the controller evaluates image
 * brightness and calculates appropriate parameter adjustments. This information is
 * useful for understanding the controller's analysis behavior and for debugging
 * brightness control performance.
 *
 * \param[in]  controller Controller handle to query for brightness algorithm
 * \param[out] algorithm  Pointer to receive the current brightness analysis algorithm.
 *                       The value indicates which statistical method is being used
 *                       for brightness evaluation. See peak_afl_controller_brightness_algorithm
 *                       for possible values and their meanings.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness algorithm retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL algorithm pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Brightness algorithm configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_BrightnessAlgorithm_IsSupported() before calling
 * \note The returned algorithm reflects the current active configuration
 * \note This function only applies to brightness-type controllers
 * \note Use this to verify algorithm settings after configuration
 *
 * \see peak_afl_AutoController_BrightnessAlgorithm_IsSupported()
 * \see peak_afl_AutoController_BrightnessAlgorithm_Set()
 * \see peak_afl_controller_brightness_algorithm
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessAlgorithm_Get(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_algorithm* algorithm);

/*!
 * \ingroup ids_peak_afl_c_brightness_algorithm
 * \brief Check if brightness algorithm configuration is supported for a controller
 *
 * Determines whether the specified controller supports brightness algorithm configuration.
 * Brightness algorithm configuration allows selection of different statistical methods
 * for analyzing image brightness, such as mean calculation, percentile analysis, or
 * weighted averaging. Not all controllers support algorithm selection, and this feature
 * is typically available only for brightness-type controllers.
 *
 * \param[in]  controller Controller handle to check for brightness algorithm support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: Brightness algorithm configuration is supported
 *                       - PEAK_AFL_FALSE: Brightness algorithm configuration is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to configure brightness algorithms
 * \note This feature is typically available only for brightness-type controllers
 * \note Algorithm support may vary between different controller implementations
 * \note Available algorithms are defined in peak_afl_controller_brightness_algorithm
 *
 * \see peak_afl_AutoController_BrightnessAlgorithm_Set()
 * \see peak_afl_AutoController_BrightnessAlgorithm_Get()
 * \see peak_afl_controller_brightness_algorithm
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessAlgorithm_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_brightness_mode
 * \brief Check if brightness component mode configuration is supported for a controller
 *
 * Determines whether the specified controller supports individual brightness component
 * mode configuration. This feature allows independent control of different brightness
 * adjustment mechanisms (such as exposure time, analog gain, digital gain) within a
 * single brightness controller. Each component can be configured with its own automatic
 * mode, providing fine-grained control over brightness adjustment behavior.
 *
 * \param[in]  controller Controller handle to check for brightness component mode support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: Brightness component mode configuration is supported
 *                       - PEAK_AFL_FALSE: Brightness component mode configuration is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to configure individual component modes
 * \note This feature is typically available only for advanced brightness controllers
 * \note Component mode support may vary between different controller implementations
 * \note Available components are defined in peak_afl_controller_brightness_component
 *
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Set()
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Get()
 * \see peak_afl_controller_brightness_component
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Mode_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_brightness_component
 * \brief Check if a specific brightness component unit is supported for a controller
 *
 * Determines whether the specified brightness controller supports a particular brightness
 * component unit. Brightness controllers can use different mechanisms to adjust image
 * brightness, such as exposure time, analog gain, digital gain, or combined gain settings.
 * This function allows checking which specific brightness adjustment mechanisms are
 * available for independent configuration and control.
 *
 * \param[in]  controller Controller handle to check for brightness component support
 * \param[in]  unit       Brightness component unit to check for support. Available units
 *                       include exposure, analog gain, digital gain, and other brightness
 *                       adjustment mechanisms. See peak_afl_controller_brightness_component
 *                       for available options.
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: The specified brightness component unit is supported
 *                       - PEAK_AFL_FALSE: The specified brightness component unit is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle, unit, or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to configure specific brightness components
 * \note Component support may vary between different camera models and controller implementations
 * \note This function is typically used with advanced brightness controllers
 * \note Available components depend on camera hardware capabilities
 *
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Set()
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Get()
 * \see peak_afl_controller_brightness_component
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Unit_IsSupported(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_component unit, peak_afl_BOOL8* supported);
/*!
 * \ingroup ids_peak_afl_c_brightness_mode
 * \brief Set the automatic mode for a specific brightness component
 *
 * Configures the automatic processing mode for an individual brightness component within
 * a brightness controller. This allows fine-grained control over how different brightness
 * adjustment mechanisms (such as exposure time, analog gain, digital gain) operate
 * independently. Each component can be set to different modes, enabling sophisticated
 * brightness control strategies that prioritize certain adjustment methods over others.
 *
 * \param[in] controller Controller handle for which to set the brightness component mode
 * \param[in] component  Brightness component to configure. Available components include
 *                      exposure time, analog gain, digital gain, and other brightness
 *                      adjustment mechanisms. See peak_afl_controller_brightness_component
 *                      for available options.
 * \param[in] mode       Automatic processing mode for the specified component:
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_OFF: Component is disabled
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_ONCE: One-shot adjustment
 *                      - PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS: Continuous adjustment
 *                      See peak_afl_controller_automode for complete list.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness component mode configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle, component, or mode
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Component mode configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_BrightnessComponent_Mode_IsSupported() before using
 * \note Component mode changes take effect for subsequent image processing operations
 * \note Different components can have different modes for sophisticated control strategies
 * \note This feature is typically available only for advanced brightness controllers
 *
 * \see peak_afl_AutoController_BrightnessComponent_Mode_IsSupported()
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Get()
 * \see peak_afl_controller_brightness_component
 * \see peak_afl_controller_automode
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Mode_Set(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_component component, peak_afl_controller_automode mode);

/*!
 * \ingroup ids_peak_afl_c_brightness_mode
 * \brief Get the current automatic mode for a specific brightness component
 *
 * Retrieves the current automatic processing mode configuration for an individual
 * brightness component within a brightness controller. This allows inspection of
 * how different brightness adjustment mechanisms are currently configured to operate.
 * The information is useful for understanding the controller's current behavior and
 * for debugging brightness control performance.
 *
 * \param[in]  controller Controller handle to query for brightness component mode
 * \param[in]  component  Brightness component to query. Available components include
 *                       exposure time, analog gain, digital gain, and other brightness
 *                       adjustment mechanisms. See peak_afl_controller_brightness_component
 *                       for available options.
 * \param[out] mode       Pointer to receive the current automatic processing mode:
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_OFF: Component is disabled
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_ONCE: One-shot adjustment mode
 *                       - PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS: Continuous adjustment mode
 *                       See peak_afl_controller_automode for all possible values.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness component mode retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle, component, or NULL mode pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Component mode configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_BrightnessComponent_Mode_IsSupported() before calling
 * \note The returned mode reflects the current active configuration for the specified component
 * \note Different components can have different modes within the same controller
 * \note Use this function to verify component mode settings after configuration
 *
 * \see peak_afl_AutoController_BrightnessComponent_Mode_IsSupported()
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Set()
 * \see peak_afl_controller_brightness_component
 * \see peak_afl_controller_automode
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Mode_Get(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_component component, peak_afl_controller_automode* mode);

/*!
 * \ingroup ids_peak_afl_c_brightness_component
 * \brief Get the operational status for a specific brightness component
 *
 * Retrieves the current operational status of an individual brightness component within
 * a brightness controller. The status indicates the component's current state, such as
 * whether it is actively processing, has converged to target values, encountered errors,
 * or is idle. This information is valuable for monitoring controller performance and
 * diagnosing issues with specific brightness adjustment mechanisms.
 *
 * \param[in]  controller Controller handle to query for brightness component status
 * \param[in]  component  Brightness component to query. Available components include
 *                       exposure time, analog gain, digital gain, and other brightness
 *                       adjustment mechanisms. See peak_afl_controller_brightness_component
 *                       for available options.
 * \param[out] status     Pointer to receive the current operational status of the component.
 *                       Status values indicate processing state, convergence, errors, etc.
 *                       See peak_afl_controller_status for possible values and meanings.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness component status retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle, component, or NULL status pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Component status monitoring is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Component status is updated during image processing operations
 * \note Different components can have different statuses within the same controller
 * \note Use this function to monitor individual component performance and convergence
 * \note Status information is useful for debugging brightness control issues
 *
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Set()
 * \see peak_afl_AutoController_BrightnessComponent_Mode_Get()
 * \see peak_afl_controller_brightness_component
 * \see peak_afl_controller_status
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Status(
    peak_afl_controller_handle controller, peak_afl_controller_brightness_component component, peak_afl_controller_status* status);

/*!
 * \ingroup ids_peak_afl_c_brightness_callback
 * \brief Set a callback function for a specific brightness component
 *
 * Configures a callback function that will be invoked when specific events occur
 * for an individual brightness component within a brightness controller. Callbacks
 * provide asynchronous notification of component state changes, processing completion,
 * convergence events, or errors. This enables responsive application behavior and
 * real-time monitoring of brightness adjustment mechanisms.
 *
 * \param[in]  controller Controller handle for which to set the brightness component callback
 * \param[in]  component  Brightness component for which to configure the callback. Available
 *                       components include exposure time, analog gain, digital gain, and other
 *                       brightness adjustment mechanisms. See peak_afl_controller_brightness_component
 *                       for available options.
 * \param[in]  type       Type of callback event to monitor. Different types correspond to
 *                       different component events such as processing completion, convergence,
 *                       or status changes. See peak_afl_callback_type for available options.
 * \param[in]  funcPtr    Function pointer to the callback function. Set to NULL to disable
 *                       the callback, or provide a valid function pointer to enable it.
 *                       The callback signature must match the specified callback type.
 * \param[in]  context    User-defined context pointer that will be passed as the last parameter
 *                       to the callback function. Can be NULL if no context is needed.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Brightness component callback configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle, component, or callback type
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Component callbacks are not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Set funcPtr to NULL to disable the callback for the specified component and type
 * \note The callback function will be called from the processing thread context
 * \note Multiple callback types can be configured for the same component
 * \note The context pointer is passed unchanged to the callback function
 * \note Callback functions should be lightweight to avoid impacting processing performance
 *
 * \see peak_afl_AutoController_BrightnessComponent_Status()
 * \see peak_afl_controller_brightness_component
 * \see peak_afl_callback_type
 *
 * \since 1.2
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_BrightnessComponent_Callback_Set(peak_afl_controller_handle controller,
    peak_afl_controller_brightness_component component, peak_afl_callback_type type, void* funcPtr, void* context);

/*!
 * \ingroup ids_peak_afl_c_exposure_limit
 * \brief Check if exposure limit configuration is supported for a controller
 *
 * Determines whether the specified controller supports exposure limit configuration.
 * Exposure limits allow constraining the automatic exposure adjustments to a specific
 * range, preventing the controller from setting exposure times that are too short
 * (causing underexposure) or too long (causing motion blur or overexposure). This
 * feature is particularly useful in applications with specific timing requirements
 * or motion sensitivity.
 *
 * \param[in]  controller Controller handle to check for exposure limit support
 * \param[out] supported  Pointer to receive support status:
 *                       - PEAK_AFL_TRUE: Exposure limit configuration is supported
 *                       - PEAK_AFL_FALSE: Exposure limit configuration is not supported
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation completed successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL supported pointer
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check this function before attempting to configure exposure limits
 * \note Exposure limit support is typically available for brightness controllers
 * \note Limits help prevent inappropriate exposure settings in automatic mode
 * \note This feature is useful for applications with motion or timing constraints
 *
 * \see peak_afl_AutoController_ExposureLimit_Set()
 * \see peak_afl_AutoController_ExposureLimit_Get()
 * \see peak_afl_double_limit
 *
 * \since 1.4
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ExposureLimit_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_exposure_limit
 * \brief Set exposure time limits for automatic exposure control
 *
 * Configures the minimum and maximum exposure time limits that constrain the automatic
 * exposure adjustments performed by the controller. The controller will only adjust
 * exposure times within the specified range, preventing exposure settings that could
 * cause underexposure (too short) or motion blur/overexposure (too long). This is
 * essential for applications with specific timing requirements or motion sensitivity.
 *
 * \param[in]  controller Controller handle for which to set exposure limits
 * \param[in]  limit      Exposure time limit structure containing minimum and maximum
 *                       exposure times in seconds. The controller will constrain all
 *                       automatic exposure adjustments to this range. Both min and max
 *                       values must be positive, and min must be less than or equal to max.

 * \return #PEAK_AFL_STATUS_SUCCESS           Exposure limits configured successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or limit values
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Exposure limit configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_ExposureLimit_IsSupported() before using
 * \note Limit values are in seconds and must be within camera hardware capabilities
 * \note Setting limits too narrow may prevent the controller from achieving target brightness
 * \note Changes take effect for subsequent image processing operations
 * \note The controller will prioritize staying within limits over achieving exact target brightness
 *
 * \see peak_afl_AutoController_ExposureLimit_IsSupported()
 * \see peak_afl_AutoController_ExposureLimit_Get()
 * \see peak_afl_double_limit
 *
 * \since 1.4
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ExposureLimit_Set(peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_exposure_limit
 * \brief Get the current exposure time limits for a controller
 *
 * Retrieves the current exposure time limit configuration for the specified controller.
 * The limits define the minimum and maximum exposure times that constrain automatic
 * exposure adjustments. This information is useful for understanding the controller's
 * operational constraints and for verifying limit configurations.
 *
 * \param[in]   controller Controller handle to query for exposure limits
 * \param[out]  limit      Pointer to receive the current exposure time limits structure
 *                        containing minimum and maximum exposure times in seconds.
 *                        If no limits have been set, default values may be returned.

 * \return #PEAK_AFL_STATUS_SUCCESS           Exposure limits retrieved successfully
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER Invalid controller handle or NULL limit pointer
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     Exposure limit configuration is not supported
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred
 *
 * \note Check support with peak_afl_AutoController_ExposureLimit_IsSupported() before calling
 * \note The returned limits reflect the current active configuration
 * \note Limit values are in seconds and represent actual camera capabilities
 * \note Use this function to verify limit settings after configuration
 * \note Default limits may correspond to camera hardware capabilities
 *
 * \see peak_afl_AutoController_ExposureLimit_IsSupported()
 * \see peak_afl_AutoController_ExposureLimit_Set()
 * \see peak_afl_double_limit
 *
 * \since 1.4
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ExposureLimit_Get(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_exposure_limit
 * \brief Get autofeature exposure limit range for a controller
 *
 * Retrieves the valid range of exposure limit values that can be configured
 * for this controller. The returned range defines the minimum and maximum
 * permissible exposure values supported by the system.
 *
 * Before setting exposure limits using #peak_afl_AutoController_ExposureLimit_Set,
 * ensure that the specified values fall within this range.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for exposure limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range.
 *                                                The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \see peak_afl_AutoController_ExposureLimit_IsSupported()
 * \see peak_afl_AutoController_ExposureLimit_Set()
 * \see peak_afl_AutoController_ExposureLimit_Get()
 * \see peak_afl_double_limit
 *
 * \since 1.3
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_ExposureLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Get the status for a controller.
 *
 * Retrieves the current operational status of the specified auto controller.
 * This function provides information about whether the controller is active,
 * idle, processing, or in an error state. The status can be used to monitor
 * the controller's operation and determine if it's ready to accept new commands
 * or if it's currently busy processing image data.
 *
 * See #peak_afl_controller_status for a list of possible status values.
 *
 * \note This function can be called at any time to check the controller state.
 * \note The status may change rapidly during active processing operations.
 *
 * \param[in]  controller controller handle
 * \param[out] status     controller status
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Status(peak_afl_controller_handle controller, peak_afl_controller_status* status);

/*!
 * \ingroup ids_peak_afl_c_brightness
 * \brief Get the last auto average for a controller.
 *
 * Used by Controllers processing a mono image. This function retrieves the
 * most recent calculated average value from the auto feature processing.
 * The average represents the calculated brightness level from the last
 * processed frame.
 *
 * \param[in]  controller controller handle
 * \param[out] average    autofeature average
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GetLastAutoAverage(peak_afl_controller_handle controller, uint8_t* average);

/*!
 * \ingroup ids_peak_afl_c_whitebalance
 * \brief Get the last auto average for a controller.
 *
 * Used by Controllers processing a color image. This function retrieves the
 * most recent calculated average values for each color channel (RGB) from
 * the auto feature processing. These averages represent the calculated
 * brightness levels for each color channel from the last processed frame.
 *
 * \param[in]  controller   controller handle
 * \param[out] averageRed   autofeature average red channel
 * \param[out] averageGreen autofeature average green channel
 * \param[out] averageBlue  autofeature average blue channel
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GetLastAutoAverages(
    peak_afl_controller_handle controller, uint8_t* averageRed, uint8_t* averageGreen, uint8_t* averageBlue);

/*!
 * \ingroup ids_peak_afl_c_auto_target
 * \brief Check if auto target is supported for a controller.
 *
 * If \p supported is #PEAK_AFL_TRUE auto target is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports auto target
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTarget_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_auto_target
 * \brief Set the auto target for a controller.
 *
 * Set an auto target value that the controller will attempt to achieve.
 * Call #peak_afl_AutoController_AutoTarget_GetRange to get the valid range.
 * This is the target value which will be aimed for by the controller during
 * automatic adjustment operations.
 *
 * \param[in] controller controller handle
 * \param[in] target     auto target value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTarget_Set(peak_afl_controller_handle controller, uint32_t target);

/*!
 * \ingroup ids_peak_afl_c_auto_target
 * \brief Get the currently set auto target for a controller.
 *
 * Retrieves the target value that the controller is currently configured to achieve.
 * This is the same value that was previously set using #peak_afl_AutoController_AutoTarget_Set.
 * The target represents the desired output level (e.g., brightness, white balance point)
 * that the automatic adjustment algorithm will attempt to maintain.
 *
 * \param[in]  controller controller handle
 * \param[out] target     auto target value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTarget_Get(peak_afl_controller_handle controller, uint32_t* target);

/*!
 * \ingroup ids_peak_afl_c_auto_target
 * \brief Get the auto target range for a controller.
 *
 * Retrieves the valid range of target values that can be configured for this controller.
 * This function provides the minimum and maximum allowable target values, as well as
 * the increment step size. The range depends on the controller type and the underlying
 * hardware capabilities.
 *
 * Call this function before setting a target value to ensure the desired value is
 * within the supported range. Use #peak_afl_AutoController_AutoTarget_Set to
 * actually configure the target value.
 *
 * \note The range may vary depending on the current controller configuration.
 * \note Always check the range before setting new target values to avoid errors.
 *
 * \param[in]  controller controller handle
 * \param[out] min        auto target minimum value
 * \param[out] max        auto target maximum value
 * \param[out] inc        auto target increment value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTarget_GetRange(
    peak_afl_controller_handle controller, uint32_t* min, uint32_t* max, uint32_t* inc);

/*!
 * \ingroup ids_peak_afl_c_auto_tolerance
 * \brief Check if auto tolerance is supported for a controller.
 *
 * If \p supported is #PEAK_AFL_TRUE auto tolerance is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports auto tolerance
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTolerance_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_auto_tolerance
 * \brief Set the auto tolerance for a controller.
 *
 * Sets the tolerance range around the auto target value. The tolerance defines
 * the acceptable deviation from the target before the controller will make
 * adjustments. For example, if the target is 128 and tolerance is 5, the
 * controller will only adjust when the measured value falls outside the
 * range of 123-133. This helps prevent oscillation and provides stable
 * operation by creating a "dead zone" around the target value.
 *
 * A smaller tolerance provides more precise control but may cause more
 * frequent adjustments. A larger tolerance provides more stable operation
 * but with less precision.
 *
 * \param[in] controller controller handle
 * \param[in] tolerance  auto tolerance value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTolerance_Set(peak_afl_controller_handle controller, uint32_t tolerance);

/*!
 * \ingroup ids_peak_afl_c_auto_tolerance
 * \brief Get the current auto tolerance for a controller.
 *
 * Retrieves the currently configured tolerance value that defines the acceptable
 * deviation range around the auto target. This is the same value that was
 * previously set using #peak_afl_AutoController_AutoTolerance_Set.
 *
 * \param[in]  controller controller handle
 * \param[out] tolerance  auto tolerance value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTolerance_Get(peak_afl_controller_handle controller, uint32_t* tolerance);

/*!
 * \ingroup ids_peak_afl_c_auto_tolerance
 * \brief Get the auto tolerance range for a controller.
 *
 * Retrieves the valid range of tolerance values that can be configured for this
 * controller. The range provides the minimum and maximum allowable tolerance
 * values, as well as the increment step size. The available range depends on
 * the controller type and implementation.
 *
 * Call this function to determine valid tolerance values before calling
 * #peak_afl_AutoController_AutoTolerance_Set to avoid parameter errors.
 *
 * \param[in]  controller controller handle
 * \param[out] min        auto tolerance minimum value
 * \param[out] max        auto tolerance maximum value
 * \param[out] inc        auto tolerance increment value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoTolerance_GetRange(
    peak_afl_controller_handle controller, uint32_t* min, uint32_t* max, uint32_t* inc);

/*!
 * \ingroup ids_peak_afl_c_auto_percentile
 * \brief Check if auto percentile is supported for a controller.
 *
 * If \p supported is #PEAK_AFL_TRUE auto percentile is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports auto percentile
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoPercentile_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_auto_percentile
 * \brief Set the auto percentile for a controller.
 *
 * This sets the percentile value used for statistical analysis by the controller.
 * The percentile determines which portion of the histogram is used for calculations.
 * For example, a value of 0.95 means the 95th percentile will be used.
 * To get the valid range, call #peak_afl_AutoController_AutoPercentile_GetRange.
 *
 * \param[in] controller controller handle
 * \param[in] percentile auto percentile value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoPercentile_Set(peak_afl_controller_handle controller, double percentile);

/*!
 * \ingroup ids_peak_afl_c_auto_percentile
 * \brief Get the auto percentile for a controller.
 *
 * Retrieves the currently configured percentile value used for statistical
 * analysis by the controller. This is the same value that was previously
 * set using #peak_afl_AutoController_AutoPercentile_Set.
 *
 * \param[in]  controller controller handle
 * \param[out] percentile auto percentile value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoPercentile_Get(peak_afl_controller_handle controller, double* percentile);

/*!
 * \ingroup ids_peak_afl_c_auto_percentile
 * \brief Get the auto percentile range for a controller.
 *
 * Retrieves the valid range of percentile values that can be configured for this
 * controller. Percentile values are typically expressed as decimal values between
 * 0.0 and 1.0 (representing 0% to 100%). The range provides the minimum and
 * maximum allowable percentile values, as well as the increment step size.
 *
 * Call this function to determine valid percentile values before calling
 * #peak_afl_AutoController_AutoPercentile_Set to ensure the desired percentile
 * is within the supported range.
 *
 * \param[in]  controller controller handle
 * \param[out] min        auto percentile minimum value
 * \param[out] max        auto percentile maximum value
 * \param[out] inc        auto percentile increment value
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_AutoPercentile_GetRange(
    peak_afl_controller_handle controller, double* min, double* max, double* inc);

/*!
 * \ingroup ids_peak_afl_c_autocontroller
 * \brief Get the controller type.
 *
 * Retrieves the type of the specified auto controller, which indicates what
 * kind of automatic adjustment it performs (e.g., brightness, white balance,
 * focus). The controller type determines which features and parameters are
 * available and how the controller processes image data.
 *
 * This information is useful for determining the capabilities of a controller
 * and for configuring type-specific parameters.
 *
 * See #peak_afl_controllerType for a list of possible controller types.
 *
 * \param[in]  controller controller handle
 * \param[out] type       auto controller type
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Type_Get(peak_afl_controller_handle controller, peak_afl_controllerType* type);

/*!
 * \ingroup ids_peak_afl_c_focus_algorithm
 * \brief Check if setting an algorithm is supported for a controller.
 *
 * If \p supported is #PEAK_AFL_TRUE algorithm is supported, otherwise it is unsupported.
 *
 * Call #peak_afl_AutoController_Algorithm_GetList to get a list of supported algorithms.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports setting an algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Algorithm_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_focus_algorithm
 * \brief Set the used algorithm for a controller.
 *
 * Configures the algorithm that the controller will use for automatic adjustments.
 * Different algorithms may provide different performance characteristics, accuracy,
 * or speed. The choice of algorithm can significantly impact the controller's
 * behavior and the quality of automatic adjustments.
 *
 * The available algorithms depend on the controller type and implementation.
 * To get a list of supported algorithms for this controller, call
 * #peak_afl_AutoController_Algorithm_GetList first.
 *
 * \param[in]  controller controller handle
 * \param[in]  algorithm  auto controller algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Algorithm_Set(
    peak_afl_controller_handle controller, peak_afl_controller_algorithm algorithm);

/*!
 * \ingroup ids_peak_afl_c_focus_algorithm
 * \brief Get the used algorithm for a controller.
 *
 * Retrieves the currently configured algorithm that the controller is using
 * for automatic adjustments. This is the same algorithm that was previously
 * set using #peak_afl_AutoController_Algorithm_Set.
 *
 * \param[in]  controller controller handle
 * \param[out] algorithm  auto controller algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Algorithm_Get(
    peak_afl_controller_handle controller, peak_afl_controller_algorithm* algorithm);

/*!
 * \ingroup ids_peak_afl_c_focus_algorithm
 * \brief Get the list of supported algorithms for a controller.
 *
 * Retrieves all algorithms that are supported by the specified controller.
 * This function allows you to discover which algorithms are available before
 * attempting to configure one. Different controllers may support different
 * sets of algorithms based on their implementation and capabilities.
 *
 * Uses the \ref principle_two_stage_query principle: call first with NULL
 * to get the required buffer size, then call again with an allocated buffer
 * to retrieve the actual algorithm list.
 *
 * To set a specific algorithm, see #peak_afl_AutoController_Algorithm_Set.
 *
 * \param[in]     controller  controller handle
 * \param[out]    typeList    Pointer to a user allocated list of #peak_afl_controller_algorithm.
 *                            If this parameter is NULL, \p listSize will contain the needed count of \p typeList.
 * \param[in,out] listSize    Size of \p typeList:<br>
 *                            \li \p typeList equal NULL: <br>
 *                                out: minimal size of \p listSize in count of #peak_afl_controller_algorithm to hold the list <br>
 *                            \li \p typeList unequal NULL: <br>
 *                                in: size of the provided \p lastErrorMessage in counts of #peak_afl_controller_algorithm <br>
 *                                out: number of #peak_afl_controller_algorithm used by the function
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_BUFFER_TOO_SMALL  The supplied buffer is too small.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Algorithm_GetList(
    peak_afl_controller_handle controller, peak_afl_controller_algorithm* typeList, uint32_t* listSize);

/*!
 * \ingroup ids_peak_afl_c_sharpness_algorithm
 * \brief Check if setting a sharpness algorithm is supported by a controller.
 *
 * If \p supported is #PEAK_AFL_TRUE sharpness algorithm is supported, otherwise it is unsupported.
 *
 * Call #peak_afl_AutoController_SharpnessAlgorithm_GetList to get a list of supported sharpness algorithms.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports setting a sharpness algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SharpnessAlgorithm_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_sharpness_algorithm
 * \brief Set the used sharpness algorithm for a controller.
 *
 * Configures the sharpness algorithm that the controller will use for focus
 * evaluation and automatic focus adjustments. Different sharpness algorithms
 * use different mathematical approaches to measure image sharpness, which can
 * affect focus accuracy and speed in different scenarios.
 *
 * The choice of sharpness algorithm can be critical for optimal focus performance,
 * especially in challenging lighting conditions or with specific types of subjects.
 *
 * To get a list of supported sharpness algorithms for this controller, call
 * #peak_afl_AutoController_SharpnessAlgorithm_GetList first.
 *
 * \param[in]  controller controller handle
 * \param[in]  algorithm  auto controller sharpness algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SharpnessAlgorithm_Set(
    peak_afl_controller_handle controller, peak_afl_controller_sharpness_algorithm algorithm);

/*!
 * \ingroup ids_peak_afl_c_sharpness_algorithm
 * \brief Get the used sharpness algorithm for a controller.
 *
 * Retrieves the currently configured sharpness algorithm that the controller
 * is using for focus evaluation. This is the same algorithm that was previously
 * set using #peak_afl_AutoController_SharpnessAlgorithm_Set.
 *
 * \param[in]  controller controller handle
 * \param[out] algorithm  auto controller sharpness algorithm
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SharpnessAlgorithm_Get(
    peak_afl_controller_handle controller, peak_afl_controller_sharpness_algorithm* algorithm);

/*!
 * \ingroup ids_peak_afl_c_sharpness_algorithm
 * \brief Get the list of supported sharpness algorithms for a controller.
 *
 * Retrieves all sharpness algorithms that are supported by the specified controller.
 * This function allows you to discover which sharpness algorithms are available
 * for focus evaluation before attempting to configure one. The available algorithms
 * may vary based on the controller implementation and hardware capabilities.
 *
 * Uses the \ref principle_two_stage_query principle: call first with NULL
 * to get the required buffer size, then call again with an allocated buffer
 * to retrieve the actual algorithm list.
 *
 * To set a specific sharpness algorithm, see #peak_afl_AutoController_SharpnessAlgorithm_Set.
 *
 * \param[in]     controller  controller handle
 * \param[out]    typeList    Pointer to a user allocated list of #peak_afl_controller_sharpness_algorithm.
 *                            If this parameter is NULL, \p listSize will contain the needed count of \p typeList.
 * \param[in,out] listSize    Size of \p typeList: <br>
 *                            \li \p typeList equal NULL: <br>
 *                                out: minimal size of \p listSize in count of #peak_afl_controller_sharpness_algorithm to hold the list
 *                            \li \p typeList unequal NULL: <br>
 *                                in: size of the provided \p lastErrorMessage in counts of #peak_afl_controller_sharpness_algorithm <br>
 *                                out: number of #peak_afl_controller_sharpness_algorithm used by the function
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_BUFFER_TOO_SMALL  The supplied buffer is too small.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_SharpnessAlgorithm_GetList(
    peak_afl_controller_handle controller, peak_afl_controller_sharpness_algorithm* typeList, uint32_t* listSize);

/*!
 * \ingroup ids_peak_afl_c_callback
 * \brief Set a callback for a controller.
 *
 * Registers a callback function that will be invoked when specific events occur
 * during controller operation. This allows for real-time notification of
 * controller state changes or processing events.
 *
 * Set \p funcPtr to NULL to disable the callback.
 * Set \p funcPtr to !NULL to enable the callback.
 *
 * The callback set by \p funcPtr will be called with \p context as its last parameter.
 * The context parameter allows passing user-defined data to the callback function.
 *
 * For a list of valid types see #peak_afl_callback_type.
 *
 * \param[in] controller controller handle
 * \param[in] type       callback type
 * \param[in] funcPtr    function pointer
 * \param[in] context    pointer
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Callback_Set(
    peak_afl_controller_handle controller, peak_afl_callback_type type, void* funcPtr, void* context);

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief Check if weighted region of interest is supported for a controller.
 *
 * Determines whether the controller supports weighted regions of interest (ROI).
 * Weighted ROIs allow you to specify multiple rectangular areas within the image
 * with different importance weights for the automatic adjustment calculations.
 * This feature enables more sophisticated control over which parts of the image
 * are prioritized during automatic processing.
 *
 * If \p supported is #PEAK_AFL_TRUE weighted region of interest is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports weighted roi
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Weighted_ROI_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief Get the autofeature minimum size for the weighted region of interest for a controller.
 *
 * Retrieves the minimum dimensions required for weighted regions of interest.
 * ROIs smaller than this minimum size will be rejected. This constraint ensures
 * that the regions are large enough to provide meaningful statistical data for
 * the automatic adjustment algorithms.
 *
 * \param[in]  controller controller handle
 * \param[out] size       the minimum size
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Weighted_ROI_Min_Size(peak_afl_controller_handle controller, peak_afl_size* size);

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief Set the autofeature weighted region of interest for a controller.
 *
 * Configures one or more weighted regions of interest that the controller will
 * use for automatic adjustments. Each region can have a different weight value,
 * allowing you to prioritize certain areas of the image over others. For example,
 * you might give higher weight to the center of the image or to areas containing
 * important subjects.
 *
 * The weights are relative values - the controller will normalize them internally.
 * Areas outside the specified regions will have zero weight in the calculations.
 *
 * Already set weighted regions of interest will be overwritten by this call.
 *
 * \param[in] controller      controller handle
 * \param[in] weightedRoiList list of weighted region of interest
 * \param[in] listSize        count of weighted region of interest in \p weightedRoiList
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Weighted_ROI_Set(
    peak_afl_controller_handle controller, const peak_afl_weighted_rectangle* weightedRoiList, uint32_t listSize);

/*!
 * \ingroup ids_peak_afl_c_weighted_roi
 * \brief Get the autofeature weighted region of interest for a controller.
 *
 * Retrieves the currently configured weighted regions of interest. This returns
 * the same regions that were previously set using #peak_afl_AutoController_Weighted_ROI_Set.
 * Each region includes its rectangular coordinates and associated weight value.
 *
 * Uses the \ref principle_two_stage_query principle: call first with NULL
 * to get the required buffer size, then call again with an allocated buffer
 * to retrieve the actual ROI list.
 *
 * \param[in]     controller      controller handle
 * \param[out]    weightedRoiList Pointer to a user allocated list of #peak_afl_weighted_rectangle.
 *                                If this parameter is NULL, \p listSize will contain the needed count of \p typeList.
 * \param[in,out] listSize        Size of \p weightedRoiList:<br>
 *                                \li \p weightedRoiList equal NULL: <br>
 *                                    out: minimal size of \p listSize in count of
 *                                         #peak_afl_weighted_rectangle to hold the list <br>
 *                                \li \p typeList unequal NULL: <br>
 *                                    in: size of the provided \p lastErrorMessage in counts of
 *                                        #peak_afl_weighted_rectangle <br>
 *                                    out: number of #peak_afl_weighted_rectangle used by the function
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_BUFFER_TOO_SMALL  The supplied buffer is too small.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Weighted_ROI_Get(
    peak_afl_controller_handle controller, peak_afl_weighted_rectangle* weightedRoiList, uint32_t* listSize);

/*!
 * \ingroup ids_peak_afl_c_focus_limit
 * \brief Check if limit is supported for a controller.
 *
 * Determines whether the controller supports configurable limits for its operation.
 * Limits allow you to constrain the range of values that the controller can set
 * during automatic adjustments. This is useful for preventing the controller from
 * making adjustments that are too extreme or outside acceptable bounds.
 *
 * If \p supported is #PEAK_AFL_TRUE limit is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports limit
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Limit_IsSupported(peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_focus_limit
 * \brief Get the autofeature default limit.
 *
 * Retrieves the default limit values that the controller uses when no custom
 * limits have been set. These defaults typically represent the full range of
 * values that the controller can work with, providing unrestricted operation.
 *
 * \param[in]  controller controller handle
 * \param[out] limit      the default limit
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Limit_Default(
    peak_afl_controller_handle controller, peak_afl_controller_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_focus_limit
 * \brief Set the autofeature limit for a controller.
 *
 * Configures the operational limits for the controller, constraining the range
 * of values it can set during automatic adjustments. This prevents the controller
 * from making adjustments outside the specified bounds, which is useful for
 * maintaining image quality within acceptable parameters.
 *
 * Sets the minimum and maximum limit for the algorithm set by #peak_afl_AutoController_Algorithm_Set.
 *
 * \param[in] controller controller handle
 * \param[in] limit      the limit to set
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Limit_Set(peak_afl_controller_handle controller, peak_afl_controller_limit limit);

/*!
 * \ingroup ids_peak_afl_c_focus_limit
 * \brief Get the autofeature limit for a controller.
 *
 * Retrieves the currently configured operational limits for the controller.
 * This returns the same limits that were previously set using
 * #peak_afl_AutoController_Limit_Set, or the default limits if none were set.
 *
 * \param[in]  controller controller handle
 * \param[out] limit      the limit to get
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Limit_Get(peak_afl_controller_handle controller, peak_afl_controller_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_hysteresis
 * \brief Check if hysteresis is supported for a controller.
 *
 * Determines whether the controller supports hysteresis functionality. Hysteresis
 * helps prevent oscillation by introducing a delay or threshold before the
 * controller responds to changes. This creates more stable behavior by avoiding
 * rapid back-and-forth adjustments when the measured value fluctuates around
 * the target.
 *
 * If \p supported is #PEAK_AFL_TRUE hysteresis is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  boolean if controller supports hysteresis
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Hysteresis_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_hysteresis
 * \brief Get the autofeature hysteresis default.
 *
 * Retrieves the default hysteresis value that the controller uses when no custom
 * hysteresis has been configured. The default value is typically chosen to
 * provide good stability for most common use cases.
 *
 * \param[in]  controller controller handle
 * \param[out] hysteresis the default hysteresis
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Hysteresis_Default(peak_afl_controller_handle controller, uint8_t* hysteresis);

/*!
 * \ingroup ids_peak_afl_c_hysteresis
 * \brief Set the autofeature hysteresis for a controller.
 *
 * Configures the hysteresis value that helps prevent oscillation and provides
 * more stable controller behavior. Higher hysteresis values result in more
 * stable operation but slower response to changes. Lower values provide faster
 * response but may cause oscillation in noisy conditions.
 *
 * Set the hysteresis for the algorithm set by #peak_afl_AutoController_Algorithm_Set.
 *
 * \param[in] controller controller handle
 * \param[in] hysteresis the hysteresis to set
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Hysteresis_Set(peak_afl_controller_handle controller, uint8_t hysteresis);

/*!
 * \ingroup ids_peak_afl_c_hysteresis
 * \brief Get the autofeature hysteresis for a controller.
 *
 * Retrieves the currently configured hysteresis value for the controller.
 * This is the same value that was previously set using
 * #peak_afl_AutoController_Hysteresis_Set, or the default value if none was set.
 *
 * \param[in]  controller controller handle
 * \param[out] hysteresis the hysteresis
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Hysteresis_Get(peak_afl_controller_handle controller, uint8_t* hysteresis);

/*!
 * \ingroup ids_peak_afl_c_hysteresis
 * \brief Get autofeature hysteresis range for a controller.
 *
 * Retrieves the valid range of hysteresis values that can be configured for
 * this controller. The range provides the minimum and maximum allowable
 * hysteresis values, as well as the increment step size. Use this information
 * to determine valid hysteresis values before calling
 * #peak_afl_AutoController_Hysteresis_Set.
 *
 * \param[in]  controller controller handle
 * \param[out] min        minimum number of hysteresis
 * \param[out] max        maximum number of hysteresis
 * \param[out] inc        increment number of hysteresis.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.0
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_Hysteresis_GetRange(
    peak_afl_controller_handle controller, uint8_t* min, uint8_t* max, uint8_t* inc);

/*!
 * \ingroup ids_peak_afl_c_gain_limit
 * \brief Check if gain limit is supported for a controller.
 *
 * Determines whether the controller supports configurable gain limits. Gain limits
 * allow you to constrain the range of gain values that the controller can apply
 * during automatic brightness adjustments. This is useful for preventing excessive
 * noise (from high gain) or underexposure (from insufficient gain).
 *
 * The gain limit feature provides control over the automatic gain adjustments by
 * setting boundaries within which the controller can operate. This helps maintain
 * image quality by preventing the controller from applying gain values that would
 * result in unacceptable noise levels or insufficient signal amplification.
 *
 * If \p supported is #PEAK_AFL_TRUE gain limit is supported, otherwise it is unsupported.
 *
 * \param[in]  controller controller handle
 * \param[out] supported  true if auto gain limit is supported, otherwise returns false.
 *
 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \see peak_afl_AutoController_GainLimit_Set()
 * \see peak_afl_AutoController_GainLimit_Get()
 * \see peak_afl_AutoController_GainLimit_GetRange()
 * \see peak_afl_double_limit
 *
 * \since 1.3
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainLimit_IsSupported(
    peak_afl_controller_handle controller, peak_afl_BOOL8* supported);

/*!
 * \ingroup ids_peak_afl_c_gain_limit
 * \brief Set autofeature gain limit for a controller
 *
 * Configures the gain limits that constrain the automatic brightness adjustments.
 * This prevents the controller from applying gain values outside the specified
 * range, helping to maintain image quality by avoiding excessive noise or
 * underexposure.
 *
 * The gain limit applies to the overall gain control strategy used by the controller.
 * When multiple gain types are available, the controller will prioritize them according
 * to the following order for optimal signal-to-noise ratio: Analog -> Digital -> Any -> IPL (if supplied).
 * This ensures that analog gain (which typically provides better noise performance) is
 * used before digital gain when possible.
 *
 * The valid values are dependent on the used gain node and can be between minimum and maximum.
 * Default is the complete range.
 * The used priority list is: Analog -> Digital -> Any -> IPL (if supplied).
 *
 * If any value of the limit is out of range, the value is clamped to be valid. In this case, the function returns with
 #PEAK_AFL_STATUS_VALUE_ADJUSTED.
 * It is recommended to check the current values by calling #peak_afl_AutoController_GainLimit_Get after this call.
 *
 * \param[in]  controller controller handle
 * \param[in]  limit      Limits the controller to adjust the gain to the supplied range between min and max of \p limit.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range. The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \see peak_afl_AutoController_GainLimit_IsSupported()
 * \see peak_afl_AutoController_GainLimit_Get()
 * \see peak_afl_AutoController_GainLimit_GetRange()
 * \see peak_afl_double_limit
 *
 * \since 1.3
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainLimit_Set(peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_gain_limit
 * \brief Get autofeature gain limit for a controller
 *
 * Retrieves the currently configured gain limits for the controller. This returns
 * the same limits that were previously set using #peak_afl_AutoController_GainLimit_Set,
 * or the default limits if none were set.
 *
 * The returned limits reflect the current constraints applied to the overall gain
 * control strategy. These limits affect how the controller manages gain across
 * all available gain types (analog, digital, combined, host) according to the
 * priority order established by the implementation.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the current gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.3
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainLimit_Get(peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_limit
 * \brief Get autofeature gain limit range for a controller
 *
 * Retrieves the valid range of gain limit values that can be configured for
 * this controller. The range provides the minimum and maximum allowable gain
 * values, helping you determine appropriate limits before calling
 * #peak_afl_AutoController_GainLimit_Set.
 *
 * The range represents the overall gain capabilities of the system, taking into
 * account all available gain types and their combined effect. This information
 * is essential for setting realistic and effective gain limits that work within
 * the hardware and software capabilities of the imaging system.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range.
 *                                                The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \see peak_afl_AutoController_GainLimit_IsSupported()
 * \see peak_afl_AutoController_GainLimit_Set()
 * \see peak_afl_AutoController_GainLimit_Get()
 * \see peak_afl_double_limit
 *
 * \since 1.3
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_analog_limit
 * \brief Set autofeature analog gain limit for a controller
 *
 * Configures the analog gain limits specifically for the analog gain stage.
 * Analog gain is typically applied in the sensor or early in the signal chain
 * and generally provides better signal-to-noise ratio than digital gain.
 *
 * Analog gain limits are particularly important because they directly affect the
 * signal quality at the earliest stage of image acquisition. By constraining analog
 * gain appropriately, you can ensure optimal signal-to-noise ratio while preventing
 * saturation or insufficient signal amplification at the sensor level.
 *
 * The valid values are dependent on the analog gain node and can be between minimum and maximum.
 * Default is the complete range.
 *
 * If any value of the limit is out of range, the value is clamped to be valid. In this case, the function returns with
 #PEAK_AFL_STATUS_VALUE_ADJUSTED.
 * It is recommended to check the current values by calling #peak_afl_AutoController_GainAnalogLimit_Get after this call.
 *
 * \param[in]  controller controller handle
 * \param[in]  limit      Limits the controller to adjust the analog gain to the supplied range between min and max of \p limit.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range. The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainAnalogLimit_Set(
    peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_gain_analog_limit
 * \brief Get autofeature analog gain limit for a controller
 *
 * Retrieves the currently configured analog gain limits. This returns the
 * same limits that were previously set using #peak_afl_AutoController_GainAnalogLimit_Set,
 * or the default limits if none were set.
 *
 * The analog gain limits directly control the signal amplification at the sensor
 * level, which is critical for maintaining optimal image quality. These limits
 * help ensure that the analog gain stays within ranges that provide good
 * signal-to-noise ratio without causing sensor saturation.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the current analog gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainAnalogLimit_Get(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_analog_limit
 * \brief Get autofeature analog gain limit range for a controller
 *
 * Retrieves the valid range of analog gain limit values that can be configured.
 * Use this information to determine appropriate analog gain limits before calling
 * #peak_afl_AutoController_GainAnalogLimit_Set.
 *
 * The analog gain range is determined by the sensor and camera hardware capabilities.
 * Understanding this range is essential for setting effective limits that take
 * advantage of the sensor's optimal operating region while avoiding problematic
 * gain levels that could introduce excessive noise or saturation.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for analog gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainAnalogLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_digital_limit
 * \brief Set autofeature digital gain limit for a controller
 *
 * Configures the digital gain limits specifically for the digital gain stage.
 * Digital gain is applied after analog-to-digital conversion and can introduce
 * more noise than analog gain, but provides finer control and wider range.
 *
 * Digital gain limits are important for balancing image brightness requirements
 * with noise performance. While digital gain can provide extensive amplification
 * ranges, higher values amplify both signal and noise, potentially degrading
 * image quality. Setting appropriate limits helps maintain acceptable noise levels.
 *
 * The valid values are dependent on the used gain node and can be between minimum and maximum.
 * Default is the complete range.
 *
 * If any value of the limit is out of range, the value is clamped to be valid. In this case, the function returns with
 #PEAK_AFL_STATUS_VALUE_ADJUSTED.
 * It is recommended to check the current values by calling #peak_afl_AutoController_GainDigitalLimit_Get after this call.
 *
 * \param[in]  controller controller handle
 * \param[in]  limit      Limits the controller to adjust the digital gain to the supplied range between min and max of \p limit.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range. The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainDigitalLimit_Set(
    peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_gain_digital_limit
 * \brief Get autofeature digital gain limit for a controller
 *
 * Retrieves the currently configured digital gain limits. This returns the
 * same limits that were previously set using #peak_afl_AutoController_GainDigitalLimit_Set,
 * or the default limits if none were set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the current digital gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainDigitalLimit_Get(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_digital_limit
 * \brief Get autofeature digital gain limit range for a controller
 *
 * Retrieves the valid range of digital gain limit values that can be configured
 * for this controller. The range provides the minimum and maximum allowable
 * digital gain values, helping you determine appropriate limits before calling
 * #peak_afl_AutoController_GainDigitalLimit_Set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for digital gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainDigitalLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_combined_limit
 * \brief Set autofeature combined gain limit for a controller
 *
 * Configures limits for the total combined gain (analog + digital). This allows
 * you to constrain the overall amplification regardless of how it's distributed
 * between analog and digital stages. Useful for maintaining overall image
 * quality while allowing the controller to optimize the gain distribution.
 *
 * The valid values are dependent on the used gain node and can be between minimum and maximum.
 * Default is the complete range.
 *
 * If any value of the limit is out of range, the value is clamped to be valid. In this case, the function returns with
 #PEAK_AFL_STATUS_VALUE_ADJUSTED.
 * It is recommended to check the current values by calling #peak_afl_AutoController_GainCombinedLimit_Get after this call.
 *
 * \param[in]  controller controller handle
 * \param[in]  limit      Limits the controller to adjust the combined gain to the supplied range between min and max of \p limit.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range. The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainCombinedLimit_Set(
    peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_gain_combined_limit
 * \brief Get autofeature combined gain limit for a controller
 *
 * Retrieves the currently configured combined gain limits. This returns the
 * same limits that were previously set using #peak_afl_AutoController_GainCombinedLimit_Set,
 * or the default limits if none were set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the current combined gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainCombinedLimit_Get(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_combined_limit
 * \brief Get autofeature combined gain limit range for a controller
 *
 * Retrieves the valid range of combined gain limit values that can be configured
 * for this controller. Combined gain represents the total amplification from both
 * analog and digital stages. Use this information to determine appropriate
 * combined gain limits before calling #peak_afl_AutoController_GainCombinedLimit_Set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for combined gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainCombinedLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_host_limit
 * \brief Set autofeature host gain limit for a controller
 *
 * Configures the host gain limits for gain processing performed on the host
 * system (CPU/software-based gain). Host gain provides maximum flexibility
 * and precision but may have performance implications compared to hardware-based
 * gain stages.
 *
 * The valid values are dependent on the used gain node and can be between minimum and maximum.
 * Default is the complete range.
 *
 * If any value of the limit is out of range, the value is clamped to be valid. In this case, the function returns with
 #PEAK_AFL_STATUS_VALUE_ADJUSTED.
 * It is recommended to check the current values by calling #peak_afl_AutoController_GainHostLimit_Get after this call.
 *
 * \param[in]  controller controller handle
 * \param[in]  limit      Limits the controller to adjust the host gain to the supplied range between min and max of \p limit.

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_VALUE_ADJUSTED    At least one value of the limit is out of range. The limit was adjusted accordingly.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainHostLimit_Set(peak_afl_controller_handle controller, peak_afl_double_limit limit);

/*!
 * \ingroup ids_peak_afl_c_gain_host_limit
 * \brief Get autofeature host gain limit for a controller
 *
 * Retrieves the currently configured host gain limits. This returns the
 * same limits that were previously set using #peak_afl_AutoController_GainHostLimit_Set,
 * or the default limits if none were set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the current host gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainHostLimit_Get(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

/*!
 * \ingroup ids_peak_afl_c_gain_host_limit
 * \brief Get autofeature host gain limit range for a controller
 *
 * Retrieves the valid range of host gain limit values that can be configured
 * for this controller. Host gain is applied in software on the host system
 * and provides maximum flexibility. Use this information to determine
 * appropriate host gain limits before calling #peak_afl_AutoController_GainHostLimit_Set.
 *
 * \param[in]   controller controller handle
 * \param[out]  limit      the possible range for host gain limit

 * \return #PEAK_AFL_STATUS_SUCCESS           Operation was successful; no error occurred.
 * \return #PEAK_AFL_STATUS_NOT_INITIALIZED   The library is not initialized.
 * \return #PEAK_AFL_STATUS_INVALID_PARAMETER The argument is invalid.
 * \return #PEAK_AFL_STATUS_NOT_SUPPORTED     The function is not supported.
 * \return #PEAK_AFL_STATUS_ERROR             An unexpected internal error occurred.
 *
 * \since 1.6
 */
PEAK_AFL_API_STATUS peak_afl_AutoController_GainHostLimit_GetRange(
    peak_afl_controller_handle controller, peak_afl_double_limit* limit);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
