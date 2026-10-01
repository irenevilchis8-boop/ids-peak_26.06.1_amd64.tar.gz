/*!
 * \file    peak_afl_generic_auto_white_balance.hpp
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
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_roi.hpp>

#include <peak_common_c/detail/peak_common_defines.h>

#include <functional>
#include <memory>

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
class GenericWhiteBalance : public IController
{
    using ProcessingCallback = std::function<void()>;

public:
    explicit GenericWhiteBalance(peak::afl::Manager& manager, ProcessingCallback callback)
        : IController(manager)
        , m_controller{ peak::afl::Controller::Create(PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE) }
        , m_processingCallback{ std::move(callback) }
        , m_skipFrames{ std::make_unique<features::SkipFrames>(m_controller) }
        , m_roi{ std::make_unique<features::Roi>(m_controller) }
    {
        GetManager().AddController(m_controller);

        m_controller->RegisterFinishedCallback([this]() { m_FinishedCallbackManager.TriggerCallbacks(); });

        m_controller->RegisterProcessingCallback([this](peak_afl_process_data* data) {
            auto* whitebalance = reinterpret_cast<peak_afl_process_data_whitebalance*>(data);
            if (whitebalance->controller_component != PEAK_AFL_CONTROLLER_WHITEBALANCE_COMPONENT_HOST_GAIN)
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
        return "GenericWhitebalance";
    }

    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        for (const auto& feature :
            std::initializer_list<const peak::common::serialization::ISerializable*>{ m_skipFrames.get(), m_roi.get() })
        {
            feature->Serialize(archive);
        }

        archive.SetString("Mode", ToString(GetMode()));
    }

    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        for (const auto& feature :
            std::initializer_list<peak::common::serialization::ISerializable*>{ m_skipFrames.get(), m_roi.get() })
        {
            feature->Deserialize(archive);
        }

        SetMode(detail::ToControllerMode(archive.GetString("Mode")));
    }

    void SetMode(ControllerMode mode) override
    {
        m_controller->SetMode(detail::ToCType(mode));
    }

    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return detail::ToControllerMode(m_controller->GetMode());
    }

    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return GetMode() != ControllerMode::Off;
    }

    void ResetToDefault() override
    {
        SetMode(ControllerMode::Off);
        SkipFrames().Set(2);
        Roi().Set({});
    }

    PEAK_COMMON_NO_DISCARD features::SkipFrames& SkipFrames() const
    {
        return *m_skipFrames;
    }

    PEAK_COMMON_NO_DISCARD features::Roi& Roi() const
    {
        return *m_roi;
    }

    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return ControllerType::WhiteBalance;
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
    std::shared_ptr<peak::afl::Controller> m_controller;

    peak::core::TTriggerCallbackManager<IController::FinishedCallbackHandle, IController::FinishedCallback>
        m_FinishedCallbackManager;
    ProcessingCallback m_processingCallback{};

    std::unique_ptr<features::SkipFrames> m_skipFrames{};
    std::unique_ptr<features::Roi> m_roi{};
};
} // namespace detail
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
