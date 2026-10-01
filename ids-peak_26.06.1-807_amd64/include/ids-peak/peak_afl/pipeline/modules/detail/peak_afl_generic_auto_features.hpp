/*!
 * \file    peak_afl_generic_auto_features.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <memory>

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_advanced_auto_brightness.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_advanced_auto_focus.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_advanced_auto_white_balance.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_basic_auto_brightness.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_basic_auto_focus.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_basic_auto_white_balance.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>

#if defined(__has_include)
#    if __has_include(<peak_icv/types/peak_icv_image.hpp>)
#        include <peak_icv/types/peak_icv_image.hpp>
#        define HAS_PEAK_ICV_IMAGE 1
#    endif
#endif

#include <peak_ipl/types/peak_ipl_image.hpp>
#include <peak/device/peak_device.hpp>
#include <peak/node_map/peak_node_map.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/pipeline/modules/peak_common_iautofeature_module.hpp>
#include <peak_common/pipeline/modules/peak_common_igain_module.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>


namespace peak
{
namespace pipeline
{
namespace modules
{
namespace detail
{
class GenericAutoFeatures : public IAutoFeature
{
    static constexpr int moduleVersion = 1;

public:
    friend class autofeature::BrightnessComponent;

    explicit GenericAutoFeatures(const std::shared_ptr<peak::core::Device>& device, bool advanced = true)
        : m_remoteDeviceNodeMap{ device ?
                device->RemoteDevice()->NodeMaps().at(0) :
                throw peak::afl::error::InvalidParameterException("The given device is not valid!", PEAK_AFL_STATUS_ERROR) }
        , m_manager{ m_remoteDeviceNodeMap }
    {
        const auto isColorCamera = [this]() {
            const auto pixelFormatNode = m_remoteDeviceNodeMap->TryFindNode<peak::core::nodes::EnumerationNode>("PixelFormat");
            if (pixelFormatNode == nullptr || !pixelFormatNode->IsReadable())
            {
                return false;
            }

            for (const auto& entry : pixelFormatNode->AvailableEntries())
            {
                try
                {
                    const auto pixelFormatInfo = peak::common::PixelFormatInfo(static_cast<peak::common::PixelFormat>(entry->Value()));
                    // If the camera supports bayer it is a color camera
                    if (pixelFormatInfo.HasChannel(peak::common::Channel::Bayer) || !pixelFormatInfo.IsSingleChannel())
                    {
                        return true;
                    }
                }
                catch (const std::exception&)
                {
                    // ignore unknown pixelformats
                }
            }

            return false;
        };

        for (const auto& controllerType :
            { autofeature::ControllerType::Focus, autofeature::ControllerType::Brightness, autofeature::ControllerType::WhiteBalance })
        {
            if (controllerType == autofeature::ControllerType::WhiteBalance && !isColorCamera())
            {
                continue;
            }

            if (m_manager.IsControllerSupported(autofeature::detail::ToCType(controllerType)))
            {
                auto controller = CreateController(m_manager, controllerType, advanced);
                m_controllers.emplace_back(std::move(controller));
            }
        }

        m_manager.SetGainIPL(m_gain);

        GenericAutoFeatures::ResetToDefault();
    }

    ~GenericAutoFeatures() override = default;

    PEAK_COMMON_NO_DISCARD const char* GetType() const override
    {
        return "GenericAutoFeatures";
    }

    void SetEnabled(bool enabled) override
    {
        m_enabled = enabled;
    }

    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetInt("Version", moduleVersion);
        archive.SetBool("Enabled", m_enabled);

        for (const auto& controller : m_controllers)
        {
            auto controllerArchive = archive.CreateArchive();
            controller->Serialize(*controllerArchive);

            archive.SetArchive(controller->GetName(), std::move(controllerArchive));
        }
    }

    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        const auto version{ archive.GetInt("Version") };
        if (version < 1)
        {
            throw peak::afl::error::CorruptedDataException(
                "Version " + std::to_string(version) + " is invalid. Must be at least 1", PEAK_AFL_STATUS_ERROR);
        }

        m_enabled = archive.GetBool("Enabled");
        for (const auto& controller : m_controllers)
        {
            auto controllerArchive = archive.GetArchive(controller->GetName());
            controller->Deserialize(*controllerArchive);
        }
    }

    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override
    {
        return m_enabled;
    }

    PEAK_COMMON_NO_DISCARD std::vector<autofeature::detail::IController*> GetControllers() const
    {
        std::vector<autofeature::detail::IController*> controllers;
        std::transform(
            m_controllers.begin(), m_controllers.end(), std::back_inserter(controllers), [](const auto& elem) { return elem.get(); });
        return controllers;
    }

    PEAK_COMMON_NO_DISCARD autofeature::detail::IController* GetController(autofeature::ControllerType controllerType) const
    {
        const auto& controllers = GetControllers();
        const auto result = std::find_if(
            controllers.begin(), controllers.end(), [controllerType](const auto* elem) { return elem->GetType() == controllerType; });
        if (result != controllers.end())
        {
            return *result;
        }

        return nullptr;
    }

    PEAK_COMMON_NO_DISCARD bool HasController(autofeature::ControllerType controllerType) const
    {
        const auto& controllers = GetControllers();
        const auto result = std::find_if(
            controllers.begin(), controllers.end(), [controllerType](const auto* elem) { return elem->GetType() == controllerType; });
        return result != controllers.end();
    }

    void ResetToDefault() override
    {
        for (auto* controller : GetControllers())
        {
            controller->ResetToDefault();
        }
    }

    void SetGainModule(std::shared_ptr<peak::pipeline::modules::IGain> gainModule) override
    {
        m_gainModule = gainModule;
    }

    void SetColorCorrectionMatrix(const std::array<float, 9>& ccm) override
    {
        m_manager.SetCCM(ccm);
    }

    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override
    {
        if (!IsEnabled())
        {
            return input;
        }

        const auto isProcessing = m_manager.Status();
        if (isProcessing)
        {
            return input;
        }

#if defined(HAS_PEAK_ICV_IMAGE) && defined(WITH_peak_ipl)
        if (input.GetType() == typeid(peak::icv::Image))
        {
            m_manager.Process(input.AnyCast<peak::icv::Image>());
        }
        else
#endif
            if (input.GetType() == typeid(peak::ipl::Image))
        {
            m_manager.Process(input.AnyCast<peak::ipl::Image>());
        }
        else
        {
            throw peak::afl::error::InvalidCastException("Unsupported input type!", PEAK_AFL_STATUS_INVALID_PARAMETER);
        }

        return input;
    }

private:
    PEAK_COMMON_NO_DISCARD std::unique_ptr<autofeature::detail::IController> CreateController(
        peak::afl::Manager& manager, autofeature::ControllerType controllerType, bool advanced)
    {
        switch (controllerType)
        {
        case autofeature::ControllerType::Focus:
            if (advanced)
            {
                return std::make_unique<autofeature::AdvancedAutoFocus>(manager);
            }
            return std::make_unique<autofeature::BasicAutoFocus>(manager);

        case autofeature::ControllerType::Brightness: {
            auto callback = [this]() {
                if (!m_gainModule)
                {
                    return;
                }
                m_gainModule->SetMaster(m_gain.MasterGainValue());
            };

            if (advanced)
            {
                return std::make_unique<autofeature::AdvancedAutoBrightness>(manager, callback);
            }
            return std::make_unique<autofeature::BasicAutoBrightness>(manager, callback);
        }

        case autofeature::ControllerType::WhiteBalance:
            auto callback = [this]() {
                if (!m_gainModule)
                {
                    return;
                }

                m_gainModule->SetRed(m_gain.RedGainValue());
                m_gainModule->SetGreen(m_gain.GreenGainValue());
                m_gainModule->SetBlue(m_gain.BlueGainValue());
            };

            if (advanced)
            {
                return std::make_unique<autofeature::AdvancedAutoWhiteBalance>(manager, callback);
            }
            return std::make_unique<autofeature::BasicAutoWhiteBalance>(manager, callback);
        }
        throw peak::afl::error::InternalErrorException("Unknown controller type", PEAK_AFL_STATUS_ERROR);
    }

    std::shared_ptr<peak::core::NodeMap> m_remoteDeviceNodeMap{};

    std::vector<std::unique_ptr<autofeature::detail::IController>> m_controllers{};
    peak::afl::Manager m_manager;

    std::shared_ptr<modules::IGain> m_gainModule{};
    peak::ipl::Gain m_gain{};

    bool m_enabled{ true };
};
} // namespace detail
} // namespace modules
} // namespace pipeline 
} // namespace peak
