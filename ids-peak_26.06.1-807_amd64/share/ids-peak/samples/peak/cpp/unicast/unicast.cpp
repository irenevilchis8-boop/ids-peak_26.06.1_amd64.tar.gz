/*!
 * \file    unicast.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   This application demonstrates how to use the unicast features of
 *          the transport layer (TL) to find devices on another subnet.
 *
 * \version 1.0.0
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
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include <peak/peak.hpp>

/*! \brief Check if the provided string is a valid IP address
 *
 * \param  ipString String to check
 *
 * \return True if valid
 */
bool isIpAddressValid(const std::string& ipString);

/*! \brief Convert an IP address from its string representation into an integer
 *
 * \param ipString The IP address as string
 *
 * \return The IP address as integer
 */
uint32_t ipStrToInt(const std::string& ipString);

/*! \brief Configure the discovery settings of the given interface
 *
 * Configure the given interface, adding explicit device IP addresses to be discovered using unicast and
 *         set whether to additionally discover via broadcast.
 *
 * If broadcast discovery is disabled, devices can only be discovered via unicast.
 *
 * \param interface      Interface to configure
 * \param allowBroadcast Allow sending a discovery via broadcast and allow a device to answer via broadcast, if it
 *                       decides to.
 * \param ipAddresses    IP addresses to send a unicast discovery to on this interface
 */
void configureInterface(
    std::shared_ptr<peak::core::Interface>& interface, bool allowBroadcast, const std::vector<uint32_t>& ipAddresses);

/*! \brief Filter out all interfaces other than GigEVision.
 *
 * \param interfaceDescriptors Descriptors of the interfaces to be filtered
 *
 * \return Interfaces that are of type GigEVision
*/
std::vector<std::shared_ptr<peak::core::Interface>> filterInterfaces(
    const std::vector<std::shared_ptr<peak::core::InterfaceDescriptor>>& interfaceDescriptors);

/*! \brief Get the IP addresses of the devices we will be looking for.
 *
 * This will prompt the user to enter IP addresses to be searched.
 *
 * \return List of IP Addresses
 */
std::vector<uint32_t> getIpAddresses();

/*! \brief Gather all interfaces of all transport layers found on the system
 *
 * For the purpose of this example, we will only include GigEVision interfaces
 *
 * \return List of all GigEVision interfaces
 */
std::vector<std::shared_ptr<peak::core::Interface>> getInterfaces();

/*! \brief Prompt the user to select an interface.
 *
 * \param interfaces List of interfaces to be selected from
 *
 * \return selected interface
 */
std::shared_ptr<peak::core::Interface> selectInterface(
    std::vector<std::shared_ptr<peak::core::Interface>> interfaces);

/*! \brief Print device information of given devices
 *
 * \param devices Devices to be listed
 */
void printDevices(const std::vector<std::shared_ptr<peak::core::DeviceDescriptor>>& devices);

/*! \brief Search for devices via unicast and without broadcast.
 *
 * This function will only search for GEV (GigEVision) devices. Other devices will not be searched for.
 * Providing the IP will not automatically add a device, only if it replied to the discovery unicast.

 * \param adapterMacAddresses      MAC addresses of the interfaces on which the unicast is to be sent.
 * \param unicastDeviceIpAddresses IP addresses of the devices which are to be discovered.
 *
 * \return List of device descriptors of the devices that have been found
*/
std::vector<std::shared_ptr<peak::core::DeviceDescriptor>> findDevicesViaUnicast(
    std::shared_ptr<peak::core::Interface>& interface, const std::vector<uint32_t>& unicastDeviceIpAddresses);

/*! \bief Wait for enter function
 *
 * The function waits for the user pressing the enter key.
 *
 * This function is called from main() whenever the program exits,
 * either in consequence of an error or after normal termination.
 */
void waitForEnter();

// NOTE: Objects need to be held, otherwise the corresponding components will be closed.
std::vector<std::shared_ptr<peak::core::ProducerLibrary>> gProducers;
std::vector<std::shared_ptr<peak::core::System>> gSystems;
std::vector<std::shared_ptr<peak::core::Interface>> gInterfaces;

int main()
{
    std::cout << "IDS peak genericAPI \"unicast\" Sample v" << VERSION << std::endl;

    // The library must be initialized before use.
    // Each `Initialize` call must be matched with a corresponding call
    // to `Close`.
    peak::Library::Initialize();

    auto interfaces = getInterfaces();
    if(interfaces.empty())
    {
        std::cout << "No interfaces found." << std::endl;
        waitForEnter();
        peak::Library::Close();
        return 0;
    }

    auto interface = selectInterface(interfaces);
    std::cout << "Selected Interface: " << interface->DisplayName() << std::endl;

    const auto unicastIpAddresses = getIpAddresses();

    // NOTE: Devices will only be discovered via unicast, so that no broadcasts are sent.
    //       Therefore, only devices with IP addresses entered above will be found.
    //       Also, this will only list GigEVision devices, USB devices will not be searched for.
    auto deviceDescriptors = findDevicesViaUnicast(interface, unicastIpAddresses);

    if(deviceDescriptors.empty())
    {
        std::cout << "Did not find any devices." << std::endl;
    }
    else
    {
        std::cout << "Found Devices: " << std::endl;
        printDevices(deviceDescriptors);
    }

    waitForEnter();
    // Each `Initialize` call must be matched with a corresponding call to `Close`.
    peak::Library::Close();
    return 0;
}

void printDevices(const std::vector<std::shared_ptr<peak::core::DeviceDescriptor>>& devices)
{
    for(const auto& deviceDescriptor : devices)
    {
        const auto openable = deviceDescriptor->IsOpenable() ? "Openable" : "No Access";
        std::cout << deviceDescriptor->DisplayName() << '(' << openable << ")| "
                  << deviceDescriptor->ParentInterface()->DisplayName() << " -> \""
                  << deviceDescriptor->ParentInterface()->ParentSystem()->CTIFullPath() << "\"\n";
    }
}

std::vector<uint32_t> getIpAddresses()
{
    std::vector<uint32_t> unicastIpAddresses;

    std::cout << "Please enter the IP addresses of the devices you want to find. Press Enter without input to continue."
              << std::endl;

    std::cin.ignore();

    while(true)
    {
        std::string ipAddress;

        std::cout << "Enter IP Address: " << std::flush;
        std::getline(std::cin, ipAddress);

        if(ipAddress.empty())
        {
            break;
        }
        if(!isIpAddressValid(ipAddress))
        {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        unicastIpAddresses.emplace_back(ipStrToInt(ipAddress));
    }

    return unicastIpAddresses;
}

std::shared_ptr<peak::core::Interface> selectInterface(
    std::vector<std::shared_ptr<peak::core::Interface>> interfaces)
{
    unsigned int selectedIndex{};

    while(true)
    {
        for (size_t i = 0; i < interfaces.size(); i++)
        {
            const auto& interface = interfaces.at(i);
            std::cout << i << " | " << interface->DisplayName() << " -> \"" << interface->ParentSystem()->CTIFullPath()
                      << "\"\n";
        }
        std::cout << std::endl << "Select Interface: " << std::flush;

        std::cin >> selectedIndex;
        if (std::cin.fail() || selectedIndex >= interfaces.size())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        break;
    }

    return interfaces.at(selectedIndex);
}

bool isIpAddressValid(const std::string& ipString)
{
    uint8_t numberCounter{};
    uint8_t dotCounter{};

    if(ipString.empty())
    {
        return false;
    }

    for(const char c : ipString)
    {
        if(c >= '0' && c <= '9')
        {
            numberCounter++;
            if(numberCounter > 3)
            {
                return false;
            }
        }
        else if(c == '.')
        {
            dotCounter++;
            if(dotCounter > 3)
            {
                return false;
            }

            numberCounter = 0;
        }
        else
        {
            return false;
        }
    }

    return true;
}

uint32_t ipStrToInt(const std::string& ipString)
{
    if(!isIpAddressValid(ipString))
    {
        throw std::invalid_argument("Invalid IP address: " + ipString);
    }

    std::istringstream iss(ipString);
    std::string byteStr;
    uint32_t ipInt = 0;

    for (int i = 0; i < 4; ++i) {
        std::getline(iss, byteStr, '.');
        ipInt = (ipInt << 8) | std::stoul(byteStr);
    }

    return ipInt;
}

void configureInterface(
    std::shared_ptr<peak::core::Interface>& interface, bool allowBroadcast, const std::vector<uint32_t>& ipAddresses)
{
    auto interfaceNodeMap = interface->NodeMaps().at(0);

    // Try to find necessary nodes to apply configuration
    auto nodeUnicastAddressToAdd = interfaceNodeMap->TryFindNode<peak::core::nodes::IntegerNode>(
        "GevDiscoveryUnicastIPAddressToAdd");
    auto nodeUnicastAddressAdd = interfaceNodeMap->TryFindNode<peak::core::nodes::CommandNode>(
        "GevDiscoveryUnicastIPAddressAdd");
    auto nodeAllowDiscoveryAckBroadcast = interfaceNodeMap->TryFindNode<peak::core::nodes::BooleanNode>(
        "GevAllowDiscoveryACKBroadcast");
    auto nodeAllowDiscoveryCmdBroadcast = interfaceNodeMap->TryFindNode<peak::core::nodes::BooleanNode>(
        "GevAllowDiscoveryCMDBroadcast");

    // Configure Unicast addresses, if supported by the transport layer (TL)
    if(nodeUnicastAddressToAdd != nullptr && nodeUnicastAddressAdd != nullptr)
    {
        for (const auto& ip : ipAddresses)
        {
            nodeUnicastAddressToAdd->SetValue(ip);
            nodeUnicastAddressAdd->Execute();
        }
    }
    else
    {
        std::cout << "WARNING: Interface \"" << interface->DisplayName() << " -> "
                  << interface->ParentSystem()->CTIFullPath() << "\" does not support unicast discovery." << std::endl;
    }

    // Configure whether broadcast is allowed, if supported by the TL
    if(nodeAllowDiscoveryCmdBroadcast != nullptr && nodeAllowDiscoveryAckBroadcast != nullptr)
    {
        nodeAllowDiscoveryCmdBroadcast->SetValue(allowBroadcast);
        nodeAllowDiscoveryAckBroadcast->SetValue(allowBroadcast);
    }
    else
    {
        std::cout << "WARNING: Interface \"" << interface->DisplayName() << " -> "
                  << interface->ParentSystem()->CTIFullPath() << "\" does not support disabling the broadcast."
                  << std::endl;
    }
}

std::vector<std::shared_ptr<peak::core::Interface>> filterInterfaces(
    const std::vector<std::shared_ptr<peak::core::InterfaceDescriptor>>& interfaceDescriptors)
{
    std::vector<std::shared_ptr<peak::core::Interface>> filteredInterfaces;

    for(const auto& interfaceDescriptor : interfaceDescriptors)
    {
        auto interface = interfaceDescriptor->OpenInterface();
        auto interfaceNodeMap = interface->NodeMaps().at(0);

        const auto interfaceType = interfaceNodeMap->FindNode<peak::core::nodes::EnumerationNode>("InterfaceType")
                                       ->CurrentEntry()
                                       ->StringValue();

        // Filter out all interfaces that are not GigEVision
        if(interfaceType != "GigEVision")
        {
            continue;
        }

        filteredInterfaces.emplace_back(std::move(interface));
    }

    return filteredInterfaces;
}

std::vector<std::shared_ptr<peak::core::Interface>> getInterfaces()
{
    // Get Paths of the installed transport layers
    auto ctiPaths = peak::core::EnvironmentInspector::CollectCTIPaths();

    for(const auto& ctiPath : ctiPaths)
    {
        std::shared_ptr<peak::core::ProducerLibrary> producer{};
        std::shared_ptr<peak::core::SystemDescriptor> systemDescriptor{};
        std::shared_ptr<peak::core::System> system{};

        try
        {
            producer = peak::core::ProducerLibrary::Open(ctiPath);
            systemDescriptor = producer->System();
            system = systemDescriptor->OpenSystem();
        }
        catch (const peak::core::Exception& e)
        {
            std::cout << "Failed to load and open cti: " << ctiPath << " with error: " << e.what() << ")" << std::endl;
            continue;
        }

        system->UpdateInterfaces(500);

        auto interfaceDescriptors = system->Interfaces();
        auto filteredInterfaces = filterInterfaces(interfaceDescriptors);

        if(!filteredInterfaces.empty())
        {
            gProducers.push_back(producer);
            gSystems.push_back(system);

            gInterfaces.insert(gInterfaces.end(), std::make_move_iterator(filteredInterfaces.begin()),
                std::make_move_iterator(filteredInterfaces.end()));
        }
    }

    return gInterfaces;
}

std::vector<std::shared_ptr<peak::core::DeviceDescriptor>> findDevicesViaUnicast(
    std::shared_ptr<peak::core::Interface>& interface, const std::vector<uint32_t>& unicastDeviceIpAddresses)
{
    std::vector<std::shared_ptr<peak::core::DeviceDescriptor>> foundDeviceDescriptors;

    // Configure interfaces to discover via unicast and unicast only
    configureInterface(interface, false, unicastDeviceIpAddresses);

    // Send device discoveries and listen for replies
    interface->UpdateDevices(1000);

    auto deviceDescriptors = interface->Devices();
    foundDeviceDescriptors.insert(foundDeviceDescriptors.end(), std::make_move_iterator(deviceDescriptors.begin()),
        std::make_move_iterator(deviceDescriptors.end()));

    return foundDeviceDescriptors;
}

void waitForEnter()
{
    std::cout << std::endl;
#if defined(_WIN32)
    system("pause");
#endif
}
