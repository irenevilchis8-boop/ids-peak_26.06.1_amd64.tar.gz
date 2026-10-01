/*!
 * \file    ids_gentl_custom_extensions.h
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   IDS GenTL Producer Interface Extension
 */

#ifndef IDS_GENTLEX_H
#define IDS_GENTLEX_H

#ifndef GC_USER_DEFINED_TYPES
 /* The types should be the same as defined in GCTypes.h from GenApi. But in
  * case you do not have this header the necessary types are defined here. */
#  if defined(_WIN32)
#    if defined(_MSC_VER) && _MSC_VER >= 1600 /* VS2010 provides stdint.h */
#      include <stdint.h>
#    elif !defined _STDINT_H && !defined _STDINT
  /* stdint.h is usually not available under Windows */
typedef unsigned char uint8_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#    endif
#  else
#    include <stdint.h>
#  endif

#  ifdef __cplusplus
typedef bool bool8_t;
#  else
typedef uint8_t bool8_t;
#  endif
#endif /* GC_DEFINE_TYPES */


#ifdef __cplusplus
extern "C"
{
/*! \brief IDS GenTL namespace */
namespace IDS_GenTL
{
#endif

/*! \brief Custom %Error code enumeration.
 *
 * This enumeration extends the standard enumeration of error codes.
 */
enum GC_ERROR_LIST_EX
{
    /*! \brief Internal error. */
    GC_ERR_INTERNAL = -10000 - 0
};

/*! \brief Data type for statistics data. */
typedef struct S_STATISTICS
{
    /*! \brief The number of values that were considered for the statistics. */
    uint64_t value_count;

    /*! \brief The mean value. */
    uint64_t mean_value;

    /*! \brief The minimum value. */
    uint64_t min_value;

    /*! \brief The maximum value. */
    uint64_t max_value;

} STATISTICS;
typedef STATISTICS Statistics;

/*! \brief Custom %Buffer Info command enumeration.
 *
 * This enumeration extends the standard enumeration of commands to retrieve
 * information with the GenICam::TL::Client::DSGetBufferInfo function on a data stream / buffer handle pair.
 */
enum  BUFFER_INFO_CMD_LIST_EX
{
    /*! \brief Gets the status value that the device reported in the leader packet.
     *
     *  Range of values: UINT16.
     *
     * \note DSGetBufferInfo() will return GC_ERR_NOT_AVAILABLE if
     *       there was no leader received for the frame of interest.
     */
    BUFFER_INFO_LEADER_STATUS  = 1000 + 0,

    /*! \brief Gets the status value that the device reported in the trailer packet.
     *
     *  Range of values: UINT16.
     * 
     * \note DSGetBufferInfo() will return GC_ERR_NOT_AVAILABLE if
     *       there was no trailer received for the frame of interest.
     */
    BUFFER_INFO_TRAILER_STATUS = 1000 + 1,

    /*!
     * \brief Retrieves the synchronized system timestamp for a buffer.
     *
     * Retrieves a system timestamp, expressed as nanoseconds since the Unix epoch
     * (00:00:00 UTC on January 1, 1970), that corresponds to the device timestamp
     * of the specified buffer.
     *
     * The returned value is calculated using the most recent synchronization
     * between system and device timestamps by mapping the buffer’s device timestamp
     * to system time based on the synchronized timestamp pair.
     *
     * This command allows buffers to be associated with a system time even when the
     * device timestamp and system clock are running independently.
     * The effective accuracy of the system timestamp is subject to various
     * platform- and environment-specific influences, such as system and device
     * clock resolution, operating system scheduling behavior, system load, and
     * network characteristics (e.g. size and traffic load). As such, a deterministic
     * timestamp precision cannot be specified.
     *
     * Internal measurements under representative conditions indicate that the
     * timestamp deviation is most commonly on the order of 1–2 ms and typically
     * remains below 10 ms, even under high network load.
     *
     * \note For high-precision or time-synchronization use cases, it is recommended
     * to use the device timestamp instead of the system timestamp. In particular,
     * devices supporting IEEE 1588 Precision Time Protocol (PTP) can provide
     * significantly higher timestamp accuracy and synchronization across multiple
     * systems.
     *
     * \note Support for this command may depend on the transport layer. If the
     * transport layer does not support this feature, the command may return
     * GC_ERR_NOT_AVAILABLE.
     */
    BUFFER_INFO_SYSTEM_TIMESTAMP_NS = 1000 + 2,
};

/*! \brief Custom %Stream Info command enumeration.
 *
 * This enumeration extends the standard enumeration of commands to retrieve
 * information with the GenICam::TL::Client::DSGetStreamInfo function on a data stream handle.
 */
enum STREAM_INFO_CMD_LIST_EX
{
    /*! \brief Gets the buffer fill level statistics.
     *
     *  The fill level is the percentage of received bytes in respect to expected bytes for the buffer.
     *  The fill level statistics is reset with acquisition start.
     *
     *  Range of values: IDS_GenTL::Statistics with values out of range 0..100.
     *
     * \note Supported for interface Socket GEV only.
     */
    STREAM_INFO_BUFFER_FILL_LEVEL_STATISTICS    = 7000 + 0,

    /*! \brief Gets the buffer packet resend statistics.
     *
     *  The packet resend value is the ratio of requested packet resends to the total packets for the buffer.
     *  The value is given in permille.
     *
     *  Range of values: IDS_GenTL::Statistics with values out of range 0..1000.
     *
     * \note Supported for interface Socket GEV only.
     */
    STREAM_INFO_BUFFER_PACKET_RESEND_STATISTICS = 7000 + 1
};

/*! \brief List of possible password protection states for the device. */
enum PASSWORD_PROTECTION_STATUS_LIST_EX
{
    /*! Password protection is not supported or not enabled on the device. */
    PASSWORD_PROTECTION_STATUS_NOT_AVAILABLE,
    /*! Password protection is active and the device is unsecured. */
    PASSWORD_PROTECTION_STATUS_UNLOCKED,
    /*! Password protection is active and the device is secured. */
    PASSWORD_PROTECTION_STATUS_LOCKED,
};
typedef uint32_t PASSWORD_PROTECTION_STATUS;

/*! \brief Custom %Device Info command enumeration.
*
* This enumeration extends the standard enumeration of commands to retrieve
* information with the GenICam::TL::Client::DevGetInfo function on a device handle.
*/
enum DEVICE_INFO_CMD_LIST_EX
{
    /*! \brief Gets the device connection ID.
     *
     *  Range of values: UINT64.
     *
     *  The connection ID changes whenever the device connection is changes, e.g. when a
     *  new device connection is established.
     *
     *  This allows the caller to detect whether the underlying device connection
     *  has changed since the last interaction by comparing connection IDs.
     */
    DEVICE_INFO_CONNECTION_ID = 1000 + 0,

    /*! \brief Get the status of the Password protection status
     *
     * Range of values: UINT32.
     *
     * Query the password protection status of the device.
     */
    DEVICE_INFO_PASSWORD_PROTECTION_STATUS = 1000 + 1
};

/*! \brief Custom %Event Type enumeration.
 *
 * This enumeration extends the standard enumeration of event types
 * that can be registered on certain modules with the GenICam::TL::Client::GCRegisterEvent function.
 */
enum EVENT_TYPE_LIST_EX
{
    /*! \brief Notification if the connection status of a device changed.
     *
     *  This notification indicates that a remote device was detached or (re-)attached.
     *
     *  This event can be registered on the %System module.
     *  The event related data is of type EVENT_DEVICE_CONNECTION_CHANGE_DATA.
     */
    EVENT_DEVICE_CONNECTION_CHANGE = 1000 + 0
};

/*! \brief Enum of device connection states */
enum DEVICE_CONNECTION_STATE_LIST
{
    /*! \brief Device is disconnected */
    DEVICE_CONNECTION_STATE_DISCONNECTED = 0,

    /*! \brief Device is connected */
    DEVICE_CONNECTION_STATE_CONNECTED = 1
};
typedef uint16_t DEVICE_CONNECTION_STATE;

enum DEVICE_RECONNECT_ERROR_LIST
{
    /*! No error occurred */
    DEVICE_RECONNECT_OPERATION_NO_ERROR = 0x0,
    /*! Indicates that the TL could not restart the remote device acquisition. */
    DEVICE_RECONNECT_OPERATION_REMOTE_DEVICE_ACQUISITION_RESTART_ERROR = 0x1000000,
    /*! The configured payload size is larger than the buffers announced in the data stream. Either the buffers must be
       reallocated to a larger size or the remote device configuration must be adjusted so the reported payload size is
       smaller or equal to the allocated buffers */
    DEVICE_RECONNECT_OPERATION_REMOTE_DEVICE_ACQUISITION_RESTART_PAYLOAD_SIZE_LARGER_THAN_BUFFERS = 0x1000001,
    /*! Indicates that the TL could not restore the remote devices configuration. */
    DEVICE_RECONNECT_OPERATION_REMOTE_DEVICE_CONFIGURATION_RESTORE_ERROR = 0x2000000,
};
typedef uint32_t DEVICE_RECONNECT_ERROR_FLAGS;

/*! \brief Structure of the data returned from a signaled "Remote Device Connection Status Change" event. */
#pragma pack (push, 1)
typedef struct S_EVENT_DEVICE_CONNECTION_CHANGE_DATA
{
    /*! \brief The Handle of the parent %Interface module of the device. */
    GenTL::IF_HANDLE InterfaceHandle;

    /*! \brief The Handle of the Local %Device that this event refers to.
     *
     * This handle is only provided, if an opened device has been disonnected or
     * if a device has been reconnected.
     * Otherwise this value is GENTL_INVALID_HANDLE.
     */
    GenTL::DEV_HANDLE DeviceHandle;

    /*! \brief The zero-terminated %Module ID of the Local %Device that this event refers to. */
    char DeviceID[192];

    /*! \brief The zero-terminated serial number of the device this event refers to. */
    char SerialNumber[64];

    /*! \brief The new connection state of the device.
     *
     * See #DEVICE_CONNECTION_STATE_LIST.
     */
    DEVICE_CONNECTION_STATE NewConnectionState;

    /*! \brief Bool whether the reconnect is active for the device. 
     *  
     * If this is true, and the connection state indicates the device to be disconnected,
     * this means, that the TL will keep the device handle open and wait for the device to be
     * reconnected.
     * 
     * Also if this is true, and the connection state indicates the device to be connected,
     * this means that the TL has tried to reconnect the device to it's original handle.
     * If the reconnect was successful can be checked via #ReconnectStatus.
     */
    bool8_t IsReconnectActive;

    /*! \brief Bool whether the acquisition in the remote device is running.
     *  
     * If this is true the acquisition in the remote device is running.
     * Otherwise it is up to the consumer application to restart the acquisition in the remote device.
     */
    bool8_t IsRemoteDeviceAcquisitionRunning;

    /*! \brief Bool whether the remote device configuration has been recovered after the reconnect.
     *
     * If this is true the remote device has been reconfigured to the state at the time of device detachment.
     * Otherwise it is up to the consumer application to take care for reconfiguring the remote device parameters.
     */
    bool8_t IsRemoteDeviceConfigurationRestored;

    bool8_t Reserved[6];

    /*! \brief Flags indicating the failed reconnect operation and the corresponding error.
     *
     * If an error occurs during a reconnect this flag field indicates the failed reconnect operation as well as a more
     * detailed error flag. Based on the error the users application can complete the missing reconnect operations,
     * e.g. reallocating the buffers if the
     * `DEVICE_RECONNECT_OPERATION_DATA_STREAM_RESTART_PAYLOAD_SIZE_LARGER_THAN_BUFFERS` flag is set.
     *
     * \see For detailed information about a specific error see DEVICE_RECONNECT_ERROR_LIST
     */
    DEVICE_RECONNECT_ERROR_FLAGS ReconnectErrorFlags;

    uint8_t Reserved2[64];

} EVENT_DEVICE_CONNECTION_CHANGE_DATA;
#pragma pack (pop)

#ifdef __cplusplus
} /* end of namespace IDS_GenTL */
} /* end of extern "C" */
#endif


#endif /* IDS_GENTLEX_H */
