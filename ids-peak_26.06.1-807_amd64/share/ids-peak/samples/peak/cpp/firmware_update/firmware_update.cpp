/*!
 * \file    firmware_update.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-07-12
 *
 * \brief   This application demonstrates how to update the firmware of devices using a .guf file
 *
 * \version 1.0.1
 *
 * Copyright (C) 2024 - 2026, IDS Imaging Development Systems GmbH.
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

#define VERSION "1.0.1"

#include <cstddef>
#include <iostream>
#include <iomanip>

#include <peak/peak.hpp>


/*! \bief Wait for enter function
 *
 * The function waits for the user pressing the enter key.
 *
 * This function is called from main() whenever the program exits,
 * either in consequence of an error or after normal termination.
 */
void wait_for_enter();


struct DeviceUpdateInformation
{
    std::shared_ptr<peak::core::DeviceDescriptor> device;
    std::shared_ptr<peak::core::FirmwareUpdateInformation> updateInformation;
};

/*!
 * \brief Find connected devices that can be updated using the provided .guf file
 *        at \p gufPath
 *
 * \return A vector of devices and their corresponding updateinformation for the latest
 *         version contained in the .guf file.
 */
std::vector<DeviceUpdateInformation> FindCompatibleDevices(const peak::DeviceManager& deviceManager,
        peak::core::FirmwareUpdater& updater, const char* gufPath);

/*!
 * \brief Register message callbacks on the update observer, so we get notified
 *        about firmware update status changes.
 */
void RegisterObserverCallbacks(peak::core::FirmwareUpdateProgressObserver& observer,
                               const DeviceUpdateInformation& update);


int main(int argc, const char* argv[])
{
    std::cout << "IDS peak genericAPI \"firmware_update\" Sample v" << VERSION << std::endl;

    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments! Usage: firmware_update_cpp <gufPath>\n";
        return -1;
    }

    // The library must be initialized before use.
    // Each `Initialize` call must be matched with a corresponding call
    // to `Close`.
    peak::Library::Initialize();

    const char* gufPath = argv[1];

    // Get the device manager singleton.
    auto& deviceManager = peak::DeviceManager::Instance();

    try
    {
        // Update the device manager.
        // When `Update` is called, it searches for all producer libraries
        // contained in the directories found in the official GenICam GenTL
        // environment variable GENICAM_GENTL{32/64}_PATH. It then opens all
        // found ProducerLibraries, their Systems, their Interfaces, and lists
        // all available DeviceDescriptors.
        deviceManager.Update();

        // Exit program if no device was found.
        if (deviceManager.Devices().empty())
        {
            std::cout << "No device found. Exiting program." << std::endl << std::endl;

            peak::Library::Close();
            wait_for_enter();
            return 0;
        }

        peak::core::FirmwareUpdater updater{};

        // Get a list of devices compatible with the firmware file.
        std::vector<DeviceUpdateInformation> compatibleDeviceUpdates = FindCompatibleDevices(
            deviceManager, updater, gufPath);

        if(compatibleDeviceUpdates.empty())
        {
            std::cout << "No compatible devices found." << std::endl;
            peak::Library::Close();
            wait_for_enter();
            return 0;
        }

        std::cout << "The following devices will be updated:\n";
        for (const auto& update : compatibleDeviceUpdates)
        {
            std::cout << "\t" << update.device->ModelName()
                << " (" << update.device->SerialNumber() << ")\n";
        }

        std::cout << "Continue? y/n: ";
        char answer{};
        std::cin >> answer;

        if (answer != 'y')
        {
            std::cout << "Update aborted!\n";
            peak::Library::Close();

            wait_for_enter();
            return 0;
        }

        for (const auto& update : compatibleDeviceUpdates)
        {
            // NOTE: `UpdateDevice` is a blocking call. We construct an
            //       observer and register callbacks to be notified about
            //       the update progress.
            peak::core::FirmwareUpdateProgressObserver observer{};
            RegisterObserverCallbacks(observer, update);

            updater.UpdateDevice(update.device, update.updateInformation, &observer);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Each `Initialize` call must be matched with a corresponding call
    // to `Close`.
    peak::Library::Close();

    wait_for_enter();

    return 0;
}

std::vector<DeviceUpdateInformation> FindCompatibleDevices(const peak::DeviceManager& deviceManager,
        peak::core::FirmwareUpdater& updater, const char* gufPath)
{
    std::vector<DeviceUpdateInformation> compatibleDeviceUpdates;
    for (const auto& device : deviceManager.Devices())
    {
        // Only proceed with devices that are openable with control-level access.
        // This ensures the device can be accessed for firmware operations.
        if (!device->IsOpenable(peak::core::DeviceAccessType::Control))
        {
            std::cerr << "Skipped device " << device->ModelName() << " ("
                << device->SerialNumber() << "), since it could not be opened!\n";
            continue;
        }

        // NOTE: Skip devices that were already added, since they can show
        //       up over multiple interfaces (transport layers, network cards, ...)
        const auto isDeviceAlreadyAdded = std::any_of(compatibleDeviceUpdates.cbegin(), compatibleDeviceUpdates.cend(),
                [&device](const auto& existingUpdate) {
            return device->SerialNumber() == existingUpdate.device->SerialNumber();
        });
        if (isDeviceAlreadyAdded)
        {
            continue;
        }

        // Query the updater for update information compatible with the device.
        // If the list is empty, the GUF file does not apply to this device.
        const auto updateInformationList = updater.CollectFirmwareUpdateInformation(gufPath, device);
        if (!updateInformationList.empty())
        {
            // Select the latest available firmware update entry for the device.
            const auto& latestUpdateInformation = updateInformationList.front();
            compatibleDeviceUpdates.emplace_back(
                DeviceUpdateInformation{device, latestUpdateInformation});
        }
    }

    return compatibleDeviceUpdates;
}

void RegisterObserverCallbacks(peak::core::FirmwareUpdateProgressObserver& observer, const DeviceUpdateInformation& update)
{
    // Copy model and serial number early, since the device object will become
    // invalid after the update starts.
    const auto modelName = update.device->ModelName();
    const auto serialNumber = update.device->SerialNumber();

    // Called once at the beginning of the firmware update process.
    // `updateInformation` includes firmware metadata like Version and Description, among other details.
    observer.RegisterUpdateStartedCallback([=](
            const std::shared_ptr<peak::core::FirmwareUpdateInformation>& updateInformation, uint32_t /* estimatedDuration_ms */) {
        std::cout << "Updating " << modelName << " (" << serialNumber
            << ") to version " << updateInformation->Version() << std::endl;
    });

    // Called once when the firmware update completes successfully.
    observer.RegisterUpdateFinishedCallback([=]() {
        std::cout << "Finished updating " << modelName << " (" << serialNumber
            << ")" << std::endl;
    });

    // Called if the firmware update fails at any point.
    // The `errorDescription` parameter provides details on why the update failed.
    observer.RegisterUpdateFailedCallback([=](const std::string& errorDescription) {
        std::cout << "Updating failed " << modelName << " (" << serialNumber
            << "): " << errorDescription << std::endl;
    });

    // Called at the start of each update step (e.g., reboot, or write).
    // Includes step type, estimated duration, and a human-readable description.
    observer.RegisterUpdateStepStartedCallback([=](peak::core::FirmwareUpdateStep updateStep,
                                                   uint32_t /* estimatedDuration_ms */, const std::string& description) {
        std::cout << modelName << " (" << serialNumber << ") | " << peak::core::ToString(updateStep)
            << " | " << description << std::endl;
    });

    // NOTE: You can also register for `UpdateStepFinishedEvent` for even more
    //       granular step tracking.
    // observer.RegisterUpdateStepFinishedCallback

    // Called periodically to report the progress percentage (0–100%) of the current update step.
    observer.RegisterUpdateStepProgressChangedCallback([=](peak::core::FirmwareUpdateStep  /* updateStep */, double progressPercentage) {
        std::cout << "\r\tProgress: " << std::fixed << std::setprecision(2) << progressPercentage << "%";
        if (progressPercentage == 100)
        {
            std::cout << "\n";
        }
        std::cout << std::flush;
    });
}

void wait_for_enter()
{
    std::cout << std::endl;
#if defined(_WIN32)
    system("pause");
#endif
}
