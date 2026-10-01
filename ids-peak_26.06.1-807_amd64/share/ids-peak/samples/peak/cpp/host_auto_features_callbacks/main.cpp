/*!
 * \brief   This application demonstrates how to setup host auto features
 *          including progress updates via the IDS peak AFL.
 *
 * Copyright (C) 2025 - 2026, IDS Imaging Development Systems GmbH.
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

#define VERSION "1.0.0"

#include <iostream>

#include <peak_afl/peak_afl.hpp>
#include <peak/converters/peak_buffer_converter_ipl.hpp>
#include <peak/peak.hpp>

namespace
{
constexpr auto gainComponent = PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_ANALOG_GAIN;

void HandleProcessData(peak_afl_process_data* data)
{
    if (data == nullptr)
    {
        std::cout << "No data for callback!\n";
        return;
    }

    std::cout << "ProcessingCallback: "
              << "Controller Status " << data->controller_status << " Controller Type " << data->controller_type
              << "\n";

    switch (data->controller_type)
    {
    case PEAK_AFL_CONTROLLER_TYPE_INVALID:
        break;
    case PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS: {
        auto* tmp = reinterpret_cast<peak_afl_process_data_brightness*>(data);
        std::cout << "Brightness:\n"
                  << "\tMean: " << tmp->mean << "\n\tController Component: " << tmp->controller_component << "\n";
        break;
    }
    case PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE: {
        auto* tmp = reinterpret_cast<peak_afl_process_data_whitebalance*>(data);
        std::cout << "Whitebalance:\n"
                  << "\tMean (R/G/B): " << tmp->mean_r << "/" << tmp->mean_g << "/" << tmp->mean_b << "\n"
                  << "\tController Component: " << tmp->controller_component << "\n";
        break;
    }
    case PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS: {
        auto* tmp = reinterpret_cast<peak_afl_process_data_focus*>(data);
        std::cout << "Focus:\n"
                  << "\tFocus: " << tmp->focus_value << " Sharpness " << tmp->sharpness_value << "\n";
        break;
    }
    }
}
} // namespace

int main()
{
    std::cout << "IDS peak genericAPI \"host_auto_features_callbacks\" Sample v" << VERSION << std::endl;

    // The library must be initialized before use.
    // Each call to `Initialize` must be matched with a corresponding call to `Close`.
    peak::Library::Initialize();
    peak::afl::library::Init();

    // Get the device manager singleton object.
    auto& deviceManager = peak::DeviceManager::Instance();

    try
    {
        // Update the device manager.
        // When `Update` is called, it searches for all ProducerLibraries contained
        // in the directories specified by the GENICAM_GENTL{32/64}_PATH environment variable.
        // It then opens all found producers, their systems, interfaces, and lists
        // all available DeviceDescriptors.
        deviceManager.Update();

        // Exit program if no device was found.
        if (deviceManager.Devices().empty())
        {
            std::cout << "No device found. Exiting program.\n";
            // One call to `Close` is required for each call to `Initialize`.
            peak::Library::Close();
            return 0;
        }

        // Open the first device, which can be opened with control access.
        // The access types correspond to the GenTL `DEVICE_ACCESS_FLAGS`.
        const auto& devices = deviceManager.Devices();
        const auto deviceIt = std::find_if(devices.cbegin(), devices.cend(), [](auto& device) {
            return device->IsOpenable(peak::core::DeviceAccessType::Control);
        });

        if (deviceIt == devices.cend())
        {
            std::cout << "No (openable) device found. Exiting program!\n";
            peak::Library::Close();
            return -1;
        }

        const auto device = (*deviceIt)->OpenDevice(peak::core::DeviceAccessType::Control);
        std::cout << "Using device " << device->DisplayName() << "\n";

        // Retrieve the remote device's primary node map.
        // In GenICam, a node map represents a hierarchical set of parameters (features)
        // such as exposure, gain, or firmware info. This node map provides access to controls
        // implemented on the device itself, typically following the GenICam SFNC, while still
        // allowing for vendor-specific extensions.
        auto nodeMapRemoteDevice = device->RemoteDevice()->NodeMaps().at(0);

        // Autofeature manager, which can have multiple controllers
        auto manager = peak::afl::Manager(nodeMapRemoteDevice);

        // Some devices might not support all controller types
        const auto brightnessSupported = manager.IsControllerSupported(PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS);
        const auto focusSupported = manager.IsControllerSupported(PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS);
        const auto whitebalanceSupported = manager.IsControllerSupported(PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE);

        std::shared_ptr<peak::afl::Controller> controllerBrightness{};
        std::shared_ptr<peak::afl::Controller> controllerFocus{};
        std::shared_ptr<peak::afl::Controller> controllerWhitebalance{};

        // Create controller types
        if (brightnessSupported)
        {
            controllerBrightness = manager.CreateController(PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS);
            std::cout << "Controller Status: " << controllerBrightness->Status() << "\n";
            std::cout << "Controller Type: " << controllerBrightness->Type() << "\n";
        }

        if (focusSupported)
        {
            controllerFocus = manager.CreateController(PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS);
        }

        if (whitebalanceSupported)
        {
            controllerWhitebalance = manager.CreateController(PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE);
        }

        // Load default camera settings
        nodeMapRemoteDevice->FindNode<peak::core::nodes::EnumerationNode>("UserSetSelector")
            ->SetCurrentEntry("Default");
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("UserSetLoad")->Execute();
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("UserSetLoad")->WaitUntilDone();

        // Register callbacks
        if (controllerBrightness != nullptr)
        {
            controllerBrightness->RegisterComponentCallback(PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE,
                []() { std::cout << "ExposureFinishedCallback!\n"; });
            controllerBrightness->RegisterComponentCallback(gainComponent,
                []() { std::cout << "ComponentGainFinishedCallback!\n"; });
            controllerBrightness->RegisterFinishedCallback(
                []() { std::cout << "BrightnessControllerFinishedCallback!\n"; });
            controllerBrightness->RegisterProcessingCallback(
                [](peak_afl_process_data* data) { HandleProcessData(data); });
        }

        if (controllerFocus != nullptr)
        {
            controllerFocus->RegisterFinishedCallback([]() { std::cout << "FocusControllerFinishedCallback!\n"; });
            controllerFocus->RegisterProcessingCallback([](peak_afl_process_data* data) { HandleProcessData(data); });
        }

        if (controllerWhitebalance != nullptr)
        {
            controllerWhitebalance->RegisterFinishedCallback(
                []() { std::cout << "WhitebalanceControllerFinishedCallback!\n"; });
            controllerWhitebalance->RegisterProcessingCallback(
                [](peak_afl_process_data* data) { HandleProcessData(data); });
        }

        // Activate the controllers
        // NOTE: mode is reset to off automatically after the operation finishes
        // when using PEAK_AFL_CONTROLLER_AUTOMODE_ONCE
        if (controllerFocus != nullptr)
        {
            controllerFocus->SetMode(PEAK_AFL_CONTROLLER_AUTOMODE_ONCE);
        }
        if (controllerWhitebalance != nullptr)
        {
            controllerWhitebalance->SetMode(PEAK_AFL_CONTROLLER_AUTOMODE_ONCE);
        }

        if (controllerBrightness != nullptr)
        {
            // Auto brightness mode is split up in two components
            // so you can't use the regular controller.SetMode etc.
            if (controllerBrightness->IsBrightnessComponentUnitSupported(PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE))
            {
                controllerBrightness->BrightnessComponentSetMode(
                    PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE, PEAK_AFL_CONTROLLER_AUTOMODE_ONCE);
            }

            if (controllerBrightness->IsBrightnessComponentUnitSupported(gainComponent))
            {
                controllerBrightness->BrightnessComponentSetMode(
                    gainComponent, PEAK_AFL_CONTROLLER_AUTOMODE_ONCE);
            }
        }

        // Open first data stream
        auto dataStream = device->DataStreams().at(0)->OpenDataStream();
        // Buffer size
        const auto payloadSize = nodeMapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("PayloadSize")
                                      ->Value();

        // Allocate buffers and add them to the pool
        for (int i = 0; i < dataStream->NumBuffersAnnouncedMinRequired(); ++i)
        {
            // Let the TL allocate the buffers
            auto buffer = dataStream->AllocAndAnnounceBuffer(payloadSize, nullptr);
            // Put the buffer in the pool
            dataStream->QueueBuffer(buffer);
        }

        // Lock writeable nodes during acquisition
        nodeMapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("TLParamsLocked")->SetValue(1);

        std::cout << "Starting acquisition...\n";
        dataStream->StartAcquisition();
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->Execute();
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStart")->WaitUntilDone();

        // Process 100 images
        for (int i = 0; i < 100; ++i)
        {
            try
            {
                // Wait for finished/filled buffer event
                const auto buffer = dataStream->WaitForFinishedBuffer(1000);
                const auto img = peak::BufferTo<peak::ipl::Image>(buffer);

                // NOTE: If performance is a concern, then `ids_peak_ipl.ImageConverter`
                //       should be preferred.
                const auto monoImg = img.ConvertTo(peak::ipl::PixelFormatName::Mono8);
                // Put the buffer back in the pool, so it can be filled again
                // NOTE: `ConvertTo` will make a copy, so it is fine to queue
                //       the buffer immediately after.
                dataStream->QueueBuffer(buffer);

                // Process the image in the autofeature manager, which will
                // apply all the actions of associated controllers.
                // Skip processing if another image is still being processed.
                const auto isProcessing = manager.Status();
                if (!isProcessing)
                {
                    manager.Process(monoImg);
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Exception: " << e.what() << "\n";
            }
        }

        std::cout << "Stopping acquisition...\n";
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStop")->Execute();
        nodeMapRemoteDevice->FindNode<peak::core::nodes::CommandNode>("AcquisitionStop")->WaitUntilDone();

        dataStream->StopAcquisition();

        // In case another thread is waiting on WaitForFinishedBuffer
        // you can interrupt it using:
        // data_stream->KillWait();

        // Remove buffers from any associated queue
        dataStream->Flush(peak::core::DataStreamFlushMode::DiscardAll);

        for (const auto& buffer : dataStream->AnnouncedBuffers())
        {
            // Remove buffer from the transport layer
            dataStream->RevokeBuffer(buffer);
        }

        // Unlock writeable nodes again
        nodeMapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("TLParamsLocked")->SetValue(0);

        // Last auto average for the controller working on a mono image
        if (controllerBrightness != nullptr)
        {
            std::cout << "LastAutoAverage: " << static_cast<int>(controllerBrightness->GetLastAutoAverage()) << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
        return -2;
    }

    // One call to `Close` is required for each call to `Initialize`.
    peak::afl::library::Exit();
    peak::Library::Close();
    return 0;
}
