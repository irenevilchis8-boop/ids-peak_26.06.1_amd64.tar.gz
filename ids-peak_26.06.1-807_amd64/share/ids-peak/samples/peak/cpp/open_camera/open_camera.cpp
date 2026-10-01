/*!
 * \file    open_camera.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2021-03-05
 * \since   1.0.0
 *
 * \brief   This application demonstrates how to use the device manager to open a camera
 *
 * \version 1.1.2
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

#define VERSION "1.1.2"

#include <cstddef>
#include <iostream>

#include <peak/peak.hpp>


/*! \bief Wait for enter function
 *
 * The function waits for the user pressing the enter key.
 *
 * This function is called from main() whenever the program exits,
 * either in consequence of an error or after normal termination.
 */
void wait_for_enter();


int main()
{
    std::cout << "IDS peak genericAPI \"open_camera\" Sample v" << VERSION << std::endl;

    // The library must be initialized before use.
    // Each call to `Initialize` must be matched with a corresponding call to `Close`.
    peak::Library::Initialize();

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
            std::cout << "No device found. Exiting program." << std::endl << std::endl;
            wait_for_enter();
            // One call to `Close` is required for each call to `Initialize`.
            peak::Library::Close();
            return 0;
        }

        // List all available devices.
        size_t i = 0;
        std::cout << "Devices available: " << std::endl;
        for (const auto& deviceDescriptor : deviceManager.Devices())
        {
            std::cout << i << ": " << deviceDescriptor->ModelName() << " ("
                      << deviceDescriptor->ParentInterface()->DisplayName() << "; "
                      << deviceDescriptor->ParentInterface()->ParentSystem()->DisplayName() << " v."
                      << deviceDescriptor->ParentInterface()->ParentSystem()->Version() << ")" << std::endl;
            ++i;
        }

        // Select a device to open.
        size_t selectedDevice = 0;

        // Prompt user for device index or remove this block to always use the first device.
        std::cout << std::endl << "Select device index to open [0-" << deviceManager.Devices().size() - 1 << "]: ";
        std::cin >> selectedDevice;

        if (std::cin.fail())
        {
            std::cout << "Invalid input! Using index 0." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            selectedDevice = 0;
        }

        if (selectedDevice >= deviceManager.Devices().size())
        {
            std::cout << "Invalid index! Using index 0." << std::endl;
            selectedDevice = 0;
        }

        // Open the selected device with control access.
        // The access types correspond to the GenTL `DEVICE_ACCESS_FLAGS`.
        auto device = deviceManager.Devices().at(selectedDevice)->OpenDevice(peak::core::DeviceAccessType::Control);

        // Retrieve the remote device's primary node map.
        // In GenICam, a node map represents a hierarchical set of parameters (features)
        // such as exposure, gain, or firmware info. This node map provides access to controls
        // implemented on the device itself, typically following the GenICam SFNC, while still
        // allowing for vendor-specific extensions.
        auto nodeMapRemoteDevice = device->RemoteDevice()->NodeMaps().at(0);

        try
        {
            // Print model name using the "DeviceModelName" node.
            std::cout
                << "Model Name: "
                << nodeMapRemoteDevice->FindNode<peak::core::nodes::StringNode>("DeviceModelName")->Value()
                << std::endl;
        }
        catch (const std::exception&)
        {
            // If the node is not implemented or not available.
            std::cout << "Model Name: (unknown)" << std::endl;
        }

        try
        {
            // Print user ID using the "DeviceUserID" node.
            std::cout << "User ID: "
                      << nodeMapRemoteDevice->FindNode<peak::core::nodes::StringNode>("DeviceUserID")->Value()
                      << std::endl;
        }
        catch (const std::exception&)
        {
            std::cout << "User ID: (unknown)" << std::endl;
        }

        try
        {
            // Print sensor information using the "SensorName" node.
            std::cout << "Sensor Name: "
                      << nodeMapRemoteDevice->FindNode<peak::core::nodes::StringNode>("SensorName")->Value()
                      << std::endl;
        }
        catch (const std::exception&)
        {
            std::cout << "Sensor Name: (unknown)" << std::endl;
        }

        try
        {
            // Print maximum sensor resolution (width x height).
            std::cout << "Max. resolution (w x h): "
                      << nodeMapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("WidthMax")->Value()
                      << " x "
                      << nodeMapRemoteDevice->FindNode<peak::core::nodes::IntegerNode>("HeightMax")->Value()
                      << std::endl;
        }
        catch (const std::exception&)
        {
            std::cout << "Max. resolution (w x h): (unknown)" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
    }

    wait_for_enter();
    // One call to `Close` is required for each call to `Initialize`.
    peak::Library::Close();
    return 0;
}


void wait_for_enter()
{
    std::cout << std::endl;
#if defined(_WIN32)
    system("pause");
#endif
}
