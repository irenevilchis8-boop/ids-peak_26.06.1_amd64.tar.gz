/*!
 * \file    peak_afl_generic_auto_focus.hpp
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
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_focus_limit.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_hysteresis.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_search_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_sharpness_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_weighted_rois.hpp>

#include <peak_common_c/detail/peak_common_defines.h>

#include <peak/generic/peak_t_callback_manager.hpp>

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
class GenericAutoFocus : public IController
{
public:
    explicit GenericAutoFocus(peak::afl::Manager& manager)
        : IController(manager)
        , m_controller{ peak::afl::Controller::Create(PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS) }
        , m_skipFrames{ std::make_unique<features::SkipFrames>(m_controller) }
        , m_hysteresis{ std::make_unique<features::Hysteresis>(m_controller) }
        , m_weightedRois{ std::make_unique<features::WeightedRois>(m_controller) }
        , m_sharpnessAlgorithm{ std::make_unique<features::SharpnessAlgorithm>(m_controller) }
        , m_searchAlgorithm{ std::make_unique<features::SearchAlgorithm>(m_controller) }
        , m_focusLimit{ std::make_unique<features::FocusLimit>(m_controller) }
    {
        GetManager().AddController(m_controller);

        m_controller->RegisterFinishedCallback([this]() { m_FinishedCallbackManager.TriggerCallbacks(); });
    }

    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "GenericAutoFocus";
    }

    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        for (const auto& feature : std::initializer_list<const peak::common::serialization::ISerializable*>{ m_skipFrames.get(),
                 m_hysteresis.get(), m_weightedRois.get(), m_sharpnessAlgorithm.get(), m_searchAlgorithm.get(), m_focusLimit.get() })
        {
            feature->Serialize(archive);
        }

        archive.SetString("Mode", ToString(GetMode()));
    }

    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        for (const auto& feature : std::initializer_list<peak::common::serialization::ISerializable*>{ m_skipFrames.get(),
                 m_hysteresis.get(), m_weightedRois.get(), m_sharpnessAlgorithm.get(), m_searchAlgorithm.get(), m_focusLimit.get() })
        {
            feature->Deserialize(archive);
        }

        SetMode(detail::ToControllerMode(archive.GetString("Mode")));
    }

    void SetMode(ControllerMode mode) override
    {
        m_controller->SetMode(ToCType(mode));
    }

    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return ToControllerMode(m_controller->GetMode());
    }

    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return GetMode() != ControllerMode::Off;
    }

    void ResetToDefault() override
    {
        SetMode(ControllerMode::Off);
        SkipFrames().Set(2);
        SearchAlgorithm().Set(FocusSearchAlgorithm::GoldenRatio);
        SharpnessAlgorithm().Set(FocusSharpnessAlgorithm::Tenengrad);

        const auto focusLimit = m_controller->GetDefaultLimit();
        FocusLimit().Set({ focusLimit.min, focusLimit.max });
        Hysteresis().Set(8);

        m_controller->SetROIPreset(PEAK_AFL_CONTROLLER_ROI_PRESET_CENTER);
    }

    PEAK_COMMON_NO_DISCARD features::SkipFrames& SkipFrames() const
    {
        return *m_skipFrames;
    }

    PEAK_COMMON_NO_DISCARD features::Hysteresis& Hysteresis() const
    {
        return *m_hysteresis;
    }

    PEAK_COMMON_NO_DISCARD features::WeightedRois& WeightedROIs() const
    {
        return *m_weightedRois;
    }

    PEAK_COMMON_NO_DISCARD features::SharpnessAlgorithm& SharpnessAlgorithm() const
    {
        return *m_sharpnessAlgorithm;
    }

    PEAK_COMMON_NO_DISCARD features::SearchAlgorithm& SearchAlgorithm() const
    {
        return *m_searchAlgorithm;
    }

    PEAK_COMMON_NO_DISCARD features::FocusLimit& FocusLimit() const
    {
        return *m_focusLimit;
    }

    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return ControllerType::Focus;
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
    std::unique_ptr<features::SkipFrames> m_skipFrames{};
    std::unique_ptr<features::Hysteresis> m_hysteresis{};
    std::unique_ptr<features::WeightedRois> m_weightedRois{};
    std::unique_ptr<features::SharpnessAlgorithm> m_sharpnessAlgorithm{};
    std::unique_ptr<features::SearchAlgorithm> m_searchAlgorithm{};
    std::unique_ptr<features::FocusLimit> m_focusLimit{};
};
} // namespace detail
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
