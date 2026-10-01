/*!
 * \file    backend.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   1.0.0
 *
 * \version 1.3
 *
 * Copyright (C) 2019 - 2026, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without notice
 * and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility for any errors
 * that may appear in this document.
 *
 * This document, or source code, is provided solely as an example of how to utilize
 * IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */

#include "backend.h"
#include "imageitem.h"

#include <peak_icv/peak_icv.hpp>

#define VERSION "1.3"


BackEnd::BackEnd(QObject* parent)
    : QObject(parent)
{
    // The library must be initialized before use.
    // Each `Initialize` call must be matched with a corresponding call
    // to `Close`.
    peak::Library::Initialize();
    peak::icv::library::Init();

    // Create worker thread that waits for new images from the camera
    m_acquisitionWorker = new AcquisitionWorker();
    m_acquisitionWorker->moveToThread(&m_acquisitionThread);

    // Worker must be started, when the acquisition starts, and deleted, when the worker thread finishes
    connect(&m_acquisitionThread, &QThread::started, m_acquisitionWorker, &AcquisitionWorker::Start);
    connect(&m_acquisitionThread, &QThread::finished, m_acquisitionWorker, &QObject::deleteLater);

    // Connect the worker new image signal with the corresponding backend signal
    connect(m_acquisitionWorker, &AcquisitionWorker::imageReceived, this, &BackEnd::imageReceived);

    // Connect the worker counter updated signal with with the corresponding backend signal
    connect(m_acquisitionWorker, &AcquisitionWorker::counterChanged, this, &BackEnd::counterChanged);

    // Connect the signal from the acquisition worker when an exception was thrown and a message should be printed
    // with the messagebox trigger slot in the BackEnd class
    connect(m_acquisitionWorker, &AcquisitionWorker::messageBoxTrigger, this, &BackEnd::messageBoxTrigger);
}

BackEnd::~BackEnd()
{
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();
    }

    CloseDevice();

    // Each `Initialize` call must be matched with a corresponding call to `Close`.
    peak::Library::Close();
    peak::icv::library::Exit();
}

bool BackEnd::OpenDevice()
{
    try
    {
        // Get the instance of the device manager singleton.
        auto& deviceManager = peak::DeviceManager::Instance();

        // Update the device manager.
        // When `Update` is called, it searches for all producer libraries
        // contained in the directories found in the official GenICam GenTL
        // environment variable GENICAM_GENTL{32/64}_PATH. It then opens all
        // found ProducerLibraries, their Systems, their Interfaces, and lists
        // all available DeviceDescriptors.
        deviceManager.Update();

        // Return if no device was found.
        if (deviceManager.Devices().empty())
        {
            qDebug() << "[BackEnd::OpenDevice] ERROR: No device found";
            emit messageBoxTrigger("Error", "No device found.", true);
            return false;
        }

        // Open the first openable device in the device manager's device list.
        size_t deviceCount = deviceManager.Devices().size();
        for (size_t i = 0; i < deviceCount; ++i)
        {
            if (deviceManager.Devices().at(i)->IsOpenable())
            {
                m_device = deviceManager.Devices().at(i)->OpenDevice(peak::core::DeviceAccessType::Control);

                // Stop after the first opened device
                break;
            }
            else if (i == (deviceCount - 1))
            {
                qDebug() << "[BackEnd::OpenDevice] ERROR: Device(s) could not be opened";
                emit messageBoxTrigger("Error", "Device could not be openend", true);
                return false;
            }
        }

        if (m_device)
        {
            try
            {
                // Open standard data stream
                m_dataStream = m_device->DataStreams().at(0)->OpenDataStream();
            }
            catch (const std::exception& e)
            {
                // Open data stream failed
                m_device.reset();
                qDebug() << "Error: Failed to open DataStream";
                emit messageBoxTrigger("Error", QString("Failed to open DataStream\n") + e.what(), true);
                return false;
            }

            // Retrieve the remote device's primary node map, which in GenICam represents
            // a hierarchical set of device parameters (features) such as exposure, gain,
            // and firmware info. The remote nodemap provides access to controls implemented
            // on the device itself, primarily following the
            // GenICam Standard Feature Naming Convention (SFNC),
            // while also supporting custom nodes to accommodate device-specific features.
            m_nodemapRemoteDevice = m_device->RemoteDevice()->NodeMaps().at(0);

            // To prepare for untriggered continuous image acquisition, load the default user set if available
            // and wait until execution is finished
            try
            {
                m_nodemapRemoteDevice->FindNode<peak::core::nodes::EnumerationNode>("UserSetSelector")
                    ->SetCurrentEntry("Default");
                m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("UserSetLoad")->Execute();
                m_nodemapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("UserSetLoad")->WaitUntilDone();
            }
            catch (const peak::core::NotFoundException&)
            {
                // UserSet is not available
            }

            // Get the payload size for correct buffer allocation
            auto payloadSize = m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("PayloadSize")
                                   ->Value();

            // Get the minimum number of buffers that must be announced
            auto bufferCountMax = m_dataStream->NumBuffersAnnouncedMinRequired();

            // Allocate and announce image buffers and queue them
            for (size_t bufferCount = 0; bufferCount < bufferCountMax; ++bufferCount)
            {
                auto buffer = m_dataStream->AllocAndAnnounceBuffer(static_cast<size_t>(payloadSize), nullptr);
                m_dataStream->QueueBuffer(buffer);
            }

            // Configure worker
            m_acquisitionWorker->SetDataStream(m_dataStream);
            emit acquisitionStarted();
        }
    }
    catch (const std::exception& e)
    {
        qDebug() << "[BackEnd::StartAcquisition] EXCEPTION: " << e.what();
        emit messageBoxTrigger("Exception", e.what(), true);
        return false;
    }

    // Start thread execution
    m_acquisitionThread.start();

    return true;
}

void BackEnd::CloseDevice()
{
    m_acquisitionWorker->Stop();

    // if device was opened, try to stop acquisition
    if (m_device)
    {
        try
        {
            auto remoteNodeMap = m_device->RemoteDevice()->NodeMaps().at(0);
            remoteNodeMap->FindNode<peak::core::nodes::CommandNode>("AcquisitionStop")->Execute();
        }
        catch (const std::exception& e)
        {
            qDebug() << "[BackEnd::stopAcquisition] EXCEPTION: " << e.what();
            emit messageBoxTrigger("Exception", e.what(), false);
        }
    }

    // if data stream was opened, try to stop it and revoke its image buffers
    if (m_dataStream)
    {
        try
        {
            // Stop and flush the `DataStream`.
            // `KillWait` will cancel pending `WaitForFinishedBuffer` calls.
            // NOTE: One call to `KillWait` will cancel one pending `WaitForFinishedBuffer`.
            //       For more information, refer to the documentation of `KillWait`.
            m_dataStream->KillWait();
            m_dataStream->StopAcquisition(peak::core::AcquisitionStopMode::Default);
            // Discard all buffers from the acquisition engine.
            // They remain in the announced buffer pool.
            m_dataStream->Flush(peak::core::DataStreamFlushMode::DiscardAll);

            for (const auto& buffer : m_dataStream->AnnouncedBuffers())
            {
                m_dataStream->RevokeBuffer(buffer);
            }
        }
        catch (const std::exception& e)
        {
            qDebug() << "[BackEnd::StopAcquisition] EXCEPTION: " << e.what();
            emit messageBoxTrigger("Exception", e.what(), false);
        }
    }

    if (m_nodemapRemoteDevice)
    {
        try
        {
            // Unlock parameters after acquisition stop
            m_nodemapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("TLParamsLocked")->SetValue(0);
        }
        catch (const std::exception& e)
        {
            qDebug() << "[BackEnd::StopAcquisition] EXCEPTION: " << e.what();
            emit messageBoxTrigger("Exception", e.what(), false);
        }
    }
}

QString BackEnd::Version()
{
    return VERSION;
}

QString BackEnd::QtVersion()
{
    return qVersion();
}
