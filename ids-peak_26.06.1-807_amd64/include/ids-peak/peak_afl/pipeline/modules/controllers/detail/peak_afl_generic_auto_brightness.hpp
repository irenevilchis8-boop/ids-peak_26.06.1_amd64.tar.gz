/*!
 * \file    peak_afl_generic_auto_brightness.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_percentile.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_target.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_tolerance.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_component.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_limit.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_roi.hpp>

#include <peak/generic/peak_t_callback_manager.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>

#include <algorithm>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
namespace detail
{
inline std::unique_ptr<features::BrightnessLimit> CreateBrightnessLimit(
    std::shared_ptr<peak::afl::Controller> controller, BrightnessComponentType type)
{
    switch (type)
    {
    case BrightnessComponentType::Exposure:
        return std::make_unique<features::BrightnessExposureLimit>(std::move(controller));
    case BrightnessComponentType::Gain:
        return std::make_unique<features::BrightnessGainLimit>(std::move(controller));
    case BrightnessComponentType::AnalogGain:
        return std::make_unique<features::BrightnessGainAnalogLimit>(std::move(controller));
    case BrightnessComponentType::DigitalGain:
        return std::make_unique<features::BrightnessGainDigitalLimit>(std::move(controller));
    case BrightnessComponentType::CombinedGain:
        return std::make_unique<features::BrightnessGainCombinedLimit>(std::move(controller));
    case BrightnessComponentType::HostGain:
        return std::make_unique<features::BrightnessGainHostLimit>(std::move(controller));
    default:
        throw peak::afl::error::InvalidParameterException("Unknown brightness component type", PEAK_AFL_STATUS_INVALID_PARAMETER);
    }
}

class GenericAutoBrightness : public IController
{
    using ProcessingCallback = std::function<void()>;

public:
    friend BrightnessComponent;

    explicit GenericAutoBrightness(
        peak::afl::Manager& manager, ProcessingCallback callback, const std::vector<BrightnessComponentType>& componentTypes)
        : IController(manager)
        , m_controller{ peak::afl::Controller::Create(PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS) }
        , m_processingCallback{ std::move(callback) }
        , m_skipFrames{ std::make_unique<features::SkipFrames>(m_controller) }
        , m_autoTarget{ std::make_unique<features::AutoTarget>(m_controller) }
        , m_autoTolerance{ std::make_unique<features::AutoTolerance>(m_controller) }
        , m_autoPercentile{ std::make_unique<features::AutoPercentile>(m_controller) }
        , m_roi{ std::make_unique<features::Roi>(m_controller) }
        , m_brightnessAlgorithm{ std::make_unique<features::BrightnessAlgorithm>(m_controller) }
    {
        GetManager().AddController(m_controller);

        m_brightnessComponents.reserve(componentTypes.size());
        for (const auto& componentType : componentTypes)
        {
            if (!m_controller->IsBrightnessComponentUnitSupported(detail::ToCType(componentType)))
            {
                continue;
            }

            m_brightnessComponents.emplace_back(std::unique_ptr<BrightnessComponent>(
                new BrightnessComponent(m_controller, componentType, detail::CreateBrightnessLimit(m_controller, componentType))));
        }

        m_controller->RegisterFinishedCallback([this]() { m_FinishedCallbackManager.TriggerCallbacks(); });

        m_controller->RegisterProcessingCallback([this](peak_afl_process_data* data) {
            auto* brightness = reinterpret_cast<peak_afl_process_data_brightness*>(data);
            if (brightness->controller_component != PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_HOST_GAIN)
            {
                return;
            }

            if (m_processingCallback)
            {
                m_processingCallback();
            }
        });
    }

    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "GenericAutoBrightness";
    }

    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        for (const auto& feature : std::initializer_list<ISerializable*>{ m_skipFrames.get(), m_autoTarget.get(), m_autoTolerance.get(),
                 m_autoPercentile.get(), m_roi.get(), m_brightnessAlgorithm.get() })
        {
            feature->Serialize(archive);
        }

        for (const auto& component : m_brightnessComponents)
        {
            auto componentArchive = archive.CreateArchive();
            component->Serialize(*componentArchive);

            archive.SetArchive(ToString(component->GetType()), componentArchive);
        }
    }

    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        for (const auto& feature : std::initializer_list<ISerializable*>{ m_skipFrames.get(), m_autoTarget.get(), m_autoTolerance.get(),
                 m_autoPercentile.get(), m_roi.get(), m_brightnessAlgorithm.get() })
        {
            feature->Deserialize(archive);
        }

        for (const auto& component : m_brightnessComponents)
        {
            auto componentArchive = archive.GetArchive(ToString(component->GetType()));
            component->Deserialize(*componentArchive);
        }
    }

    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return ControllerType::Brightness;
    }

    void SetMode(ControllerMode mode) override
    {
        for (const auto& component : m_brightnessComponents)
        {
            component->SetMode(mode);
        }
    }

    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        ControllerMode controllerMode{};
        for (const auto& component : m_brightnessComponents)
        {
            if (controllerMode == ControllerMode::Continuous)
            {
                return controllerMode;
            }

            controllerMode = (std::max)(controllerMode, component->GetMode());
        }

        return controllerMode;
    }

    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return GetMode() != ControllerMode::Off;
    }

    PEAK_COMMON_NO_DISCARD features::SkipFrames& SkipFrames() const
    {
        return *m_skipFrames;
    }

    PEAK_COMMON_NO_DISCARD features::AutoTarget& AutoTarget() const
    {
        return *m_autoTarget;
    }

    PEAK_COMMON_NO_DISCARD features::AutoTolerance& AutoTolerance() const
    {
        return *m_autoTolerance;
    }

    PEAK_COMMON_NO_DISCARD features::AutoPercentile& AutoPercentile() const
    {
        return *m_autoPercentile;
    }

    PEAK_COMMON_NO_DISCARD features::Roi& Roi()
    {
        return *m_roi;
    }

    PEAK_COMMON_NO_DISCARD features::BrightnessAlgorithm& AnalysisAlgorithm() const
    {
        return *m_brightnessAlgorithm;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent& ExposureComponent() const
    {
        auto* component = GetComponent(BrightnessComponentType::Exposure);
        if (nullptr == component)
        {
            throw peak::afl::error::NotSupportedException(
                "Exposure component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        return *component;
    }

    PEAK_COMMON_NO_DISCARD bool HasExposureComponent() const
    {
        return GetComponent(BrightnessComponentType::Exposure) != nullptr;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent& AnalogGainComponent() const
    {
        auto* component = GetComponent(BrightnessComponentType::AnalogGain);
        if (nullptr == component)
        {
            throw peak::afl::error::NotSupportedException(
                "Analog gain component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        return *component;
    }

    PEAK_COMMON_NO_DISCARD bool HasAnalogGainComponent() const
    {
        return GetComponent(BrightnessComponentType::AnalogGain) != nullptr;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent& DigitalGainComponent() const
    {
        auto* component = GetComponent(BrightnessComponentType::DigitalGain);
        if (nullptr == component)
        {
            throw peak::afl::error::NotSupportedException(
                "Digital gain component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        return *component;
    }

    PEAK_COMMON_NO_DISCARD bool HasDigitalGainComponent() const
    {
        return GetComponent(BrightnessComponentType::DigitalGain) != nullptr;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent& CombinedGainComponent() const
    {
        auto* component = GetComponent(BrightnessComponentType::CombinedGain);
        if (nullptr == component)
        {
            throw peak::afl::error::NotSupportedException(
                "Combined gain component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        return *component;
    }

    PEAK_COMMON_NO_DISCARD bool HasCombinedGainComponent() const
    {
        return GetComponent(BrightnessComponentType::CombinedGain) != nullptr;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent& HostGainComponent() const
    {
        auto* component = GetComponent(BrightnessComponentType::HostGain);
        if (nullptr == component)
        {
            throw peak::afl::error::NotSupportedException(
                "Host gain component is not available! Call IAutofeature::SetGainModule to set gain module!",
                PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        return *component;
    }

    PEAK_COMMON_NO_DISCARD bool HasHostGainComponent() const
    {
        return GetComponent(BrightnessComponentType::HostGain) != nullptr;
    }

    PEAK_COMMON_NO_DISCARD std::vector<BrightnessComponent*> GetComponents() const
    {
        std::vector<BrightnessComponent*> components;
        std::transform(m_brightnessComponents.begin(), m_brightnessComponents.end(), std::back_inserter(components),
            [](const auto& elem) { return elem.get(); });
        return components;
    }

    PEAK_COMMON_NO_DISCARD BrightnessComponent* GetComponent(BrightnessComponentType componentType) const
    {
        auto entry = std::find_if(m_brightnessComponents.begin(), m_brightnessComponents.end(),
            [componentType](const std::unique_ptr<BrightnessComponent>& component) { return component->GetType() == componentType; });
        if (entry != m_brightnessComponents.end())
        {
            return entry->get();
        }
        return {};
    }

    void ResetToDefault() override
    {
        SetMode(ControllerMode::Off);
        SkipFrames().Set(2);
        AutoPercentile().Set(13);
        AutoTarget().Set(150);
        AutoTolerance().Set(3);
        AnalysisAlgorithm().Set(BrightnessAnalysisAlgorithm::Median);
        Roi().Set({});

        for (auto* component : GetComponents())
        {
            component->SetLimit({ 0, (std::numeric_limits<double>::max)() });
        }
    }

    IController::FinishedCallbackHandle RegisterFinishedCallback(const IController::FinishedCallback& callback)
    {
        return m_FinishedCallbackManager.RegisterCallback(callback);
    }

    void UnregisterFinishedCallback(IController::FinishedCallbackHandle callbackHandle)
    {
        m_FinishedCallbackManager.UnregisterCallback(callbackHandle);
    }

private:
    peak::core::TTriggerCallbackManager<IController::FinishedCallbackHandle, IController::FinishedCallback>
        m_FinishedCallbackManager;

    std::shared_ptr<peak::afl::Controller> m_controller{};
    std::vector<std::unique_ptr<BrightnessComponent>> m_brightnessComponents{};
    ProcessingCallback m_processingCallback{};

    std::unique_ptr<features::SkipFrames> m_skipFrames{};
    std::unique_ptr<features::AutoTarget> m_autoTarget{};
    std::unique_ptr<features::AutoTolerance> m_autoTolerance{};
    std::unique_ptr<features::AutoPercentile> m_autoPercentile{};
    std::unique_ptr<features::Roi> m_roi{};
    std::unique_ptr<features::BrightnessAlgorithm> m_brightnessAlgorithm{};
};
} // namespace detail
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
