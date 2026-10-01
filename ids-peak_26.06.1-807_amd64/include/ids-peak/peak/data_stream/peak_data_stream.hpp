/*!
 * \file    peak_data_stream.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#include <peak/backend/peak_backend.h>
#include <peak/buffer/peak_buffer.hpp>
#include <peak/common/peak_common_structs.hpp>
#include <peak/common/peak_event_supporting_module.hpp>
#include <peak/dll_interface/peak_dll_interface_util.hpp>

#include <unordered_map>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <memory>
#include <mutex>
#include <string>
#include <vector>


namespace peak
{
namespace core
{

/*!
 * \brief Operation modes for DataStream::Flush() method.
 *
 * See GenTL ACQ_QUEUE_TYPE.
 */
enum class DataStreamFlushMode
{
    /*!
     * Flushes the buffers from the input pool to the
     * output buffer queue and if necessary adds
     * entries in the "New Buffer" event data queue.
     * The buffers currently being filled are not
     * affected by this operation.
     */
    InputPoolToOutputQueue,
    /*!
     * Discards all buffers in the output buffer queue
     * and if necessary remove the entries from the
     * event data queue.
     */
    DiscardOutputQueue,
    /*!
     * Puts all buffers in the input pool. This is
     * including those in the output buffer queue and
     * the ones which are currently being filled and
     * discard entries in the event data queue.
     */
    AllToInputPool,
    /*!
     * Puts all buffers that are neither in the input pool
     * nor being currently filled nor in the output
     * buffer queue in the input pool.
     */
    UnqueuedToInputPool,
    /*!
     * Discards all buffers in the input pool and the
     * buffers in the output queue including buffers
     * currently being filled so that no buffer is bound
     * to any internal mechanism and all buffers may
     * be revoked or requeued.
     */
    DiscardAll,

    /*!
     * Starting value for GenTL Producer custom IDs which are implementation specific.
     */
    Custom = 1000
};

/*!
 * \brief The enum holding the possible acquisition start modes, for DataStream::StartAcquisition().
 *
 * See GenTL ACQ_START_FLAGS.
 */
enum class AcquisitionStartMode
{
    /*!
     * Default behavior.
     */
    Default,

    /*!
     * Starting value for GenTL Producer custom IDs which are implementation specific.
     */
    Custom = 1000
};

/*!
 * \brief The enum holding the possible acquisition stop modes, for DataStream::StopAcquisition().
 *
 * See GenTL ACQ_STOP_FLAGS.
 */
enum class AcquisitionStopMode
{
    /*!
     * Stops the acquisition engine when the currently
     * running tasks like filling a buffer are completed
     * (default behavior).
     */
    Default,
    /*!
     * Stop the acquisition engine immediately. In
     * case this results in a partially filled buffer the
     * Producer will return the buffer through the
     * regular mechanism to the user, indicating
     * through the info function of that buffer that this
     * buffer is not complete.
     */
    Kill,

    /*!
     * Starting value for GenTL Producer custom IDs which are implementation specific.
     */
    Custom = 1000
};


class Device;

/*!
 * \ingroup ids_peak_acquisition
 * \brief Represents a GenTL DataStream module.
 *
 * This class allows to query information about a GenTL DataStream module and to manage and receive
 * \link Buffer Buffers\endlink from the physical device.
 *
 * The workflow for the buffers follows the GenTL model: First, memory needs to be allocated and announced to
 * the API, so they are in the GenTL "Announced Buffer Pool". Then, the buffers are queued, so they are available in
 * the GenTL "Input Buffer Pool". From this pool, buffers are chosen and filled by the device. Once a buffer is filled,
 * i.e. a new frame is available, it is added to the GenTL "Output Buffer Queue" and a "NewBufferEvent" is sent. At
 * this point, the newly filled buffer is available to the API.
 *
 * ### Buffer management
 *
 * There are two options for managing memory for the buffers:
 * * Allocate the memory for the buffer yourself and announce it to the API yourself, using AnnounceBuffer().
 *   Then you'll also need to free the memory for the buffer yourself, once you are done. To help with that,
 *   AnnounceBuffer() allows to add a callback, which is called when the buffer is revoked. At that point the memory
 *   won't be used anymore, and therefore can be deleted. If you don't add this callback, you'll have to manage the
 *   time of deletion yourself.
 * * Let the API allocate and free the memory for the buffer, using AllocAndAnnounceBuffer(). Then, the memory
 *   will be freed automatically when the buffer is revoked.
 *
 * After announcing the buffer, use QueueBuffer() to move it to the "Input Buffer Pool".
 *
 * Once a Buffer is not needed anymore, revoke it using RevokeBuffer().
 *
 * Use Flush() to move buffers between the Input Buffer Pool, the Output Buffer Queue and the Announced Buffer Pool.
 *
 * ### Receiving new buffers
 *
 * Once enough buffers are announced and queued, use StartAcquisition() to start generating new frames.
 *
 * \note Typically, the RemoteDevice also needs to be started using its NodeMap, e.g.:
 * \code
 * stream->StartAcquisition(peak::core::AcquisitionStartMode::Default);
 * remoteDevice->NodeMaps()[0]->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->Execute();
 * remoteDevice->NodeMaps()[0]->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->WaitUntilDone();
 * \endcode
 *
 * Once the acquisition is started, wait for the NewBufferEvent using WaitForFinishedBuffer(), which blocks until a
 * newly filled buffer is available.
 *
 * See GenTL Data Stream Module.
 */
class DataStream
    : public EventSupportingModule
    , public std::enable_shared_from_this<DataStream>
{
public:
    /*! The type of buffer revocation callbacks. */
    using BufferRevocationCallback = std::function<void(void* buffer, void* userPtr)>;
    /*! The constant defining an infinite number, used in StartAcquisition(). */
    static const uint64_t INFINITE_NUMBER = PEAK_INFINITE_NUMBER;

    DataStream() = delete;
    ~DataStream() override;
    DataStream(const DataStream& other) = delete;
    DataStream& operator=(const DataStream& other) = delete;
    DataStream(DataStream&& other) = delete;
    DataStream& operator=(DataStream&& other) = delete;

    /*! @copydoc ProducerLibrary::Key() */
    std::string Key() const;

    /*! @copydoc SystemDescriptor::Info() */
    RawInformation Info(int32_t infoCommand) const;

    /*! @copydoc System::ID() */
    std::string ID() const;

    /*! @copydoc SystemDescriptor::TLType() */
    std::string TLType() const;

    /*!
     * \brief Returns the minimum number of buffers that must be announced before starting the acquisition
     * with #StartAcquisition.
     *
     * This value is influenced by the "StreamBufferHandlingMode" node in the datastream nodemap.
     *
     * \return The minimum number of announced buffers required.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    size_t NumBuffersAnnouncedMinRequired() const;

    /*!
     * \brief Retrieves the count of buffers announced via #AnnounceBuffer or #AllocAndAnnounceBuffer.
     *
     * The state or pool of the buffers does not affect the count, as long as they have been announced.
     *
     * \return The number of buffers that have been announced.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    size_t NumBuffersAnnounced() const;

    /*!
     * \brief Retrieves the count of buffers that are currently queued,
     * i.e., the number of buffers present in the input pool.
     *
     * For additional details, refer to #QueueBuffer and #WaitForFinishedBuffer.
     *
     * \return The number of buffers currently queued.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    size_t NumBuffersQueued() const;

    /*!
     * \brief Retrieves the count of buffers that are currently waiting to be delivered,
     * i.e., the number of buffers present in the output pool.
     *
     * \return The number of buffers awaiting delivery.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    size_t NumBuffersAwaitDelivery() const;

    /*!
     * \brief Retrieves the count of buffers delivered since the last acquisition start.
     *
     * A buffer is considered delivered once it has been retrieved through #WaitForFinishedBuffer.
     *
     * This counter is reset to 0 when a new acquisition is initiated, as described in #StartAcquisition.
     *
     * \return The number of buffers delivered since the last acquisition start.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    uint64_t NumBuffersDelivered() const;

    /*!
     * \brief Returns the count of buffers that have been initiated.
     *
     * This counter increases with each new buffer that the acquisition engine begins to fill,
     * regardless of whether the buffer is ultimately discarded or delivered.
     *
     * The counter starts at 0 when the #DataStream is opened and is not reset until the #DataStream is closed.
     *
     * \return The total number of buffers that have been initiated.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    uint64_t NumBuffersStarted() const;

    /*!
     * \brief Retrieves the count of underruns.
     *
     * This counter increments when the acquisition engine has no buffers queued (see #QueueBuffer)
     * and a new frame is received from the remote device. As a result, the acquisition engine discards the
     * incoming data because there is no available buffer to store it.
     *
     * If you encounter this situation, verify that you are calling #QueueBuffer and ensure the time between receiving
     * the buffer through #WaitForFinishedBuffer and calling #QueueBuffer is less than the time required to capture
     * a frame (1 / frame rate).
     *
     * This counter is reset to zero at the time the #DataStream is opened
     * using #DataStreamDescriptor::OpenDataStream.
     *
     * \return The number of underruns.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    uint64_t NumUnderruns() const;

    /*!
     * \brief Returns the maximum number of chunks per buffer.
     *
     * \return Maximum number of chunks per buffer
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    size_t NumChunksPerBufferMax() const;

    /*!
     * \brief Returns the buffer alignment.
     *
     * \return Buffer alignment in bytes
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    size_t BufferAlignment() const;

    /*!
     * \brief Returns the payload size in bytes, i.e. the size of the buffers.
     *
     * \return Payload size in bytes
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    size_t PayloadSize() const;

    /*!
     * \brief Checks whether the data stream defines the payload size.
     *
     * \return True, if the DataStream defines the payload size.
     * \return False otherwise. In this case, ask the RemoteDevice for the payload size instead of the DataStream, e.g.:
     *         \code
     *         payload_size =
     * device->RemoteDevice()->NodeMaps()[0]->FindNode<peak::core::nodes::IntegerNode>("PayloadSize")->Value();
     *         \endcode
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    bool DefinesPayloadSize() const;

    /*!
     * \brief Checks whether the data stream is grabbing.
     *
     * \return True, while the acquisition is running.
     * \return False, if the acquisition isn't started yet or was stopped.
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    bool IsGrabbing() const;

    /*!
     * \anchor BufferManagement
     * \name Buffer Management
     */
    //!\{
    /*!
     * \brief Announces a given client allocated buffer to the data stream.
     *
     * The size of this buffer must be equal to the value of the "PayloadSize" node.
     *
     * To ensure that the payload size does not change while the acquisition is
     * running, it is strongly recommended to set the integer node
     * "TLParamsLocked" in the remote device nodemap to a value of 1.
     * Setting the "TLParamsLocked" node to 1 locks all writable nodes in the
     * XML tree that must not be modified during image acquisition.
     *
     * Announcing a #Buffer to the #DataStream will not queue it for use
     * in the acquisition engine. This is a separate step handled by
     * #QueueBuffer.
     *
     * \param[in] buffer             The raw buffer to announce.
     * \param[in] size               The size in bytes of the raw buffer to announce.
     * \param[in] userPtr            A pointer to user defined data, for identifying the buffer or attaching custom
     *                               data to the buffer. Optional (i.e. can be nullptr). See Buffer::UserPtr().
     * \param[in] revocationCallback Callback that is called when this buffer is revoked (via RevokeBuffer()). Use it
     *                               to handle cleanup of the raw buffer, e.g.:
     *                               \code
     *                               uint8_t* image_data = new uint8_t[payload_size];
     *                               (void)datastream->AnnounceBuffer(image_data, payload_size, nullptr,
     *                                   [](void* buffer, void* userPtr)
     *                                   {
     *                                       delete[] static_cast<uint8_t*>(buffer);
     *                                   });
     *                               \endcode
     *                               Optional (i.e. can be nullptr), if you handle the memory management differently.
     *
     * \return Proxy to the #Buffer that was added to the "Announced Buffer Pool"
     *
     * \since 1.0
     *
     * \throws InvalidArgumentException One of the submitted arguments is outside the valid range or is not supported.
     * \throws BadAccessException The acquisition has been started and the producer
     *                            does not support announcing buffers while the
     *                            acquisition is running.
     * \throws InternalErrorException An internal error has occurred.
     */
    std::shared_ptr<Buffer> AnnounceBuffer(
        void* buffer, size_t size, void* userPtr, const BufferRevocationCallback& revocationCallback);

    /*!
     * \brief Allocates and announces a producer allocated buffer on the data stream.
     *
     * The size of this buffer must be equal to the value of the "PayloadSize" node.
     *
     * To ensure that the payload size does not change while the acquisition is
     * running, it is strongly recommended to set the integer node
     * "TLParamsLocked" in the remote device nodemap to a value of 1.
     * Setting the "TLParamsLocked" node to 1 locks all writable nodes in the
     * XML tree that must not be modified during image acquisition.
     *
     * Announcing a #Buffer to the #DataStream will not queue it for use
     * in the acquisition engine. This is a separate step handled by
     * #QueueBuffer.
     *
     * \param[in] size The size of the buffer in bytes to allocate and announce.
     * \param[in] userPtr A pointer to user defined data, for identifying the buffer or attaching custom data to
     *                    the buffer. It is optional (i.e. can be nullptr). See Buffer::UserPtr().
     *
     * \return Proxy to the #Buffer that was added to the "Announced Buffer Pool"
     *
     * \since 1.0
     *
     * \throws BadAllocException Bad memory allocation
     * \throws BadAccessException The acquisition has been started and the producer
     *                            does not support announcing buffers while the
     *                            acquisition is running.
     * \throws InternalErrorException An internal error has occurred.
     */
    std::shared_ptr<Buffer> AllocAndAnnounceBuffer(size_t size, void* userPtr);

    /*!
     * \brief Queues a given buffer.
     *
     * Queueing a given buffer makes it available to be used by the acquisition
     * engine for receiving new data.
     *
     * \param[in] buffer The buffer to queue.
     *
     * \since 1.0
     *
     * \throws InvalidArgumentException One of the submitted arguments is outside the valid range or is not supported.
     * \throws InternalErrorException An internal error has occurred.
     */
    void QueueBuffer(const std::shared_ptr<Buffer>& buffer);

    /*!
     * \brief Revokes a specified buffer.
     *
     * This function revokes the given buffer. If the buffer was allocated by the client, the callback provided
     * during the buffer announcement (#AnnounceBuffer) will be triggered.
     *
     * \note A buffer can only be revoked if it is not queued, meaning it is neither in the input nor the output pool.
     *
     * You can use the #Flush function with #DataStreamFlushMode::DiscardAll as the flush mode to ensure that all
     * buffers are safe to be revoked.
     *
     * \param[in] buffer The buffer to revoke.
     *
     * \since 1.0
     *
     * \throws InvalidArgumentException If one of the provided arguments is outside the valid range or unsupported.
     * \throws InternalErrorException If an internal error occurs.
     */
    void RevokeBuffer(const std::shared_ptr<Buffer>& buffer);

    /*!
     * \brief Move buffers between the Input %Buffer Pool, the Output %Buffer Pool and the Announced %Buffer Pool,
     * depending on the mode parameter.
     *
     * \param[in] mode Operation modes being used to flush the buffers of the data stream.
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    void Flush(DataStreamFlushMode mode);

    /*!
     * \brief Retrieves the list of the currently announced buffers. The buffers' states are irrelevant, as long as
     * they have been announced.
     *
     * \return A list of currently announced buffers.
     *
     * \since 1.0
     *
     * \throws InternalErrorException If an internal error occurs.
     */
    std::vector<std::shared_ptr<Buffer>> AnnouncedBuffers() const;

    //!\}

    /*!
     * \anchor StartStop
     * \name Start/Stop Acquisition
     */
    //!\{
    /*!
     * \brief Starts the acquisition.
     *
     * Starts the acquisition engine on the host side. The acquisition on the
     * remote device needs to be started separately using the "AcquisitionStart"
     * command node.
     *
     * The acquisition engine depends on the payload size value not changing
     * between announcing the buffers to the data stream and while the
     * acquisition is running. For information on how to ensure this can't
     * happen, see \ref AnnounceBuffer.
     *
     * \param[in] mode The mode being used to start the acquisition.
     * \param[in] numToAcquire The number of buffers to acquire.
     *
     * \since 1.0
     *
     * \throws BadAccessException The acquisition is already running
     * \throws InternalErrorException An internal error has occurred.
     */
    void StartAcquisition(
        AcquisitionStartMode mode = AcquisitionStartMode::Default, uint64_t numToAcquire = INFINITE_NUMBER);

    /*!
     * \brief Stops the acquisition.
     *
     * \param[in] mode The mode being used to stop the acquisition.
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    void StopAcquisition(AcquisitionStopMode mode = AcquisitionStopMode::Default);

    //!\}

    /*!
     * \anchor NewBuffer
     * \name Wait for new buffer
     */
    //!\{
    /*!
     * \brief Blocking wait for a finished Buffer.
     *
     * Block and wait for the next buffer to be received or until the supplied
     * timeout is exceeded. In order to wait indefinitely use
     * [INFINITE_TIMEOUT](#peak::core::Timeout::INFINITE_TIMEOUT).
     *
     * A call to #WaitForFinishedBuffer can be aborted immediately and at any time by calling
     * #KillWait from another thread, resulting in an #AbortedException being thrown.
     * This is especially useful when using [INFINITE_TIMEOUT](#peak::core::Timeout::INFINITE_TIMEOUT).
     *
     * A buffer returned by #WaitForFinishedBuffer is guaranteed to remain untouched by the acquisition engine,
     * until it has been re-queued using #QueueBuffer. Depending on the time it takes the application to process the
     * image, it may be beneficial to copy the buffer data, re-queue the buffer and to process the copy.
     *
     * \attention If buffers are not re-queued using #QueueBuffer in time and no more buffers are available
     *            to the acquisition engine, no buffers will be received and image data will be discarded!
     *            For more information see #NumUnderruns.
     *
     *
     * \param[in] timeout_ms The time to wait for a finished buffer in milliseconds.
     *                       Use #DataStream::INFINITE_NUMBER to wait indefinitely.
     *
     * \return Newly filled Buffer.
     *
     * \since 1.0
     *
     * \throws AbortedException The wait was aborted by #KillWait or #FlushPendingKillWaits
     * \throws TimeoutException The function call timed out
     * \throws InternalErrorException An internal error has occurred.
     */
    std::shared_ptr<Buffer> WaitForFinishedBuffer(Timeout timeout_ms);

    /*!
     * \brief Tells the data stream to kill one call to #WaitForFinishedBuffer.
     *
     * Kills one call to #WaitForFinishedBuffer or queues the kill request
     * to be applied to the next call. Each kill results in one call to #WaitForFinishedBuffer to be aborted.
     * Calling #KillWait multiple times will queue multiple kills.
     * A pending #KillWait takes precedence over regular events. This means
     * that if both a new buffer event and a pending #KillWait exist, a call
     * to #WaitForFinishedBuffer will fail with an #AbortedException.
     *
     * \attention Pending kills stay queued even if the acquisition is stopped and restarted.
     *            They can only be cleared by closing the datastream or calling #FlushPendingKillWaits.
     *
     * To prevent queueing kills, call #KillWait only once and only when your acquisition is running.
     * Then, allow the acquisition thread to continue until #WaitForFinishedBuffer triggers an #AbortedException.
     * You can verify if the acquisition is running by using #IsGrabbing.
     *
     * \since 1.0
     *
     * \throws InternalErrorException An internal error has occurred.
     */
    void KillWait();

    /*!
     * \brief Flushes the KillWait queue.
     *
     * This function clears all queued KillWaits, preventing subsequent calls to #DataStream::WaitForFinishedBuffer
     * from throwing a #peak::core::AbortedException.
     *
     * Calls to #DataStream::WaitForFinishedBuffer that are currently waiting will be aborted and throw a
     * #peak::core::AbortedException.
     *
     * \note This function is only available when the acquisition is stopped.
     *
     * \attention Any pending new-buffer events will be discarded.
     *            Buffers still in the output queue will be moved to a
     *            non-queued state, where they will only count as announced and
     *            must be requeued. Otherwise, the buffer can not be used by the acquisition engine.
     *            To retrieve data from discarded buffers,
     *            use Buffer::IsQueued and Buffer::HasNewData to identify them.
     *            A buffer discarded by FlushPendingKillWaits is expected to contain new
     *            data and return `false` for Buffer::IsQueued.
     * \since 1.11
     *
     * \throws BadAccessException The acquisition is currently running and needs to be stopped first.
     * \throws InternalErrorException An internal error has occurred.
     */
    void FlushPendingKillWaits();

    //!\}

    /*! @copydoc DataStreamDescriptor::ParentDevice() */
    std::shared_ptr<Device> ParentDevice() const;

private:
    static void PEAK_CALL_CONV BufferRevocationCallbackCWrapper(void* buffer, void* userPtr, void* context);

    PEAK_MODULE_HANDLE ModuleHandle() const override;
    PEAK_EVENT_SUPPORTING_MODULE_HANDLE EventSupportingModuleHandle() const override;

    std::shared_ptr<Buffer> GetAnnouncedBuffer(PEAK_BUFFER_HANDLE bufferHandle) const;
    void AddAnnouncedBuffer(const std::shared_ptr<Buffer>& buffer);
    void RemoveAnnouncedBuffer(const std::shared_ptr<Buffer>& buffer);
    void RevokeAnnouncedBuffers();

    void Shutdown();

    friend ClassCreator<DataStream>;
    DataStream(PEAK_DATA_STREAM_HANDLE dataStreamHandle, const std::weak_ptr<Device>& parentDevice);
    PEAK_DATA_STREAM_HANDLE m_backendHandle;

    std::weak_ptr<Device> m_parentDevice;

    std::vector<std::shared_ptr<Buffer>> m_announcedBuffers;
    std::unordered_map<PEAK_BUFFER_HANDLE, std::shared_ptr<Buffer>> m_announcedBuffersByHandle;
    std::unordered_map<PEAK_BUFFER_HANDLE, std::unique_ptr<BufferRevocationCallback>>
        m_bufferRevocationCallbacksByBufferHandle;

    mutable std::mutex m_announcedBuffersMutex;
    mutable std::mutex m_bufferRevocationCallbacksByBufferHandleMutex;

    std::string m_key;
};

} /* namespace core */
} /* namespace peak */

/* Implementation */
namespace peak
{
namespace core
{

inline std::string ToString(DataStreamFlushMode entry)
{
    std::string entryString;

    if (entry == DataStreamFlushMode::InputPoolToOutputQueue)
    {
        entryString = "InputPoolToOutputQueue";
    }
    else if (entry == DataStreamFlushMode::DiscardOutputQueue)
    {
        entryString = "DiscardOutputQueue";
    }
    else if (entry == DataStreamFlushMode::AllToInputPool)
    {
        entryString = "AllToInputPool";
    }
    else if (entry == DataStreamFlushMode::UnqueuedToInputPool)
    {
        entryString = "UnqueuedToInputPool";
    }
    else if (entry == DataStreamFlushMode::DiscardAll)
    {
        entryString = "DiscardAll";
    }
    else if (entry >= DataStreamFlushMode::Custom)
    {
        entryString = "Custom";
    }

    return entryString;
}

inline std::string ToString(AcquisitionStartMode entry)
{
    std::string entryString;

    if (entry == AcquisitionStartMode::Default)
    {
        entryString = "Default";
    }
    else if (entry >= AcquisitionStartMode::Custom)
    {
        entryString = "Custom";
    }

    return entryString;
}

inline std::string ToString(AcquisitionStopMode entry)
{
    std::string entryString;

    if (entry == AcquisitionStopMode::Default)
    {
        entryString = "Default";
    }
    else if (entry == AcquisitionStopMode::Kill)
    {
        entryString = "Kill";
    }
    else if (entry >= AcquisitionStopMode::Custom)
    {
        entryString = "Custom";
    }

    return entryString;
}

inline DataStream::DataStream(PEAK_DATA_STREAM_HANDLE dataStreamHandle, const std::weak_ptr<Device>& parentDevice)
    : m_backendHandle(dataStreamHandle)
    , m_parentDevice(parentDevice)
    , m_announcedBuffers()
    , m_announcedBuffersByHandle()
    , m_announcedBuffersMutex()
    , m_key(QueryStringFromCInterfaceFunction([&](char* key, size_t* keySize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetKey(dataStreamHandle, key, keySize);
    }))
{}

inline DataStream::~DataStream()
{
    try
    {
        Shutdown();
    }
    catch (const Exception&)
    {}

    (void)PEAK_C_ABI_PREFIX PEAK_DataStream_Destruct(m_backendHandle);
}

inline std::string DataStream::Key() const
{
    return m_key;
}

inline RawInformation DataStream::Info(int32_t infoCommand) const
{
    return QueryRawInformationFromCInterfaceFunction([&](int32_t* dataType, uint8_t* buffer, size_t* bufferSize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetInfo(
            m_backendHandle, infoCommand, dataType, buffer, bufferSize);
    });
}

inline std::string DataStream::ID() const
{
    return QueryStringFromCInterfaceFunction([&](char* id, size_t* idSize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetID(m_backendHandle, id, idSize);
    });
}

inline std::string DataStream::TLType() const
{
    return QueryStringFromCInterfaceFunction([&](char* tlType, size_t* tlTypeSize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetTLType(m_backendHandle, tlType, tlTypeSize);
    });
}

inline size_t DataStream::NumBuffersAnnouncedMinRequired() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* numBuffersAnnouncedMinRequired) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersAnnouncedMinRequired(
            m_backendHandle, numBuffersAnnouncedMinRequired);
    });
}

inline size_t DataStream::NumBuffersAnnounced() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* numBuffersAnnounced) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersAnnounced(m_backendHandle, numBuffersAnnounced);
    });
}

inline size_t DataStream::NumBuffersQueued() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* numBuffersQueued) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersQueued(m_backendHandle, numBuffersQueued);
    });
}

inline size_t DataStream::NumBuffersAwaitDelivery() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* numBuffersAwaitDelivery) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersAwaitDelivery(
            m_backendHandle, numBuffersAwaitDelivery);
    });
}

inline uint64_t DataStream::NumBuffersDelivered() const
{
    return QueryNumericFromCInterfaceFunction<uint64_t>([&](uint64_t* numBuffersDelivered) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersDelivered(m_backendHandle, numBuffersDelivered);
    });
}

inline uint64_t DataStream::NumBuffersStarted() const
{
    return QueryNumericFromCInterfaceFunction<uint64_t>([&](uint64_t* numBuffersStarted) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumBuffersStarted(m_backendHandle, numBuffersStarted);
    });
}

inline uint64_t DataStream::NumUnderruns() const
{
    return QueryNumericFromCInterfaceFunction<uint64_t>([&](uint64_t* numUnderruns) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumUnderruns(m_backendHandle, numUnderruns);
    });
}

inline size_t DataStream::NumChunksPerBufferMax() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* numChunksPerBufferMax) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetNumChunksPerBufferMax(m_backendHandle, numChunksPerBufferMax);
    });
}

inline size_t DataStream::BufferAlignment() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* bufferAlignment) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetBufferAlignment(m_backendHandle, bufferAlignment);
    });
}

inline size_t DataStream::PayloadSize() const
{
    return QueryNumericFromCInterfaceFunction<size_t>([&](size_t* payloadSize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetPayloadSize(m_backendHandle, payloadSize);
    });
}

inline bool DataStream::DefinesPayloadSize() const
{
    return QueryNumericFromCInterfaceFunction<PEAK_BOOL8>([&](PEAK_BOOL8* definesPayloadSize) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetDefinesPayloadSize(m_backendHandle, definesPayloadSize);
    }) > 0;
}

inline bool DataStream::IsGrabbing() const
{
    return QueryNumericFromCInterfaceFunction<PEAK_BOOL8>([&](PEAK_BOOL8* isGrabbing) {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_GetIsGrabbing(m_backendHandle, isGrabbing);
    }) > 0;
}

inline std::shared_ptr<Buffer> DataStream::AnnounceBuffer(
    void* buffer, size_t size, void* userPtr, const DataStream::BufferRevocationCallback& revocationCallback)
{
    auto _callback = std::make_unique<BufferRevocationCallback>(revocationCallback);

    auto callbackContext = _callback.get();

    auto bufferHandle = QueryNumericFromCInterfaceFunction<PEAK_BUFFER_HANDLE>(
        [&](PEAK_BUFFER_HANDLE* _bufferHandle) {
            return PEAK_C_ABI_PREFIX PEAK_DataStream_AnnounceBuffer(m_backendHandle, buffer, size, userPtr,
                BufferRevocationCallbackCWrapper, callbackContext, _bufferHandle);
        });

    auto _buffer = std::make_shared<ClassCreator<Buffer>>(bufferHandle, shared_from_this());
    AddAnnouncedBuffer(_buffer);

    {
        std::lock_guard<std::mutex> lock(m_bufferRevocationCallbacksByBufferHandleMutex);

        m_bufferRevocationCallbacksByBufferHandle.emplace(bufferHandle, std::move(_callback));
    }

    return _buffer;
}

inline std::shared_ptr<Buffer> DataStream::AllocAndAnnounceBuffer(size_t size, void* userPtr)
{
    auto bufferHandle = QueryNumericFromCInterfaceFunction<PEAK_BUFFER_HANDLE>(
        [&](PEAK_BUFFER_HANDLE* _bufferHandle) {
            return PEAK_C_ABI_PREFIX PEAK_DataStream_AllocAndAnnounceBuffer(
                m_backendHandle, size, userPtr, _bufferHandle);
        });

    auto buffer = std::make_shared<ClassCreator<Buffer>>(bufferHandle, shared_from_this());
    AddAnnouncedBuffer(buffer);

    return buffer;
}

inline void DataStream::QueueBuffer(const std::shared_ptr<Buffer>& buffer)
{
    if (buffer == nullptr)
    {
        throw InvalidArgumentException("The given buffer is a nullptr!");
    }

    auto bufferHandle = buffer->m_backendHandle;

    CallAndCheckCInterfaceFunction(
        [&] { return PEAK_C_ABI_PREFIX PEAK_DataStream_QueueBuffer(m_backendHandle, bufferHandle); });
}

inline void DataStream::RevokeBuffer(const std::shared_ptr<Buffer>& buffer)
{
    if (buffer == nullptr)
    {
        throw InvalidArgumentException("The given buffer is a nullptr!");
    }

    auto bufferHandle = buffer->m_backendHandle;

    CallAndCheckCInterfaceFunction(
        [&] { return PEAK_C_ABI_PREFIX PEAK_DataStream_RevokeBuffer(m_backendHandle, bufferHandle); });

    RemoveAnnouncedBuffer(buffer);

    {
        std::lock_guard<std::mutex> lock(m_bufferRevocationCallbacksByBufferHandleMutex);

        m_bufferRevocationCallbacksByBufferHandle.erase(bufferHandle);
    }

    buffer->Revoke();
}

inline std::shared_ptr<Buffer> DataStream::WaitForFinishedBuffer(Timeout timeout_ms)
{
    auto bufferHandle = QueryNumericFromCInterfaceFunction<PEAK_BUFFER_HANDLE>(
        [&](PEAK_BUFFER_HANDLE* _bufferHandle) {
            return PEAK_C_ABI_PREFIX PEAK_DataStream_WaitForFinishedBuffer(
                m_backendHandle, timeout_ms, _bufferHandle);
        });

    return GetAnnouncedBuffer(bufferHandle);
}

inline void DataStream::KillWait()
{
    CallAndCheckCInterfaceFunction([&] { return PEAK_C_ABI_PREFIX PEAK_DataStream_KillWait(m_backendHandle); });
}

inline void DataStream::FlushPendingKillWaits()
{
    CallAndCheckCInterfaceFunction([&] { return PEAK_C_ABI_PREFIX PEAK_DataStream_FlushPendingKillWaits(m_backendHandle); });
}

inline void DataStream::Flush(DataStreamFlushMode mode)
{
    CallAndCheckCInterfaceFunction([&] {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_Flush(
            m_backendHandle, static_cast<PEAK_DATA_STREAM_FLUSH_MODE>(mode));
    });
}

inline std::vector<std::shared_ptr<Buffer>> DataStream::AnnouncedBuffers() const
{
    std::lock_guard<std::mutex> lock(m_announcedBuffersMutex);

    return m_announcedBuffers;
}

inline void DataStream::StartAcquisition(AcquisitionStartMode mode, uint64_t numToAcquire /*= INFINITE_NUMBER*/)
{
    CallAndCheckCInterfaceFunction([&] {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_StartAcquisition(
            m_backendHandle, static_cast<PEAK_ACQUISITION_START_MODE>(mode), numToAcquire);
    });
}

inline void DataStream::StopAcquisition(AcquisitionStopMode mode)
{
    CallAndCheckCInterfaceFunction([&] {
        return PEAK_C_ABI_PREFIX PEAK_DataStream_StopAcquisition(
            m_backendHandle, static_cast<PEAK_ACQUISITION_STOP_MODE>(mode));
    });
}

inline std::shared_ptr<Device> DataStream::ParentDevice() const
{
    return LockOrThrow(m_parentDevice);
}

inline void PEAK_CALL_CONV DataStream::BufferRevocationCallbackCWrapper(void* buffer, void* userPtr, void* context)
{
    auto callback = static_cast<DataStream::BufferRevocationCallback*>(context);
    if (*callback)
    {
        callback->operator()(buffer, userPtr);
    }
}

inline PEAK_MODULE_HANDLE DataStream::ModuleHandle() const
{
    auto moduleHandle = QueryNumericFromCInterfaceFunction<PEAK_MODULE_HANDLE>(
        [&](PEAK_MODULE_HANDLE* _moduleHandle) {
            return PEAK_C_ABI_PREFIX PEAK_DataStream_ToModule(m_backendHandle, _moduleHandle);
        });

    return moduleHandle;
}

inline PEAK_EVENT_SUPPORTING_MODULE_HANDLE DataStream::EventSupportingModuleHandle() const
{
    auto eventSupportingModuleHandle = QueryNumericFromCInterfaceFunction<PEAK_EVENT_SUPPORTING_MODULE_HANDLE>(
        [&](PEAK_EVENT_SUPPORTING_MODULE_HANDLE* _eventSupportingModuleHandle) {
            return PEAK_C_ABI_PREFIX PEAK_DataStream_ToEventSupportingModule(
                m_backendHandle, _eventSupportingModuleHandle);
        });

    return eventSupportingModuleHandle;
}

inline std::shared_ptr<Buffer> DataStream::GetAnnouncedBuffer(PEAK_BUFFER_HANDLE bufferHandle) const
{
    std::lock_guard<std::mutex> lock(m_announcedBuffersMutex);

    return m_announcedBuffersByHandle.at(bufferHandle);
}

inline void DataStream::AddAnnouncedBuffer(const std::shared_ptr<Buffer>& buffer)
{
    std::lock_guard<std::mutex> lock(m_announcedBuffersMutex);

    m_announcedBuffers.emplace_back(buffer);
    m_announcedBuffersByHandle.emplace(buffer->m_backendHandle, buffer);
}

inline void DataStream::RemoveAnnouncedBuffer(const std::shared_ptr<Buffer>& buffer)
{
    std::lock_guard<std::mutex> lock(m_announcedBuffersMutex);

    m_announcedBuffers.erase(std::remove(std::begin(m_announcedBuffers), std::end(m_announcedBuffers), buffer));
    m_announcedBuffersByHandle.erase(buffer->m_backendHandle);
}

inline void DataStream::RevokeAnnouncedBuffers()
{
    for (const auto& buffer : AnnouncedBuffers())
    {
        RevokeBuffer(buffer);
    }
}

inline void DataStream::Shutdown()
{
    if (IsGrabbing())
    {
        StopAcquisition(AcquisitionStopMode::Default);
    }
    Flush(DataStreamFlushMode::DiscardAll);
    RevokeAnnouncedBuffers();
}

} /* namespace core */
} /* namespace peak */
