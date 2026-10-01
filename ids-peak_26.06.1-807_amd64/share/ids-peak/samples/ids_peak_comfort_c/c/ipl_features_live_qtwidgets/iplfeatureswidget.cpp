/*!
 * \file    iplfeatures.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \brief   The IPL features class provides controls to access IPL features
 *
 * \version 1.1.0
 *
 * Copyright (C) 2022 - 2026, IDS Imaging Development Systems GmbH.
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

#include "iplfeatureswidget.h"

#include <QDebug>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>

#include "backend.h"


IplFeaturesWidget::IplFeaturesWidget(QWidget* parent)
    : QTabWidget(parent)
{
    setUsesScrollButtons(false);
    setElideMode(Qt::TextElideMode::ElideRight);
    CreateControls();

    // Create a timer and a thread that watch for changes when automatic functions are enabled
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &IplFeaturesWidget::CheckForChangedValues);

    m_isMonoCamera = backend_camera_isMono();
    if (m_isMonoCamera)
    {
        m_whiteBalanceWidget->setEnabled(false);
        m_colorCorrectionWidget->setEnabled(false);
        m_labelGainRed->setEnabled(false);
        m_sliderGainRed->setEnabled(false);
        m_editGainRed->setEnabled(false);
        m_labelGainGreen->setEnabled(false);
        m_sliderGainGreen->setEnabled(false);
        m_editGainGreen->setEnabled(false);
        m_labelGainBlue->setEnabled(false);
        m_sliderGainBlue->setEnabled(false);
        m_editGainBlue->setEnabled(false);
    }

    UpdateBrightnessAutoModes();
    UpdateBrightnessRoi();
    UpdateBrightnessOptions();
    UpdateWhiteBalanceAutoMode();
    UpdateWhiteBalanceRoi();
    UpdateGain();
    UpdateGamma();
    UpdateDigitalBlack();
    UpdateColorCorrection();
    UpdateTransformations();
    UpdateHotpixel();
    UpdateEdgeEnhancement();
}

void IplFeaturesWidget::CreateControls()
{
    // Brightness Exposure
    m_labelExposureMode = new QLabel("Auto mode", this);
    m_comboExposureMode = new QComboBox(this);
    m_comboExposureMode->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboExposureMode, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboExposureMode);

    // Brightness 
    m_labelGainModeAuto = new QLabel("Auto mode", this);
    m_comboGainModeAuto = new QComboBox(this);
    m_comboGainModeAuto->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboGainModeAuto, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboGainModeAuto);

    // Brightness analog gain
    m_labelGainModeAnalog = new QLabel("Auto mode", this);
    m_comboGainModeAnalog = new QComboBox(this);
    m_comboGainModeAnalog->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboGainModeAnalog, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboGainModeAnalog);

    // Brightness digital gain
    m_labelGainModeDigital = new QLabel("Auto mode", this);
    m_comboGainModeDigital = new QComboBox(this);
    m_comboGainModeDigital->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboGainModeDigital, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboGainModeDigital);

    // Brightness combined gain
    m_labelGainModeCombined = new QLabel("Auto mode", this);
    m_comboGainModeCombined = new QComboBox(this);
    m_comboGainModeCombined->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboGainModeCombined, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboGainModeCombined);

    // Brightness host gain
    m_labelGainModeHost = new QLabel("Auto mode", this);
    m_comboGainModeHost = new QComboBox(this);
    m_comboGainModeHost->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboGainModeHost, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboGainModeHost);

    // Brightness algorithm
    m_labelBrightnessAlgorithm = new QLabel("Algorithm", this);
    m_comboBrightnessAlgorithm = new QComboBox(this);
    m_comboBrightnessAlgorithm->addItems({"Median", "Mean"});
    connect(m_comboBrightnessAlgorithm, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboBrightnessAlgorithm);

    // Brightness ROI Mode
    m_labelBrightnessROIMode = new QLabel("ROI Mode", this);
    m_comboBrightnessRoiMode = new QComboBox(this);
    m_comboBrightnessRoiMode->addItems({ "Full Image", "Manual" });
    connect(
        m_comboBrightnessRoiMode, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboBrightnessRoiMode);

    // Brightness ROI
    m_labelBrightnessRoiOffsetX = new QLabel("Offset X", this);
    m_sliderBrightnessRoiOffsetX = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderBrightnessRoiOffsetX, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderBrightnessRoi);
    m_editBrightnessRoiOffsetX = new QLineEdit(this);
    m_editBrightnessRoiOffsetX->setFixedWidth(80);
    m_editBrightnessRoiOffsetX->setValidator(new QIntValidator(m_editBrightnessRoiOffsetX));
    connect(m_editBrightnessRoiOffsetX, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditBrightnessRoi);

    m_labelBrightnessRoiOffsetY = new QLabel("Offset Y", this);
    m_sliderBrightnessRoiOffsetY = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderBrightnessRoiOffsetY, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderBrightnessRoi);
    m_editBrightnessRoiOffsetY = new QLineEdit(this);
    m_editBrightnessRoiOffsetY->setFixedWidth(80);
    m_editBrightnessRoiOffsetY->setValidator(new QIntValidator(m_editBrightnessRoiOffsetY));
    connect(m_editBrightnessRoiOffsetY, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditBrightnessRoi);

    m_labelBrightnessRoiWidth = new QLabel("Width", this);
    m_sliderBrightnessRoiWidth = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderBrightnessRoiWidth, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderBrightnessRoi);
    m_editBrightnessRoiWidth = new QLineEdit(this);
    m_editBrightnessRoiWidth->setFixedWidth(80);
    m_editBrightnessRoiWidth->setValidator(new QIntValidator(m_editBrightnessRoiWidth));
    connect(m_editBrightnessRoiWidth, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditBrightnessRoi);

    m_labelBrightnessRoiHeight = new QLabel("Height", this);
    m_sliderBrightnessRoiHeight = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderBrightnessRoiHeight, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderBrightnessRoi);
    m_editBrightnessRoiHeight = new QLineEdit(this);
    m_editBrightnessRoiHeight->setFixedWidth(80);
    m_editBrightnessRoiHeight->setValidator(new QIntValidator(m_editBrightnessRoiHeight));
    connect(m_editBrightnessRoiHeight, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditBrightnessRoi);

    // Target
    m_labelTarget = new QLabel("Target", this);
    m_sliderTarget = new QSlider(Qt::Orientation::Horizontal, this);
    m_editTarget = new QLineEdit(this);
    m_editTarget->setFixedWidth(80);
    auto range = backend_ipl_brightness_target_range();
    m_sliderTarget->setRange(static_cast<int>(range.min), static_cast<int>(range.max));
    m_editTarget->setValidator(
        new QIntValidator(static_cast<int>(range.min), static_cast<int>(range.max), m_editTarget));
    connect(m_sliderTarget, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderTarget);
    connect(m_editTarget, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditTarget);

    // Target Percentile
    m_labelTargetPercentile = new QLabel("Percentile", this);
    m_sliderTargetPercentile = new QSlider(Qt::Orientation::Horizontal, this);
    m_editTargetPercentile = new QLineEdit(this);
    m_editTargetPercentile->setFixedWidth(80);

    auto doubleRange = backend_ipl_brightness_targetPercentile_range();
    m_targetPercentileMin = doubleRange.min;
    m_targetPercentileMax = doubleRange.max;
    m_targetPercentileInc = doubleRange.inc;

    auto steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderTargetPercentile->setRange(0, steps);
    connect(m_sliderTargetPercentile, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderTargetPercentile);
    connect(m_editTargetPercentile, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditTargetPercentile);

    // Target Tolerance
    m_labelTargetTolerance = new QLabel("Tolerance", this);
    m_sliderTargetTolerance = new QSlider(Qt::Orientation::Horizontal, this);
    m_editTargetTolerance = new QLineEdit(this);
    m_editTargetTolerance->setFixedWidth(80);
    range = backend_ipl_brightness_targetTolerance_range();
    m_sliderTargetTolerance->setRange(static_cast<int>(range.min), static_cast<int>(range.max));
    m_editTargetTolerance->setValidator(
        new QIntValidator(static_cast<int>(range.min), static_cast<int>(range.max), m_editTargetTolerance));
    connect(m_sliderTargetTolerance, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderTargetTolerance);
    connect(m_editTargetTolerance, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditTargetTolerance);


    m_labelSkipFrames = new QLabel("Skip frames", this);
    m_sliderSkipFrames = new QSlider(Qt::Orientation::Horizontal, this);
    m_editSkipFrames = new QLineEdit(this);
    m_editSkipFrames->setFixedWidth(80);
    range = backend_ipl_brightness_skipFrames_range();
    m_sliderSkipFrames->setRange(static_cast<int>(range.min), static_cast<int>(range.max));
    m_editSkipFrames->setValidator(
        new QIntValidator(static_cast<int>(range.min), static_cast<int>(range.max), m_editSkipFrames));
    connect(m_sliderSkipFrames, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderSkipFrames);
    connect(m_editSkipFrames, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditSkipFrames);

    auto autoBrighntessConfigurationGroup = new QGroupBox("Auto brightness configuration", this);
    auto autoBrighntessConfigurationLayout = new QVBoxLayout();
    autoBrighntessConfigurationGroup->setLayout(autoBrighntessConfigurationLayout);

    auto autoBrightnessConfigurationAlgorithmLayout = new QHBoxLayout(); 
    autoBrightnessConfigurationAlgorithmLayout->addWidget(m_labelBrightnessAlgorithm);
    autoBrightnessConfigurationAlgorithmLayout->addWidget(m_comboBrightnessAlgorithm);
    autoBrighntessConfigurationLayout->addLayout(autoBrightnessConfigurationAlgorithmLayout);

    auto autoBrightnessConfigurationTargetLayout = new QHBoxLayout(); 
    autoBrightnessConfigurationTargetLayout->addWidget(m_labelTarget);
    autoBrightnessConfigurationTargetLayout->addWidget(m_sliderTarget);
    autoBrightnessConfigurationTargetLayout->addWidget(m_editTarget);
    autoBrighntessConfigurationLayout->addLayout(autoBrightnessConfigurationTargetLayout);

    auto autoBrightnessConfigurationPercentileLayout = new QHBoxLayout(); 
    autoBrightnessConfigurationPercentileLayout->addWidget(m_labelTargetPercentile);
    autoBrightnessConfigurationPercentileLayout->addWidget(m_sliderTargetPercentile);
    autoBrightnessConfigurationPercentileLayout->addWidget(m_editTargetPercentile);
    autoBrighntessConfigurationLayout->addLayout(autoBrightnessConfigurationPercentileLayout);

    auto autoBrightnessConfigurationToleranceLayout = new QHBoxLayout(); 
    autoBrightnessConfigurationToleranceLayout->addWidget(m_labelTargetTolerance);
    autoBrightnessConfigurationToleranceLayout->addWidget(m_sliderTargetTolerance);
    autoBrightnessConfigurationToleranceLayout->addWidget(m_editTargetTolerance);
    autoBrighntessConfigurationLayout->addLayout(autoBrightnessConfigurationToleranceLayout);

    auto autoBrightnessConfigurationSkipFramesLayout = new QHBoxLayout(); 
    autoBrightnessConfigurationSkipFramesLayout->addWidget(m_labelSkipFrames);
    autoBrightnessConfigurationSkipFramesLayout->addWidget(m_sliderSkipFrames);
    autoBrightnessConfigurationSkipFramesLayout->addWidget(m_editSkipFrames);
    autoBrighntessConfigurationLayout->addLayout(autoBrightnessConfigurationSkipFramesLayout);

    auto exposureLimitGroup = new QGroupBox("Auto exposure", this);
    auto exposureLimitLayout = new QHBoxLayout();
    
    auto exposureModeLayout = new QHBoxLayout();
    exposureModeLayout->addWidget(m_labelExposureMode);
    exposureModeLayout->addWidget(m_comboExposureMode);

    auto exposureLayout = new QVBoxLayout();
    exposureLayout->addLayout(exposureModeLayout);
    exposureLayout->addLayout(exposureLimitLayout);

    exposureLimitGroup->setLayout(exposureLayout);

    m_spinboxExposureLimitMin = new QDoubleSpinBox(exposureLimitGroup);
    connect(m_spinboxExposureLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &IplFeaturesWidget::OnExposureLimitChange);

    m_spinboxExposureLimitMax = new QDoubleSpinBox(exposureLimitGroup);
    connect(m_spinboxExposureLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &IplFeaturesWidget::OnExposureLimitChange);

    exposureLimitLayout->addWidget(new QLabel("Minimum"));
    exposureLimitLayout->addWidget(m_spinboxExposureLimitMin);

    exposureLimitLayout->addWidget(new QLabel("Maximum"));
    exposureLimitLayout->addWidget(m_spinboxExposureLimitMax);

    auto autoGainGroup = new QGroupBox("Auto gain", this);
    auto autoGainGroupLayout = new QVBoxLayout();
    autoGainGroup->setLayout(autoGainGroupLayout);

    auto autoGainRadio = new QRadioButton("Auto select", this);
    auto manualGainRadio = new QRadioButton("Manual select", this);

    auto autoGainModeLayout = new QHBoxLayout();
    autoGainModeLayout->addWidget(autoGainRadio);
    autoGainModeLayout->addWidget(manualGainRadio);

    autoGainGroupLayout->addLayout(autoGainModeLayout);

    auto gainAutoGroup = new QGroupBox("Gain", this);

    auto gainAutoLimitLayout = new QHBoxLayout();
    auto gainAutoModeLayout = new QHBoxLayout();

    gainAutoModeLayout->addWidget(m_labelGainModeAuto);
    gainAutoModeLayout->addWidget(m_comboGainModeAuto);

    auto gainAutoLayout = new QVBoxLayout();
    gainAutoLayout->addLayout(gainAutoModeLayout);
    gainAutoLayout->addLayout(gainAutoLimitLayout);

    gainAutoGroup->setLayout(gainAutoLayout);

    m_spinboxGainAutoLimitMin = new QDoubleSpinBox(gainAutoGroup);
    connect(m_spinboxGainAutoLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &IplFeaturesWidget::OnGainAutoLimitChange);

    m_spinboxGainAutoLimitMax = new QDoubleSpinBox(gainAutoGroup);
    connect(m_spinboxGainAutoLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &IplFeaturesWidget::OnGainAutoLimitChange);

    gainAutoLimitLayout->addWidget(new QLabel("Minimum"));
    gainAutoLimitLayout->addWidget(m_spinboxGainAutoLimitMin);

    gainAutoLimitLayout->addWidget(new QLabel("Maximum"));
    gainAutoLimitLayout->addWidget(m_spinboxGainAutoLimitMax);

    auto gainAnalogGroup = new QGroupBox("Analog gain", this);
    auto gainAnalogGroupLayout = new QHBoxLayout();
    
    auto gainAnalogModeLayout = new QHBoxLayout();
    gainAnalogModeLayout->addWidget(m_labelGainModeAnalog);
    gainAnalogModeLayout->addWidget(m_comboGainModeAnalog);

    auto gainAnalogLayout = new QVBoxLayout();
    gainAnalogLayout->addLayout(gainAnalogModeLayout);
    gainAnalogLayout->addLayout(gainAnalogGroupLayout);

    gainAnalogGroup->setLayout(gainAnalogLayout);

    m_spinboxGainAnalogLimitMin = new QDoubleSpinBox(gainAnalogGroup);
    connect(m_spinboxGainAnalogLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainAnalogLimitChange);

    m_spinboxGainAnalogLimitMax = new QDoubleSpinBox(gainAnalogGroup);
    connect(m_spinboxGainAnalogLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainAnalogLimitChange);

    gainAnalogGroupLayout->addWidget(new QLabel("Minimum"));
    gainAnalogGroupLayout->addWidget(m_spinboxGainAnalogLimitMin);

    gainAnalogGroupLayout->addWidget(new QLabel("Maximum"));
    gainAnalogGroupLayout->addWidget(m_spinboxGainAnalogLimitMax);

    gainAnalogGroup->setVisible(backend_gain_analog_isWriteable());

    auto gainDigitalGroup = new QGroupBox("Digital gain", this);
    auto gainDigitalGroupLayout = new QHBoxLayout();
    
    auto gainDigitalModeLayout = new QHBoxLayout();
    gainDigitalModeLayout->addWidget(m_labelGainModeDigital);
    gainDigitalModeLayout->addWidget(m_comboGainModeDigital);

    auto gainDigitalLayout = new QVBoxLayout();
    gainDigitalLayout->addLayout(gainDigitalModeLayout);
    gainDigitalLayout->addLayout(gainDigitalGroupLayout);

    gainDigitalGroup->setLayout(gainDigitalLayout);

    m_spinboxGainDigitalLimitMin = new QDoubleSpinBox(gainDigitalGroup);
    connect(m_spinboxGainDigitalLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainDigitalLimitChange);

    m_spinboxGainDigitalLimitMax = new QDoubleSpinBox(gainDigitalGroup);
    connect(m_spinboxGainDigitalLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainDigitalLimitChange);

    gainDigitalGroupLayout->addWidget(new QLabel("Minimum"));
    gainDigitalGroupLayout->addWidget(m_spinboxGainDigitalLimitMin);

    gainDigitalGroupLayout->addWidget(new QLabel("Maximum"));
    gainDigitalGroupLayout->addWidget(m_spinboxGainDigitalLimitMax);

    gainDigitalGroup->setVisible(backend_gain_digital_isWriteable());

    auto gainCombinedGroup = new QGroupBox("Combined gain", this);
    auto gainCombinedGroupLayout = new QHBoxLayout();
    
    auto gainCombinedModeLayout = new QHBoxLayout();
    gainCombinedModeLayout->addWidget(m_labelGainModeCombined);
    gainCombinedModeLayout->addWidget(m_comboGainModeCombined);

    auto gainCombinedLayout = new QVBoxLayout();
    gainCombinedLayout->addLayout(gainCombinedModeLayout);
    gainCombinedLayout->addLayout(gainCombinedGroupLayout);

    gainCombinedGroup->setLayout(gainCombinedLayout);

    m_spinboxGainCombinedLimitMin = new QDoubleSpinBox(gainCombinedGroup);
    connect(m_spinboxGainCombinedLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainCombinedLimitChange);

    m_spinboxGainCombinedLimitMax = new QDoubleSpinBox(gainCombinedGroup);
    connect(m_spinboxGainCombinedLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainCombinedLimitChange);

    gainCombinedGroupLayout->addWidget(new QLabel("Minimum"));
    gainCombinedGroupLayout->addWidget(m_spinboxGainCombinedLimitMin);

    gainCombinedGroupLayout->addWidget(new QLabel("Maximum"));
    gainCombinedGroupLayout->addWidget(m_spinboxGainCombinedLimitMax);

    gainCombinedGroup->setVisible(backend_gain_combined_isWriteable());

    auto gainHostGroup = new QGroupBox("Software gain", this);
    auto gainHostGroupLayout = new QHBoxLayout();
    
    auto gainHostModeLayout = new QHBoxLayout();
    gainHostModeLayout->addWidget(m_labelGainModeHost);
    gainHostModeLayout->addWidget(m_comboGainModeHost);

    auto gainHostLayout = new QVBoxLayout();
    gainHostLayout->addLayout(gainHostModeLayout);
    gainHostLayout->addLayout(gainHostGroupLayout);

    gainHostGroup->setLayout(gainHostLayout);

    m_spinboxGainHostLimitMin = new QDoubleSpinBox(gainHostGroup);
    connect(m_spinboxGainHostLimitMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainHostLimitChange);

    m_spinboxGainHostLimitMax = new QDoubleSpinBox(gainHostGroup);
    connect(m_spinboxGainHostLimitMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnGainHostLimitChange);

    gainHostGroupLayout->addWidget(new QLabel("Minimum"));
    gainHostGroupLayout->addWidget(m_spinboxGainHostLimitMin);

    gainHostGroupLayout->addWidget(new QLabel("Maximum"));
    gainHostGroupLayout->addWidget(m_spinboxGainHostLimitMax);

    gainHostGroup->setVisible(backend_gain_host_isWriteable());

    const auto update_gain_mode = [gainAutoGroup, gainAnalogGroup, gainDigitalGroup, gainCombinedGroup, gainHostGroup, autoGainRadio, manualGainRadio, this](bool) {
        gainAutoGroup->setVisible(autoGainRadio->isChecked());

        gainAnalogGroup->setVisible(manualGainRadio->isChecked() && backend_gain_analog_isWriteable());
        gainDigitalGroup->setVisible(manualGainRadio->isChecked() && backend_gain_digital_isWriteable());
        gainCombinedGroup->setVisible(manualGainRadio->isChecked() && backend_gain_combined_isWriteable());
        gainHostGroup->setVisible(manualGainRadio->isChecked() && backend_gain_host_isWriteable());

        m_comboGainModeAuto->setCurrentIndex(0);
        m_comboGainModeAnalog->setCurrentIndex(0);
        m_comboGainModeDigital->setCurrentIndex(0);
        m_comboGainModeCombined->setCurrentIndex(0);
        m_comboGainModeHost->setCurrentIndex(0);
    };

    connect(manualGainRadio, &QRadioButton::toggled, this, update_gain_mode);
    connect(autoGainRadio, &QRadioButton::toggled, this, update_gain_mode);
    
    autoGainRadio->setChecked(true);

    // WhiteBalance Mode
    m_labelWhiteBalanceMode = new QLabel("Auto white balance", this);
    m_comboWhiteBalanceMode = new QComboBox(this);
    m_comboWhiteBalanceMode->addItems({ "Off", "Once", "Continuous" });
    connect(m_comboWhiteBalanceMode, &QComboBox::currentTextChanged, this, &IplFeaturesWidget::OnComboWhiteBalanceMode);

    // WhiteBalance ROI Mode
    m_labelWhiteBalanceRoiMode = new QLabel("ROI Mode", this);
    m_comboWhiteBalanceRoiMode = new QComboBox(this);
    m_comboWhiteBalanceRoiMode->addItems({ "Full Image", "Manual" });
    connect(m_comboWhiteBalanceRoiMode, &QComboBox::currentTextChanged, this,
        &IplFeaturesWidget::OnComboWhiteBalanceRoiMode);

    // WhiteBalance ROI
    m_labelWhiteBalanceRoiOffsetX = new QLabel("Offset X", this);
    m_sliderWhiteBalanceRoiOffsetX = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderWhiteBalanceRoiOffsetX, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderWhiteBalanceRoi);
    m_editWhiteBalanceRoiOffsetX = new QLineEdit(this);
    m_editWhiteBalanceRoiOffsetX->setFixedWidth(80);
    m_editWhiteBalanceRoiOffsetX->setValidator(new QIntValidator(m_editWhiteBalanceRoiOffsetX));
    connect(m_editWhiteBalanceRoiOffsetX, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditWhiteBalanceRoi);

    m_labelWhiteBalanceRoiOffsetY = new QLabel("Offset Y", this);
    m_sliderWhiteBalanceRoiOffsetY = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderWhiteBalanceRoiOffsetY, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderWhiteBalanceRoi);
    m_editWhiteBalanceRoiOffsetY = new QLineEdit(this);
    m_editWhiteBalanceRoiOffsetY->setFixedWidth(80);
    m_editWhiteBalanceRoiOffsetY->setValidator(new QIntValidator(m_editWhiteBalanceRoiOffsetY));
    connect(m_editWhiteBalanceRoiOffsetY, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditWhiteBalanceRoi);

    m_labelWhiteBalanceRoiWidth = new QLabel("Width", this);
    m_sliderWhiteBalanceRoiWidth = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderWhiteBalanceRoiWidth, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderWhiteBalanceRoi);
    m_editWhiteBalanceRoiWidth = new QLineEdit(this);
    m_editWhiteBalanceRoiWidth->setFixedWidth(80);
    m_editWhiteBalanceRoiWidth->setValidator(new QIntValidator(m_editWhiteBalanceRoiWidth));
    connect(m_editWhiteBalanceRoiWidth, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditWhiteBalanceRoi);

    m_labelWhiteBalanceRoiHeight = new QLabel("Height", this);
    m_sliderWhiteBalanceRoiHeight = new QSlider(Qt::Orientation::Horizontal, this);
    connect(m_sliderWhiteBalanceRoiHeight, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderWhiteBalanceRoi);
    m_editWhiteBalanceRoiHeight = new QLineEdit(this);
    m_editWhiteBalanceRoiHeight->setFixedWidth(80);
    m_editWhiteBalanceRoiHeight->setValidator(new QIntValidator(m_editWhiteBalanceRoiHeight));
    connect(m_editWhiteBalanceRoiHeight, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditWhiteBalanceRoi);

    // Master Gain
    m_labelGainMaster = new QLabel("Gain master", this);
    m_sliderGainMaster = new QSlider(Qt::Orientation::Horizontal, this);
    m_editGainMaster = new QLineEdit(this);
    m_editGainMaster->setFixedWidth(80);
    doubleRange = backend_ipl_gainMaster_range();
    m_gainMasterMin = doubleRange.min;
    m_gainMasterMax = doubleRange.max;
    m_gainMasterInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderGainMaster->setRange(0, steps);
    connect(m_sliderGainMaster, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderGainMaster);
    connect(m_editGainMaster, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditGainMaster);

    // Red Gain
    m_labelGainRed = new QLabel("Gain red", this);
    m_sliderGainRed = new QSlider(Qt::Orientation::Horizontal, this);
    m_editGainRed = new QLineEdit(this);
    m_editGainRed->setFixedWidth(80);
    doubleRange = backend_ipl_gainRed_range();
    m_gainRedMin = doubleRange.min;
    m_gainRedMax = doubleRange.max;
    m_gainRedInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderGainRed->setRange(0, steps);
    connect(m_sliderGainRed, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderGainRed);
    connect(m_editGainRed, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditGainRed);

    // Green Gain
    m_labelGainGreen = new QLabel("Gain green", this);
    m_sliderGainGreen = new QSlider(Qt::Orientation::Horizontal, this);
    m_editGainGreen = new QLineEdit(this);
    m_editGainGreen->setFixedWidth(80);
    doubleRange = backend_ipl_gainGreen_range();
    m_gainGreenMin = doubleRange.min;
    m_gainGreenMax = doubleRange.max;
    m_gainGreenInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderGainGreen->setRange(0, steps);
    connect(m_sliderGainGreen, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderGainGreen);
    connect(m_editGainGreen, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditGainGreen);

    // Blue Gain
    m_labelGainBlue = new QLabel("Gain blue", this);
    m_sliderGainBlue = new QSlider(Qt::Orientation::Horizontal, this);
    m_editGainBlue = new QLineEdit(this);
    m_editGainBlue->setFixedWidth(80);
    doubleRange = backend_ipl_gainBlue_range();
    m_gainBlueMin = doubleRange.min;
    m_gainBlueMax = doubleRange.max;
    m_gainBlueInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderGainBlue->setRange(0, steps);
    connect(m_sliderGainBlue, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderGainBlue);
    connect(m_editGainBlue, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditGainBlue);

    // Gamma
    m_labelGamma = new QLabel("Gamma", this);
    m_sliderGamma = new QSlider(Qt::Orientation::Horizontal, this);
    m_editGamma = new QLineEdit(this);
    m_editGamma->setFixedWidth(80);
    doubleRange = backend_ipl_gamma_range();
    m_gammaMin = doubleRange.min;
    m_gammaMax = doubleRange.max;
    m_gammaInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    m_sliderGamma->setRange(0, steps);
    connect(m_sliderGamma, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderGamma);
    connect(m_editGamma, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditGamma);

    // DigitalBlack
    m_labelDigitalBlack = new QLabel("DigitalBlack", this);
    m_sliderDigitalBlack = new QSlider(Qt::Orientation::Horizontal, this);
    m_editDigitalBlack = new QLineEdit(this);
    m_editDigitalBlack->setFixedWidth(80);
    doubleRange = backend_ipl_digital_black_range();
    m_digitalBlackMin = doubleRange.min;
    m_digitalBlackMax = doubleRange.max;
    m_sliderDigitalBlack->setRange(0, 100u);
    connect(m_sliderDigitalBlack, &QSlider::valueChanged, this, &IplFeaturesWidget::OnSliderDigitalBlack);
    connect(m_editDigitalBlack, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditDigitalBlack);

    // Color Correction
    m_checkBoxColorCorrectionEnable = new QCheckBox("Enable Color Correction", this);
    connect(
        m_checkBoxColorCorrectionEnable, &QCheckBox::stateChanged, this, &IplFeaturesWidget::OnColorCorrectionEnable);

    m_labelCcm = new QLabel(this);
    m_labelCcm->setText("CCM");

    m_editCcm00 = new QLineEdit(this);
    connect(m_editCcm00, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm01 = new QLineEdit(this);
    connect(m_editCcm01, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm02 = new QLineEdit(this);
    connect(m_editCcm02, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm10 = new QLineEdit(this);
    connect(m_editCcm10, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm11 = new QLineEdit(this);
    connect(m_editCcm11, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm12 = new QLineEdit(this);
    connect(m_editCcm12, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm20 = new QLineEdit(this);
    connect(m_editCcm20, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm21 = new QLineEdit(this);
    connect(m_editCcm21, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);
    m_editCcm22 = new QLineEdit(this);
    connect(m_editCcm22, &QLineEdit::editingFinished, this, &IplFeaturesWidget::OnEditCcm);

    m_buttonCcmDefault = new QPushButton("Camera default CCM", this);
    connect(m_buttonCcmDefault, &QPushButton::clicked, this, &IplFeaturesWidget::OnButtonCcmDefault);
    m_buttonCcmIdentity = new QPushButton("Identity CCM", this);
    connect(m_buttonCcmIdentity, &QPushButton::clicked, this, &IplFeaturesWidget::OnButtonCcmIdentity);

    // Image transformation
    m_checkBoxMirrorLeftRight = new QCheckBox("Mirror left/right", this);
    connect(m_checkBoxMirrorLeftRight, &QCheckBox::stateChanged, this, &IplFeaturesWidget::OnCheckBoxMirrorLeftRight);
    m_checkBoxMirrorUpDown = new QCheckBox("Mirror up/down", this);
    connect(m_checkBoxMirrorUpDown, &QCheckBox::stateChanged, this, &IplFeaturesWidget::OnCheckBoxMirrorUpDown);

    // Hotpixel
    m_checkBoxHotpixelEnable = new QCheckBox("Hotpixel correction enable", this);
    connect(m_checkBoxHotpixelEnable, &QCheckBox::stateChanged, this, &IplFeaturesWidget::OnHotpixelCorrectionEnable);

    m_labelHotpixelSensitivity = new QLabel(this);
    m_labelHotpixelSensitivity->setText("Sensitivity Level");
    m_spinBoxHotpixelSensitivity = new QSpinBox(this);
    m_spinBoxHotpixelSensitivity->setRange(1, 5);
    connect(m_spinBoxHotpixelSensitivity, QOverload<int>::of(&QSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnSpinBoxHotpixelSensitivity);

    m_buttonHotpixelResetList = new QPushButton("Reset hotpixel list", this);
    connect(m_buttonHotpixelResetList, &QPushButton::clicked, this, &IplFeaturesWidget::OnButtonHotpixelResetList);

    m_labelHotpixelCount = new QLabel(this);
    m_labelHotpixelCount->setText("Number of detected hotpixels");
    m_labelHotpixelCountValue = new QLabel(this);

    // Edge Enhancement
    m_checkBoxEdgeEnhancementEnable = new QCheckBox("Edge enhancement enabled", this);
    connect(m_checkBoxEdgeEnhancementEnable, &QCheckBox::toggled, this, &IplFeaturesWidget::OnEdgeEnhancementEnable);

    m_labelEdgeEnhancementFactor = new QLabel(this);
    m_labelEdgeEnhancementFactor->setText("Factor");
    m_sliderEdgeEnhancementFactor = new QSlider(Qt::Orientation::Horizontal, this);
    m_spinBoxEdgeEnhancementFactor = new QSpinBox(this);

    {
        std::uint32_t min{}, max{}, inc{};
        backend_ipl_edgeEnhancement_factor_getRange(&min, &max, &inc);
        m_sliderEdgeEnhancementFactor->setRange(static_cast<int>(min), static_cast<int>(max));
        m_sliderEdgeEnhancementFactor->setTickInterval(static_cast<int>(inc));

        m_spinBoxEdgeEnhancementFactor->setRange(static_cast<int>(min), static_cast<int>(max));
        m_spinBoxEdgeEnhancementFactor->setSingleStep(static_cast<int>(inc));
    }

    connect(m_sliderEdgeEnhancementFactor, &QSlider::valueChanged, this,
        &IplFeaturesWidget::OnEdgeEnhancementFactorChanged);

    connect(m_spinBoxEdgeEnhancementFactor, QOverload<int>::of(&QSpinBox::valueChanged), this,
        &IplFeaturesWidget::OnEdgeEnhancementFactorChanged);

    // Widgets for tabs
    m_brightnessWidget = new QWidget();
    m_brightnessWidget->setAutoFillBackground(true);
    m_brightnessLayout = new QVBoxLayout(m_brightnessWidget);

    m_whiteBalanceWidget = new QWidget();
    m_whiteBalanceWidget->setAutoFillBackground(true);
    m_whiteBalanceLayout = new QGridLayout(m_whiteBalanceWidget);

    m_gainWidget = new QWidget();
    m_gainWidget->setAutoFillBackground(true);
    m_gainLayout = new QGridLayout(m_gainWidget);

    m_colorCorrectionWidget = new QWidget();
    m_colorCorrectionWidget->setAutoFillBackground(true);
    m_colorCorrectionLayout = new QGridLayout(m_colorCorrectionWidget);

    m_transformWidget = new QWidget();
    m_transformWidget->setAutoFillBackground(true);
    m_transformLayout = new QGridLayout(m_transformWidget);

    m_hotpixelWidget = new QWidget();
    m_hotpixelWidget->setAutoFillBackground(true);
    m_hotpixelLayout = new QGridLayout(m_hotpixelWidget);

    m_edgeEnhancementWidget = new QWidget();
    m_edgeEnhancementWidget->setAutoFillBackground(true);
    m_edgeEnhancementLayout = new QGridLayout(m_edgeEnhancementWidget);

    m_brightnessLayout->addWidget(autoBrighntessConfigurationGroup);
    m_brightnessLayout->addWidget(exposureLimitGroup);
    m_brightnessLayout->addWidget(autoGainGroup);
    
    autoGainGroupLayout->addWidget(gainAutoGroup);
    autoGainGroupLayout->addWidget(gainAnalogGroup);
    autoGainGroupLayout->addWidget(gainDigitalGroup);
    autoGainGroupLayout->addWidget(gainCombinedGroup);
    autoGainGroupLayout->addWidget(gainHostGroup);

    auto roiGroup = new QGroupBox(this);
    roiGroup->setTitle("Region of interest");
    auto roiLayout = new QGridLayout;
    roiGroup->setLayout(roiLayout);

    roiLayout->addWidget(m_labelBrightnessROIMode, 0, 0);
    roiLayout->addWidget(m_comboBrightnessRoiMode, 0, 1, 1, 3);

    roiLayout->addWidget(m_labelBrightnessRoiOffsetX, 1, 0);
    roiLayout->addWidget(m_sliderBrightnessRoiOffsetX, 1, 1, 1, 2);
    roiLayout->addWidget(m_editBrightnessRoiOffsetX, 1, 3);

    roiLayout->addWidget(m_labelBrightnessRoiOffsetY, 2, 0);
    roiLayout->addWidget(m_sliderBrightnessRoiOffsetY, 2, 1, 1, 2);
    roiLayout->addWidget(m_editBrightnessRoiOffsetY, 2, 3);

    roiLayout->addWidget(m_labelBrightnessRoiWidth, 3, 0);
    roiLayout->addWidget(m_sliderBrightnessRoiWidth, 3, 1, 1, 2);
    roiLayout->addWidget(m_editBrightnessRoiWidth, 3, 3);

    roiLayout->addWidget(m_labelBrightnessRoiHeight, 4, 0);
    roiLayout->addWidget(m_sliderBrightnessRoiHeight, 4, 1, 1, 2);
    roiLayout->addWidget(m_editBrightnessRoiHeight, 4, 3);

    roiLayout->addWidget(new QWidget(), 4, 0);
 
    m_brightnessLayout->addWidget(roiGroup);
    m_brightnessLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceMode, 0, 0);
    m_whiteBalanceLayout->addWidget(m_comboWhiteBalanceMode, 0, 1, 1, 3);

    m_whiteBalanceLayout->addWidget(new QWidget(), 1, 0);
    m_whiteBalanceLayout->setRowMinimumHeight(1, 8);

    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceRoiMode, 2, 0);
    m_whiteBalanceLayout->addWidget(m_comboWhiteBalanceRoiMode, 2, 1, 1, 3);

    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceRoiOffsetX, 3, 0);
    m_whiteBalanceLayout->addWidget(m_sliderWhiteBalanceRoiOffsetX, 3, 1, 1, 2);
    m_whiteBalanceLayout->addWidget(m_editWhiteBalanceRoiOffsetX, 3, 3);
    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceRoiOffsetY, 4, 0);
    m_whiteBalanceLayout->addWidget(m_sliderWhiteBalanceRoiOffsetY, 4, 1, 1, 2);
    m_whiteBalanceLayout->addWidget(m_editWhiteBalanceRoiOffsetY, 4, 3);
    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceRoiWidth, 5, 0);
    m_whiteBalanceLayout->addWidget(m_sliderWhiteBalanceRoiWidth, 5, 1, 1, 2);
    m_whiteBalanceLayout->addWidget(m_editWhiteBalanceRoiWidth, 5, 3);
    m_whiteBalanceLayout->addWidget(m_labelWhiteBalanceRoiHeight, 6, 0);
    m_whiteBalanceLayout->addWidget(m_sliderWhiteBalanceRoiHeight, 6, 1, 1, 2);
    m_whiteBalanceLayout->addWidget(m_editWhiteBalanceRoiHeight, 6, 3);
    m_whiteBalanceLayout->addWidget(new QWidget(), 7, 0);
    m_whiteBalanceLayout->setRowStretch(7, 1);
    m_whiteBalanceLayout->setColumnStretch(1, 1);

    m_gainLayout->addWidget(m_labelGainMaster, 0, 0);
    m_gainLayout->addWidget(m_sliderGainMaster, 0, 1);
    m_gainLayout->addWidget(m_editGainMaster, 0, 2);
    m_gainLayout->addWidget(m_labelGainRed, 1, 0);
    m_gainLayout->addWidget(m_sliderGainRed, 1, 1);
    m_gainLayout->addWidget(m_editGainRed, 1, 2);
    m_gainLayout->addWidget(m_labelGainGreen, 2, 0);
    m_gainLayout->addWidget(m_sliderGainGreen, 2, 1);
    m_gainLayout->addWidget(m_editGainGreen, 2, 2);
    m_gainLayout->addWidget(m_labelGainBlue, 3, 0);
    m_gainLayout->addWidget(m_sliderGainBlue, 3, 1);
    m_gainLayout->addWidget(m_editGainBlue, 3, 2);

    m_gainLayout->addWidget(new QWidget(), 4, 0);
    m_gainLayout->setRowMinimumHeight(4, 8);

    m_gainLayout->addWidget(m_labelGamma, 5, 0);
    m_gainLayout->addWidget(m_sliderGamma, 5, 1);
    m_gainLayout->addWidget(m_editGamma, 5, 2);

    m_gainLayout->addWidget(m_labelDigitalBlack, 6, 0);
    m_gainLayout->addWidget(m_sliderDigitalBlack, 6, 1);
    m_gainLayout->addWidget(m_editDigitalBlack, 6, 2);

    m_gainLayout->addWidget(new QWidget(), 7, 0);
    m_gainLayout->setRowStretch(7, 1);
    m_gainLayout->setColumnStretch(1, 1);

    m_colorCorrectionLayout->addWidget(m_checkBoxColorCorrectionEnable, 0, 0, 1, 3);

    m_colorCorrectionLayout->addWidget(new QWidget(), 1, 0);
    m_colorCorrectionLayout->setRowMinimumHeight(1, 8);

    m_colorCorrectionLayout->addWidget(m_labelCcm, 2, 0, 1, 3);
    m_colorCorrectionLayout->addWidget(m_editCcm00, 3, 0);
    m_colorCorrectionLayout->addWidget(m_editCcm01, 3, 1);
    m_colorCorrectionLayout->addWidget(m_editCcm02, 3, 2);
    m_colorCorrectionLayout->addWidget(m_editCcm10, 4, 0);
    m_colorCorrectionLayout->addWidget(m_editCcm11, 4, 1);
    m_colorCorrectionLayout->addWidget(m_editCcm12, 4, 2);
    m_colorCorrectionLayout->addWidget(m_editCcm20, 5, 0);
    m_colorCorrectionLayout->addWidget(m_editCcm21, 5, 1);
    m_colorCorrectionLayout->addWidget(m_editCcm22, 5, 2);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setMargin(0);
    buttonLayout->addWidget(m_buttonCcmDefault);
    buttonLayout->addWidget(m_buttonCcmIdentity);
    m_colorCorrectionLayout->addLayout(buttonLayout, 6, 0, 1, 3);

    m_colorCorrectionLayout->addWidget(new QWidget(), 7, 0);
    m_colorCorrectionLayout->setRowStretch(7, 1);

    m_transformLayout->addWidget(m_checkBoxMirrorLeftRight, 0, 0);
    m_transformLayout->addWidget(m_checkBoxMirrorUpDown, 1, 0);

    m_transformLayout->addWidget(new QWidget(), 2, 0);
    m_transformLayout->setRowStretch(2, 1);

    m_hotpixelLayout->addWidget(m_checkBoxHotpixelEnable, 0, 0, 1, 2);
    m_hotpixelLayout->addWidget(m_labelHotpixelSensitivity, 1, 0);
    m_hotpixelLayout->addWidget(m_spinBoxHotpixelSensitivity, 1, 1);
    m_hotpixelLayout->addWidget(m_buttonHotpixelResetList, 2, 0, 1, 2);
    m_hotpixelLayout->addWidget(m_labelHotpixelCount, 3, 0);
    m_hotpixelLayout->addWidget(m_labelHotpixelCountValue, 3, 1);

    m_hotpixelLayout->addWidget(new QWidget(), 4, 0);
    m_hotpixelLayout->setRowStretch(4, 1);
    m_hotpixelLayout->setColumnStretch(1, 1);

    m_edgeEnhancementLayout->addWidget(m_checkBoxEdgeEnhancementEnable, 0, 0, 1, 3);
    m_edgeEnhancementLayout->addWidget(m_labelEdgeEnhancementFactor, 1, 0);
    m_edgeEnhancementLayout->addWidget(m_sliderEdgeEnhancementFactor, 1, 1);
    m_edgeEnhancementLayout->addWidget(m_spinBoxEdgeEnhancementFactor, 1, 2);
    m_edgeEnhancementLayout->setRowStretch(4, 1);
    m_edgeEnhancementLayout->setColumnStretch(1, 1);

    addTab(m_brightnessWidget, "AutoBrightness");
    addTab(m_whiteBalanceWidget, "AutoWhiteBalance");
    addTab(m_gainWidget, "Gain");
    addTab(m_colorCorrectionWidget, "ColorCorrection");
    addTab(m_transformWidget, "Transform");
    addTab(m_hotpixelWidget, "Hotpixel");
    addTab(m_edgeEnhancementWidget, "Edge Enhancement");
}

void IplFeaturesWidget::UpdateBrightnessAutoModes()
{
    auto exposureMode = backend_ipl_brightness_exposureMode_get();
    if (m_comboExposureMode->currentIndex() != exposureMode)
    {
        m_comboExposureMode->setCurrentIndex(exposureMode);
    }

    auto gainModeAuto = backend_ipl_brightness_gainMode_get();
    if (m_comboGainModeAuto->currentIndex() != gainModeAuto)
    {
        m_comboGainModeAuto->setCurrentIndex(gainModeAuto);
    }

    auto gainModeAnalog = backend_ipl_brightness_gainAnalogMode_get();
    if (m_comboGainModeAnalog->currentIndex() != gainModeAnalog)
    {
        m_comboGainModeAnalog->setCurrentIndex(gainModeAnalog);
    }

    auto gainModeDigital = backend_ipl_brightness_gainDigitalMode_get();
    if (m_comboGainModeDigital->currentIndex() != gainModeDigital)
    {
        m_comboGainModeDigital->setCurrentIndex(gainModeDigital);
    }

    auto brightnessAlgorithm = backend_ipl_brightness_brightnessAlgorithm_get();
    if (m_comboBrightnessAlgorithm->currentIndex() != brightnessAlgorithm)
    {
        m_comboBrightnessAlgorithm->setCurrentIndex(brightnessAlgorithm);
    }
}

void IplFeaturesWidget::UpdateBrightnessRoi()
{
    auto roiMode = backend_ipl_brightness_roiMode_get();
    if (m_comboBrightnessRoiMode->currentIndex() != roiMode)
    {
        m_comboBrightnessRoiMode->setCurrentIndex(roiMode);
    }

    auto enableManualRoi = (roiMode == 1);
    m_sliderBrightnessRoiOffsetX->setEnabled(enableManualRoi);
    m_editBrightnessRoiOffsetX->setEnabled(enableManualRoi);
    m_sliderBrightnessRoiOffsetY->setEnabled(enableManualRoi);
    m_editBrightnessRoiOffsetY->setEnabled(enableManualRoi);
    m_sliderBrightnessRoiWidth->setEnabled(enableManualRoi);
    m_editBrightnessRoiWidth->setEnabled(enableManualRoi);
    m_sliderBrightnessRoiHeight->setEnabled(enableManualRoi);
    m_editBrightnessRoiHeight->setEnabled(enableManualRoi);

    auto rangeX = backend_ipl_brightness_roiOffsetX_range();
    if (rangeX.min == 0 && rangeX.max == 0 && rangeX.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeY = backend_ipl_brightness_roiOffsetY_range();
    if (rangeY.min == 0 && rangeY.max == 0 && rangeY.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeW = backend_ipl_brightness_roiWidth_range();
    if (rangeW.min == 0 && rangeW.max == 0 && rangeW.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeH = backend_ipl_brightness_roiHeight_range();
    if (rangeH.min == 0 && rangeH.max == 0 && rangeH.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto roi = backend_ipl_brightness_roi_get();
    if (roi.offset.x == 0 && roi.offset.y == 0 && roi.size.width == 0 && roi.size.height == 0)
    {
        emit error("Unable to read brightness ROI.");
        return;
    }

    QRect display_rect(roi.offset.x, roi.offset.y, roi.size.width, roi.size.height);
    if (backend_ipl_mirrorLeftRight_isEnabled())
    {
        auto camera_roi = backend_roi_get();
        display_rect.moveLeft(camera_roi.size.width - (roi.offset.x + roi.size.width));
    }

    if (backend_ipl_mirrorUpDown_isEnabled())
    {
        auto camera_roi = backend_roi_get();
        display_rect.moveBottom(camera_roi.size.height - (roi.offset.y));
    }

    emit updateDisplayBrightnessRoi( enableManualRoi ? display_rect : QRect{});

    m_sliderBrightnessRoiOffsetX->blockSignals(true);
    m_editBrightnessRoiOffsetX->blockSignals(true);
    m_sliderBrightnessRoiOffsetY->blockSignals(true);
    m_editBrightnessRoiOffsetY->blockSignals(true);
    m_sliderBrightnessRoiWidth->blockSignals(true);
    m_editBrightnessRoiWidth->blockSignals(true);
    m_sliderBrightnessRoiHeight->blockSignals(true);
    m_editBrightnessRoiHeight->blockSignals(true);

    m_sliderBrightnessRoiOffsetX->setRange(static_cast<int>(rangeX.min), static_cast<int>(rangeX.max));
    m_sliderBrightnessRoiOffsetX->setSingleStep(static_cast<int>(rangeX.inc));
    m_sliderBrightnessRoiOffsetX->setValue(static_cast<int>(roi.offset.x));
    m_editBrightnessRoiOffsetX->setValidator(
        new QIntValidator(static_cast<int>(rangeX.min), static_cast<int>(rangeX.max), m_editBrightnessRoiOffsetX));
    m_editBrightnessRoiOffsetX->setText(QString::number(roi.offset.x));

    m_sliderBrightnessRoiOffsetY->setRange(static_cast<int>(rangeY.min), static_cast<int>(rangeY.max));
    m_sliderBrightnessRoiOffsetY->setSingleStep(static_cast<int>(rangeY.inc));
    m_sliderBrightnessRoiOffsetY->setValue(static_cast<int>(roi.offset.y));
    m_editBrightnessRoiOffsetY->setValidator(
        new QIntValidator(static_cast<int>(rangeY.min), static_cast<int>(rangeY.max), m_editBrightnessRoiOffsetY));
    m_editBrightnessRoiOffsetY->setText(QString::number(roi.offset.y));

    m_sliderBrightnessRoiWidth->setRange(static_cast<int>(rangeW.min), static_cast<int>(rangeW.max));
    m_sliderBrightnessRoiWidth->setSingleStep(static_cast<int>(rangeW.inc));
    m_sliderBrightnessRoiWidth->setValue(static_cast<int>(roi.size.width));
    m_editBrightnessRoiWidth->setValidator(
        new QIntValidator(static_cast<int>(rangeW.min), static_cast<int>(rangeW.max), m_editBrightnessRoiWidth));
    m_editBrightnessRoiWidth->setText(QString::number(roi.size.width));

    m_sliderBrightnessRoiHeight->setRange(static_cast<int>(rangeH.min), static_cast<int>(rangeH.max));
    m_sliderBrightnessRoiHeight->setSingleStep(static_cast<int>(rangeH.inc));
    m_sliderBrightnessRoiHeight->setValue(static_cast<int>(roi.size.height));
    m_editBrightnessRoiHeight->setValidator(
        new QIntValidator(static_cast<int>(rangeH.min), static_cast<int>(rangeH.max), m_editBrightnessRoiHeight));
    m_editBrightnessRoiHeight->setText(QString::number(roi.size.height));

    m_sliderBrightnessRoiOffsetX->blockSignals(false);
    m_editBrightnessRoiOffsetX->blockSignals(false);
    m_sliderBrightnessRoiOffsetY->blockSignals(false);
    m_editBrightnessRoiOffsetY->blockSignals(false);
    m_sliderBrightnessRoiWidth->blockSignals(false);
    m_editBrightnessRoiWidth->blockSignals(false);
    m_sliderBrightnessRoiHeight->blockSignals(false);
    m_editBrightnessRoiHeight->blockSignals(false);
}

void IplFeaturesWidget::UpdateBrightnessOptions()
{
    auto targetPercentile = backend_ipl_brightness_targetPercentile_get();
    auto step = static_cast<int>((targetPercentile - m_targetPercentileMin) / m_targetPercentileInc);

    auto target = backend_ipl_brightness_target_get();

    auto targetTolerance = backend_ipl_brightness_targetTolerance_get();

    auto exposureRange = backend_exposureTime_range();
    auto exposureLimit = backend_ipl_brightness_exposure_limit_get();

    auto gainAutoLimitRange = backend_ipl_brightness_gain_limit_range_get();
    auto gainAutoLimit = backend_ipl_brightness_gain_limit_get();

    auto gainAnalogLimitRange = backend_ipl_brightness_gain_analog_limit_range_get();
    auto gainAnalogLimit = backend_ipl_brightness_gain_analog_limit_get();

    auto gainDigitalLimitRange = backend_ipl_brightness_gain_digital_limit_range_get();
    auto gainDigitalLimit = backend_ipl_brightness_gain_digital_limit_get();

    auto gainCombinedLimitRange = backend_ipl_brightness_gain_combined_limit_range_get();
    auto gainCombinedLimit = backend_ipl_brightness_gain_combined_limit_get();

    auto gainHostLimitRange = backend_ipl_brightness_gain_host_limit_range_get();
    auto gainHostLimit = backend_ipl_brightness_gain_host_limit_get();

    auto skipFrames = backend_ipl_brightness_skipFrames_get();

    m_sliderTargetPercentile->blockSignals(true);
    m_editTargetPercentile->blockSignals(true);
    m_sliderTarget->blockSignals(true);
    m_editTarget->blockSignals(true);
    m_sliderTargetTolerance->blockSignals(true);
    m_editTargetTolerance->blockSignals(true);
    m_sliderSkipFrames->blockSignals(true);
    m_editSkipFrames->blockSignals(true);
    m_spinboxExposureLimitMin->blockSignals(true);
    m_spinboxExposureLimitMax->blockSignals(true);
    m_spinboxGainAutoLimitMin->blockSignals(true);
    m_spinboxGainAutoLimitMax->blockSignals(true);
    m_spinboxGainAnalogLimitMin->blockSignals(true);
    m_spinboxGainAnalogLimitMax->blockSignals(true);
    m_spinboxGainDigitalLimitMin->blockSignals(true);
    m_spinboxGainDigitalLimitMax->blockSignals(true);
    m_spinboxGainCombinedLimitMin->blockSignals(true);
    m_spinboxGainCombinedLimitMax->blockSignals(true);
    m_spinboxGainHostLimitMin->blockSignals(true);
    m_spinboxGainHostLimitMax->blockSignals(true);

    m_sliderTargetPercentile->setValue(step);
    m_editTargetPercentile->setText(QString::number(targetPercentile, 'f', 2));

    m_sliderTarget->setValue(static_cast<int>(target));
    m_editTarget->setText(QString::number(target));

    m_sliderTargetTolerance->setValue(static_cast<int>(targetTolerance));
    m_editTargetTolerance->setText(QString::number(targetTolerance));

    m_sliderSkipFrames->setValue(static_cast<int>(skipFrames));
    m_editSkipFrames->setText(QString::number(skipFrames));

    m_spinboxExposureLimitMin->setRange(exposureRange.min, exposureRange.max);
    m_spinboxExposureLimitMin->setSingleStep(1000);
    m_spinboxExposureLimitMin->setValue(exposureLimit.min);

    m_spinboxExposureLimitMax->setRange(exposureRange.min, exposureRange.max);
    m_spinboxExposureLimitMax->setSingleStep(1000);
    m_spinboxExposureLimitMax->setValue(exposureLimit.max);

    m_spinboxGainAutoLimitMin->setRange(gainAutoLimitRange.min, gainAutoLimitRange.max);
    m_spinboxGainAutoLimitMin->setValue(gainAutoLimit.min);
    m_spinboxGainAutoLimitMax->setRange(gainAutoLimitRange.min, gainAutoLimitRange.max);
    m_spinboxGainAutoLimitMax->setValue(gainAutoLimit.max);

    m_spinboxGainAnalogLimitMin->setRange(gainAnalogLimitRange.min, gainAnalogLimitRange.max);
    m_spinboxGainAnalogLimitMin->setValue(gainAnalogLimit.min);
    m_spinboxGainAnalogLimitMax->setRange(gainAnalogLimitRange.min, gainAnalogLimitRange.max);
    m_spinboxGainAnalogLimitMax->setValue(gainAnalogLimit.max);

    m_spinboxGainDigitalLimitMin->setRange(gainDigitalLimitRange.min, gainDigitalLimitRange.max);
    m_spinboxGainDigitalLimitMin->setValue(gainDigitalLimit.min);
    m_spinboxGainDigitalLimitMax->setRange(gainDigitalLimitRange.min, gainDigitalLimitRange.max);
    m_spinboxGainDigitalLimitMax->setValue(gainDigitalLimit.max);

    m_spinboxGainCombinedLimitMin->setRange(gainCombinedLimitRange.min, gainCombinedLimitRange.max);
    m_spinboxGainCombinedLimitMin->setValue(gainCombinedLimit.min);
    m_spinboxGainCombinedLimitMax->setRange(gainCombinedLimitRange.min, gainCombinedLimitRange.max);
    m_spinboxGainCombinedLimitMax->setValue(gainCombinedLimit.max);

    m_spinboxGainHostLimitMin->setRange(gainHostLimitRange.min, gainHostLimitRange.max);
    m_spinboxGainHostLimitMin->setValue(gainHostLimit.min);
    m_spinboxGainHostLimitMax->setRange(gainHostLimitRange.min, gainHostLimitRange.max);
    m_spinboxGainHostLimitMax->setValue(gainHostLimit.max);

    m_sliderTargetPercentile->blockSignals(false);
    m_editTargetPercentile->blockSignals(false);
    m_sliderTarget->blockSignals(false);
    m_editTarget->blockSignals(false);
    m_sliderTargetTolerance->blockSignals(false);
    m_editTargetTolerance->blockSignals(false);
    m_sliderSkipFrames->blockSignals(false);
    m_editSkipFrames->blockSignals(false);
    m_spinboxExposureLimitMin->blockSignals(false);
    m_spinboxExposureLimitMax->blockSignals(false);
    m_spinboxGainAutoLimitMin->blockSignals(false);
    m_spinboxGainAutoLimitMax->blockSignals(false);
    m_spinboxGainAnalogLimitMin->blockSignals(false);
    m_spinboxGainAnalogLimitMax->blockSignals(false);
    m_spinboxGainDigitalLimitMin->blockSignals(false);
    m_spinboxGainDigitalLimitMax->blockSignals(false);
    m_spinboxGainCombinedLimitMin->blockSignals(false);
    m_spinboxGainCombinedLimitMax->blockSignals(false);
    m_spinboxGainHostLimitMin->blockSignals(false);
    m_spinboxGainHostLimitMax->blockSignals(false);
}


void IplFeaturesWidget::UpdateWhiteBalanceAutoMode()
{
    if (m_isMonoCamera)
        return;

    auto whiteBalanceMode = backend_ipl_whiteBalance_mode_get();
    if (m_comboExposureMode->currentIndex() != whiteBalanceMode)
    {
        m_comboExposureMode->setCurrentIndex(whiteBalanceMode);
    }
}

void IplFeaturesWidget::UpdateWhiteBalanceRoi()
{
    if (m_isMonoCamera)
        return;

    auto roiMode = backend_ipl_whiteBalance_roiMode_get();
    if (m_comboWhiteBalanceRoiMode->currentIndex() != roiMode)
    {
        m_comboWhiteBalanceRoiMode->setCurrentIndex(roiMode);
    }

    auto enableManualRoi = (roiMode == 1);
    m_sliderWhiteBalanceRoiOffsetX->setEnabled(enableManualRoi);
    m_editWhiteBalanceRoiOffsetX->setEnabled(enableManualRoi);
    m_sliderWhiteBalanceRoiOffsetY->setEnabled(enableManualRoi);
    m_editWhiteBalanceRoiOffsetY->setEnabled(enableManualRoi);
    m_sliderWhiteBalanceRoiWidth->setEnabled(enableManualRoi);
    m_editWhiteBalanceRoiWidth->setEnabled(enableManualRoi);
    m_sliderWhiteBalanceRoiHeight->setEnabled(enableManualRoi);
    m_editWhiteBalanceRoiHeight->setEnabled(enableManualRoi);

    auto rangeX = backend_ipl_whiteBalance_roiOffsetX_range();
    if (rangeX.min == 0 && rangeX.max == 0 && rangeX.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeY = backend_ipl_whiteBalance_roiOffsetY_range();
    if (rangeY.min == 0 && rangeY.max == 0 && rangeY.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeW = backend_ipl_whiteBalance_roiWidth_range();
    if (rangeW.min == 0 && rangeW.max == 0 && rangeW.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeH = backend_ipl_whiteBalance_roiHeight_range();
    if (rangeH.min == 0 && rangeH.max == 0 && rangeH.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto roi = backend_ipl_whiteBalance_roi_get();
    if (roi.offset.x == 0 && roi.offset.y == 0 && roi.size.width == 0 && roi.size.height == 0)
    {
        emit error("Unable to read white balance ROI.");
        return;
    }

    QRect display_rect(roi.offset.x, roi.offset.y, roi.size.width, roi.size.height);
    if (backend_ipl_mirrorLeftRight_isEnabled())
    {
        auto camera_roi = backend_roi_get();
        display_rect.moveLeft(camera_roi.size.width - (roi.offset.x + roi.size.width));
    }

    if (backend_ipl_mirrorUpDown_isEnabled())
    {
        auto camera_roi = backend_roi_get();
        display_rect.moveBottom(camera_roi.size.height - (roi.offset.y));
    }

    emit updateDisplayWhitebalanceRoi( enableManualRoi ? display_rect : QRect{});

    m_sliderWhiteBalanceRoiOffsetX->blockSignals(true);
    m_editWhiteBalanceRoiOffsetX->blockSignals(true);
    m_sliderWhiteBalanceRoiOffsetY->blockSignals(true);
    m_editWhiteBalanceRoiOffsetY->blockSignals(true);
    m_sliderWhiteBalanceRoiWidth->blockSignals(true);
    m_editWhiteBalanceRoiWidth->blockSignals(true);
    m_sliderWhiteBalanceRoiHeight->blockSignals(true);
    m_editWhiteBalanceRoiHeight->blockSignals(true);

    m_sliderWhiteBalanceRoiOffsetX->setRange(static_cast<int>(rangeX.min), static_cast<int>(rangeX.max));
    m_sliderWhiteBalanceRoiOffsetX->setSingleStep(static_cast<int>(rangeX.inc));
    m_sliderWhiteBalanceRoiOffsetX->setValue(static_cast<int>(roi.offset.x));
    m_editWhiteBalanceRoiOffsetX->setValidator(
        new QIntValidator(static_cast<int>(rangeX.min), static_cast<int>(rangeX.max), m_editWhiteBalanceRoiOffsetX));
    m_editWhiteBalanceRoiOffsetX->setText(QString::number(roi.offset.x));

    m_sliderWhiteBalanceRoiOffsetY->setRange(static_cast<int>(rangeY.min), static_cast<int>(rangeY.max));
    m_sliderWhiteBalanceRoiOffsetY->setSingleStep(static_cast<int>(rangeY.inc));
    m_sliderWhiteBalanceRoiOffsetY->setValue(static_cast<int>(roi.offset.y));
    m_editWhiteBalanceRoiOffsetY->setValidator(
        new QIntValidator(static_cast<int>(rangeY.min), static_cast<int>(rangeY.max), m_editWhiteBalanceRoiOffsetY));
    m_editWhiteBalanceRoiOffsetY->setText(QString::number(roi.offset.y));

    m_sliderWhiteBalanceRoiWidth->setRange(static_cast<int>(rangeW.min), static_cast<int>(rangeW.max));
    m_sliderWhiteBalanceRoiWidth->setSingleStep(static_cast<int>(rangeW.inc));
    m_sliderWhiteBalanceRoiWidth->setValue(static_cast<int>(roi.size.width));
    m_editWhiteBalanceRoiWidth->setValidator(
        new QIntValidator(static_cast<int>(rangeW.min), static_cast<int>(rangeW.max), m_editWhiteBalanceRoiWidth));
    m_editWhiteBalanceRoiWidth->setText(QString::number(roi.size.width));

    m_sliderWhiteBalanceRoiHeight->setRange(static_cast<int>(rangeH.min), static_cast<int>(rangeH.max));
    m_sliderWhiteBalanceRoiHeight->setSingleStep(static_cast<int>(rangeH.inc));
    m_sliderWhiteBalanceRoiHeight->setValue(static_cast<int>(roi.size.height));
    m_editWhiteBalanceRoiHeight->setValidator(
        new QIntValidator(static_cast<int>(rangeH.min), static_cast<int>(rangeH.max), m_editWhiteBalanceRoiHeight));
    m_editWhiteBalanceRoiHeight->setText(QString::number(roi.size.height));

    m_sliderWhiteBalanceRoiOffsetX->blockSignals(false);
    m_editWhiteBalanceRoiOffsetX->blockSignals(false);
    m_sliderWhiteBalanceRoiOffsetY->blockSignals(false);
    m_editWhiteBalanceRoiOffsetY->blockSignals(false);
    m_sliderWhiteBalanceRoiWidth->blockSignals(false);
    m_editWhiteBalanceRoiWidth->blockSignals(false);
    m_sliderWhiteBalanceRoiHeight->blockSignals(false);
    m_editWhiteBalanceRoiHeight->blockSignals(false);
}

void IplFeaturesWidget::UpdateGain()
{
    double gainMaster = backend_ipl_gainMaster_get();
    auto stepMaster = static_cast<int>((gainMaster - m_gainMasterMin) / m_gainMasterInc);

    m_sliderGainMaster->blockSignals(true);
    m_editGainMaster->blockSignals(true);
    m_sliderGainMaster->setValue(stepMaster);
    m_editGainMaster->setText(QString::number(gainMaster, 'f', 2));

    m_sliderGainMaster->blockSignals(false);
    m_editGainMaster->blockSignals(false);

    if (!m_isMonoCamera)
    {
        double gainRed = backend_ipl_gainRed_get();
        double gainGreen = backend_ipl_gainGreen_get();
        double gainBlue = backend_ipl_gainBlue_get();

        auto stepRed = static_cast<int>((gainRed - m_gainRedMin) / m_gainRedInc);
        auto stepGreen = static_cast<int>((gainGreen - m_gainGreenMin) / m_gainGreenInc);
        auto stepBlue = static_cast<int>((gainBlue - m_gainBlueMin) / m_gainBlueInc);

        m_sliderGainRed->blockSignals(true);
        m_editGainRed->blockSignals(true);
        m_sliderGainGreen->blockSignals(true);
        m_editGainGreen->blockSignals(true);
        m_sliderGainBlue->blockSignals(true);
        m_editGainBlue->blockSignals(true);

        m_sliderGainRed->setValue(stepRed);
        m_editGainRed->setText(QString::number(gainRed, 'f', 2));

        m_sliderGainGreen->setValue(stepGreen);
        m_editGainGreen->setText(QString::number(gainGreen, 'f', 2));

        m_sliderGainBlue->setValue(stepBlue);
        m_editGainBlue->setText(QString::number(gainBlue, 'f', 2));

        m_sliderGainRed->blockSignals(false);
        m_editGainRed->blockSignals(false);
        m_sliderGainGreen->blockSignals(false);
        m_editGainGreen->blockSignals(false);
        m_sliderGainBlue->blockSignals(false);
        m_editGainBlue->blockSignals(false);
    }
}

void IplFeaturesWidget::UpdateGamma()
{
    double gamma = backend_ipl_gamma_get();
    auto step = static_cast<int>((gamma - m_gammaMin) / m_gammaInc);

    m_sliderGamma->blockSignals(true);
    m_editGamma->blockSignals(true);

    m_sliderGamma->setValue(step);
    m_editGamma->setText(QString::number(gamma, 'f', 2));

    m_sliderGamma->blockSignals(false);
    m_editGamma->blockSignals(false);
}

void IplFeaturesWidget::UpdateDigitalBlack()
{
    const double digitalBlack = backend_ipl_digital_black_get();

    m_sliderDigitalBlack->blockSignals(true);
    m_editDigitalBlack->blockSignals(true);

    m_sliderDigitalBlack->setValue(static_cast<int>(digitalBlack * 100.0));
    m_editDigitalBlack->setText(QString::number(digitalBlack, 'f', 2));

    m_sliderDigitalBlack->blockSignals(false);
    m_editDigitalBlack->blockSignals(false);
}

void IplFeaturesWidget::UpdateColorCorrection()
{
    if (m_isMonoCamera)
        return;

    auto enabled = backend_ipl_colorCorrection_isEnabled();
    m_checkBoxColorCorrectionEnable->blockSignals(true);
    if (enabled)
    {
        m_checkBoxColorCorrectionEnable->setCheckState(Qt::Checked);
    }
    else
    {
        m_checkBoxColorCorrectionEnable->setCheckState(Qt::Unchecked);
    }
    m_checkBoxColorCorrectionEnable->blockSignals(false);

    auto ccm = backend_ipl_colorCorrectionMatrix_get();

    m_editCcm00->setText(QString::number(ccm.elementArray[0][0], 'f', 2));
    m_editCcm01->setText(QString::number(ccm.elementArray[0][1], 'f', 2));
    m_editCcm02->setText(QString::number(ccm.elementArray[0][2], 'f', 2));
    m_editCcm10->setText(QString::number(ccm.elementArray[1][0], 'f', 2));
    m_editCcm11->setText(QString::number(ccm.elementArray[1][1], 'f', 2));
    m_editCcm12->setText(QString::number(ccm.elementArray[1][2], 'f', 2));
    m_editCcm20->setText(QString::number(ccm.elementArray[2][0], 'f', 2));
    m_editCcm21->setText(QString::number(ccm.elementArray[2][1], 'f', 2));
    m_editCcm22->setText(QString::number(ccm.elementArray[2][2], 'f', 2));
}


void IplFeaturesWidget::UpdateTransformations()
{
    auto enabled = backend_ipl_mirrorLeftRight_isEnabled();
    m_checkBoxMirrorLeftRight->blockSignals(true);
    if (enabled)
    {
        m_checkBoxMirrorLeftRight->setCheckState(Qt::Checked);
    }
    else
    {
        m_checkBoxMirrorLeftRight->setCheckState(Qt::Unchecked);
    }
    m_checkBoxMirrorLeftRight->blockSignals(false);

    enabled = backend_ipl_mirrorUpDown_isEnabled();
    m_checkBoxMirrorUpDown->blockSignals(true);
    if (enabled)
    {
        m_checkBoxMirrorUpDown->setCheckState(Qt::Checked);
    }
    else
    {
        m_checkBoxMirrorUpDown->setCheckState(Qt::Unchecked);
    }
    m_checkBoxMirrorUpDown->blockSignals(false);

    UpdateBrightnessRoi();
    UpdateWhiteBalanceRoi();
}

void IplFeaturesWidget::UpdateHotpixel()
{
    auto enabled = backend_ipl_hotpixelCorrection_isEnabled();
    m_checkBoxHotpixelEnable->blockSignals(true);
    if (enabled)
    {
        m_checkBoxHotpixelEnable->setCheckState(Qt::Checked);
    }
    else
    {
        m_checkBoxHotpixelEnable->setCheckState(Qt::Unchecked);
    }
    m_checkBoxHotpixelEnable->blockSignals(false);

    int value = backend_ipl_hotpixelCorrection_sensitivity_get();
    m_spinBoxHotpixelSensitivity->blockSignals(true);
    m_spinBoxHotpixelSensitivity->setValue(value);
    m_spinBoxHotpixelSensitivity->blockSignals(false);
}

void IplFeaturesWidget::UpdateEdgeEnhancement()
{
    auto enabled = backend_ipl_edgeEnhancement_isEnabled();
    m_checkBoxEdgeEnhancementEnable->blockSignals(true);
    if (enabled)
    {
        m_checkBoxEdgeEnhancementEnable->setCheckState(Qt::Checked);
    }
    else
    {
        m_checkBoxEdgeEnhancementEnable->setCheckState(Qt::Unchecked);
    }
    m_checkBoxEdgeEnhancementEnable->blockSignals(false);

    int value = backend_ipl_edgeEnhancement_factor_get();
    m_sliderEdgeEnhancementFactor->blockSignals(true);
    m_sliderEdgeEnhancementFactor->setValue(value);
    m_sliderEdgeEnhancementFactor->blockSignals(false);
}


void IplFeaturesWidget::OnComboExposureMode(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_exposureMode_set(0);
        emit exposureAutoModeChanged(false);
        // change range back to regular range
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_exposureMode_set(1);
        emit exposureAutoModeChanged(true);

        // change range to afl range max

        // start a timer that checks if the exposure auto algorithm finished
        // and sends a signal to update the exposure time regularly
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_exposureMode_set(2);
        emit exposureAutoModeChanged(true);

        // start a timer that sends a signal to update the exposure time regularly
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void IplFeaturesWidget::OnComboGainModeAnalog(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainAnalogMode_set(0);
        emit gainAutoModeAnalogChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainAnalogMode_set(1);
        emit gainAutoModeAnalogChanged(true);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainAnalogMode_set(2);
        emit gainAutoModeAnalogChanged(true);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void IplFeaturesWidget::OnComboGainModeAuto(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainMode_set(0);
        emit gainAutoModeAutoChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainMode_set(1);
        emit gainAutoModeAutoChanged(true);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainMode_set(2);
        emit gainAutoModeAutoChanged(true);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void IplFeaturesWidget::OnComboGainModeDigital(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainDigitalMode_set(0);
        emit gainDigitalAutoModeChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainDigitalMode_set(1);
        emit gainDigitalAutoModeChanged(true);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainDigitalMode_set(2);
        emit gainDigitalAutoModeChanged(true);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void IplFeaturesWidget::OnComboGainModeCombined(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainCombinedMode_set(0);
        emit gainCombinedAutoModeChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainCombinedMode_set(1);
        emit gainCombinedAutoModeChanged(true);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainCombinedMode_set(2);
        emit gainCombinedAutoModeChanged(true);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}


void IplFeaturesWidget::OnComboGainModeHost(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainHostMode_set(0);
        emit gainHostAutoModeChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainHostMode_set(1);
        emit gainHostAutoModeChanged(true);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainHostMode_set(2);
        emit gainHostAutoModeChanged(true);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}


void IplFeaturesWidget::OnComboBrightnessAlgorithm(const QString& text)
{
    if(text == "Median")
    {
        backend_ipl_brightness_brightnessAlgorithm_set(0);
    }
    else if(text == "Mean")
    {
        backend_ipl_brightness_brightnessAlgorithm_set(1);
    }

    m_labelTargetPercentile->setVisible(text == "Median");
    m_editTargetPercentile->setVisible(text == "Median");
    m_sliderTargetPercentile->setVisible(text == "Median");
}

void IplFeaturesWidget::OnComboBrightnessRoiMode(const QString& text)
{
    if (text == "Full Image")
    {
        backend_ipl_brightness_roiMode_set(0);
    }
    else if (text == "Manual")
    {
        backend_ipl_brightness_roiMode_set(1);
    }
    UpdateBrightnessRoi();
}

void IplFeaturesWidget::OnSliderBrightnessRoi(int value)
{
    auto roi = backend_ipl_brightness_roi_get();
    if (sender() == m_sliderBrightnessRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == m_sliderBrightnessRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == m_sliderBrightnessRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == m_sliderBrightnessRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_brightness_roi_set(roi);
    UpdateBrightnessRoi();
}

void IplFeaturesWidget::OnEditBrightnessRoi()
{
    auto line_edit = dynamic_cast<QLineEdit*>(sender());
    if (!line_edit)
    {
        return;
    }

    QString text = line_edit->text();
    auto roi = backend_ipl_brightness_roi_get();
    auto value = text.toInt();
    if (sender() == m_editBrightnessRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == m_editBrightnessRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == m_editBrightnessRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == m_editBrightnessRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_brightness_roi_set(roi);
    UpdateBrightnessRoi();
}

void IplFeaturesWidget::OnSliderTarget(int value)
{
    backend_ipl_brightness_target_set(value);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnEditTarget()
{
    QString text = m_editTarget->text();
    auto value = text.toInt();
    backend_ipl_brightness_target_set(value);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnSliderTargetPercentile(int value)
{
    double val = static_cast<double>(value) * m_targetPercentileInc + m_targetPercentileMin;
    if (val > m_targetPercentileMax)
    {
        val = m_targetPercentileMax;
    }
    backend_ipl_brightness_targetPercentile_set(val);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnEditTargetPercentile()
{
    auto value = m_editTargetPercentile->text().toDouble();
    backend_ipl_brightness_targetPercentile_set(value);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnSliderTargetTolerance(int value)
{
    backend_ipl_brightness_targetTolerance_set(value);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnEditTargetTolerance()
{
    QString text = m_editTargetTolerance->text();
    auto value = text.toInt();
    backend_ipl_brightness_targetTolerance_set(value);
    UpdateBrightnessRoi();
}

void IplFeaturesWidget::OnSliderSkipFrames(int value)
{
    backend_ipl_brightness_skipFrames_set(value);
    UpdateBrightnessOptions();
}

void IplFeaturesWidget::OnEditSkipFrames()
{
    QString text = m_editSkipFrames->text();
    auto value = text.toInt();
    backend_ipl_brightness_skipFrames_set(value);
    UpdateBrightnessRoi();
}

void IplFeaturesWidget::OnExposureLimitChange(double)
{
    m_spinboxExposureLimitMax->setMinimum(m_spinboxExposureLimitMin->value());
    backend_ipl_brightness_exposure_limit_set(m_spinboxExposureLimitMin->value(), m_spinboxExposureLimitMax->value());
}

void IplFeaturesWidget::OnGainAutoLimitChange(double)
{
    m_spinboxGainAutoLimitMax->setMinimum(m_spinboxGainAutoLimitMin->value());
    backend_ipl_brightness_gain_limit_set(m_spinboxGainAutoLimitMin->value(), m_spinboxGainAutoLimitMax->value());
}

void IplFeaturesWidget::OnGainAnalogLimitChange(double)
{
    m_spinboxGainAnalogLimitMax->setMinimum(m_spinboxGainAnalogLimitMin->value());
    backend_ipl_brightness_gain_analog_limit_set(m_spinboxGainAnalogLimitMin->value(), m_spinboxGainAnalogLimitMax->value());
}

void IplFeaturesWidget::OnGainDigitalLimitChange(double)
{
    m_spinboxGainDigitalLimitMax->setMinimum(m_spinboxGainDigitalLimitMin->value());
    backend_ipl_brightness_gain_digital_limit_set(m_spinboxGainDigitalLimitMin->value(), m_spinboxGainDigitalLimitMax->value());
}

void IplFeaturesWidget::OnGainCombinedLimitChange(double)
{
    m_spinboxGainCombinedLimitMax->setMinimum(m_spinboxGainCombinedLimitMin->value());
    backend_ipl_brightness_gain_combined_limit_set(m_spinboxGainCombinedLimitMin->value(), m_spinboxGainCombinedLimitMax->value());
}

void IplFeaturesWidget::OnGainHostLimitChange(double)
{
    m_spinboxGainHostLimitMax->setMinimum(m_spinboxGainHostLimitMin->value());
    backend_ipl_brightness_gain_host_limit_set(m_spinboxGainHostLimitMin->value(), m_spinboxGainHostLimitMax->value());
}


void IplFeaturesWidget::CheckForChangedValues()
{
    auto mode = backend_ipl_brightness_exposureMode_get();
    bool keepRunning = false;
    if (mode == 0)
    {
        if (mode != m_comboExposureMode->currentIndex())
        {
            m_comboExposureMode->setCurrentIndex(mode);
            emit exposureAutoModeChanged(false);
            emit updateExposureTime();
        }
    }
    else
    {
        keepRunning = true;
        emit updateExposureTime();
    }

    mode = backend_ipl_brightness_gainMode_get();
    if (mode == 0)
    {
        if (mode != m_comboGainModeAuto->currentIndex())
        {
            m_comboGainModeAuto->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
        emit updateGainAuto();
    }
    
    mode = backend_ipl_brightness_gainAnalogMode_get();
    if (mode == 0)
    {
        if (mode != m_comboGainModeAnalog->currentIndex())
        {
            m_comboGainModeAnalog->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
        emit updateGainAnalog();
    }

    mode = backend_ipl_brightness_gainDigitalMode_get();
    if (mode == 0)
    {
        if (mode != m_comboGainModeDigital->currentIndex())
        {
            m_comboGainModeDigital->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
        emit updateGainDigital();
    }

    mode = backend_ipl_brightness_gainCombinedMode_get();
    if (mode == 0)
    {
        if (mode != m_comboGainModeCombined->currentIndex())
        {
            m_comboGainModeCombined->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
        emit updateGainCombined();
    }

    mode = backend_ipl_brightness_gainHostMode_get();
    if (mode == 0)
    {
        if (mode != m_comboGainModeHost->currentIndex())
        {
            m_comboGainModeHost->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
        emit updateGainHost();
    }

    mode = backend_ipl_whiteBalance_mode_get();
    if (mode == 0)
    {
        if (mode != m_comboWhiteBalanceMode->currentIndex())
        {
            m_comboWhiteBalanceMode->setCurrentIndex(mode);
            UpdateGain();
        }
    }
    else
    {
        UpdateGain();
        keepRunning = true;
    }

    auto count = backend_ipl_hotpixelCorrection_list_getCount();
    if (count != 0)
    {
        m_labelHotpixelCountValue->setText(QString::number(count));
    }
    else if (m_checkBoxHotpixelEnable->isChecked())
    {
        keepRunning = true;
    }

    if (!keepRunning)
    {
        m_timer->stop();
    }
}

void IplFeaturesWidget::OnComboWhiteBalanceMode(const QString& text)
{
    if (text == "Off")
    {
        backend_ipl_whiteBalance_mode_set(0);
    }
    else if (text == "Once")
    {
        backend_ipl_whiteBalance_mode_set(1);

        // start a timer that checks if the white balance auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_whiteBalance_mode_set(2);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void IplFeaturesWidget::OnComboWhiteBalanceRoiMode(const QString& text)
{
    if (text == "Full Image")
    {
        backend_ipl_whiteBalance_roiMode_set(0);
    }
    else if (text == "Manual")
    {
        backend_ipl_whiteBalance_roiMode_set(1);
    }
    UpdateWhiteBalanceRoi();
}

void IplFeaturesWidget::OnSliderWhiteBalanceRoi(int value)
{
    auto roi = backend_ipl_whiteBalance_roi_get();
    if (sender() == m_sliderWhiteBalanceRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == m_sliderWhiteBalanceRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == m_sliderWhiteBalanceRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == m_sliderWhiteBalanceRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_whiteBalance_roi_set(roi);
    UpdateWhiteBalanceRoi();
}

void IplFeaturesWidget::OnEditWhiteBalanceRoi()
{
    QString text = dynamic_cast<QLineEdit*>(sender())->text();
    auto roi = backend_ipl_whiteBalance_roi_get();
    auto value = text.toInt();
    if (sender() == m_editWhiteBalanceRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == m_editWhiteBalanceRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == m_editWhiteBalanceRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == m_editWhiteBalanceRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_whiteBalance_roi_set(roi);
    UpdateWhiteBalanceRoi();
}

void IplFeaturesWidget::OnSliderGainMaster(int value)
{
    double val = static_cast<double>(value) * m_gainMasterInc + m_gainMasterMin;
    if (val > m_gainMasterMax)
    {
        val = m_gainMasterMax;
    }
    backend_ipl_gainMaster_set(val);
    UpdateGain();
}

void IplFeaturesWidget::OnEditGainMaster()
{
    auto value = m_editGainMaster->text().toDouble();
    backend_ipl_gainMaster_set(value);
    UpdateGain();
}

void IplFeaturesWidget::OnSliderGainRed(int value)
{
    double val = static_cast<double>(value) * m_gainRedInc + m_gainRedMin;
    if (val > m_gainRedMax)
    {
        val = m_gainRedMax;
    }
    backend_ipl_gainRed_set(val);
    UpdateGain();
}

void IplFeaturesWidget::OnEditGainRed()
{
    auto value = m_editGainRed->text().toDouble();
    backend_ipl_gainRed_set(value);
    UpdateGain();
}

void IplFeaturesWidget::OnSliderGainGreen(int value)
{
    double val = static_cast<double>(value) * m_gainGreenInc + m_gainGreenMin;
    if (val > m_gainGreenMax)
    {
        val = m_gainGreenMax;
    }
    backend_ipl_gainGreen_set(val);
    UpdateGain();
}

void IplFeaturesWidget::OnEditGainGreen()
{
    auto value = m_editGainGreen->text().toDouble();
    backend_ipl_gainGreen_set(value);
    UpdateGain();
}

void IplFeaturesWidget::OnSliderGainBlue(int value)
{
    double val = static_cast<double>(value) * m_gainBlueInc + m_gainBlueMin;
    if (val > m_gainBlueMax)
    {
        val = m_gainBlueMax;
    }
    backend_ipl_gainBlue_set(val);
    UpdateGain();
}

void IplFeaturesWidget::OnEditGainBlue()
{
    auto value = m_editGainBlue->text().toDouble();
    backend_ipl_gainBlue_set(value);
    UpdateGain();
}

void IplFeaturesWidget::OnSliderGamma(int value)
{
    double val = static_cast<double>(value) * m_gammaInc + m_gammaMin;
    if (val > m_gammaMax)
    {
        val = m_gammaMax;
    }
    backend_ipl_gamma_set(val);
    UpdateGamma();
}

void IplFeaturesWidget::OnEditGamma()
{
    auto value = m_editGamma->text().toDouble();
    backend_ipl_gamma_set(value);
    UpdateGamma();
}

void IplFeaturesWidget::OnSliderDigitalBlack(int value)
{
    backend_ipl_digital_black_set(static_cast<float>(value) / 100.0f);
    UpdateDigitalBlack();
}

void IplFeaturesWidget::OnEditDigitalBlack()
{
    auto value = m_editDigitalBlack->text().toDouble();
    backend_ipl_digital_black_set(value);
    UpdateDigitalBlack();
}

void IplFeaturesWidget::OnColorCorrectionEnable(int state)
{
    if (state == Qt::Checked)
    {
        backend_ipl_colorCorrection_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        backend_ipl_colorCorrection_enable(false);
    }
    UpdateColorCorrection();
}


void IplFeaturesWidget::OnEditCcm()
{
    auto line_edit = dynamic_cast<QLineEdit*>(sender());
    if (!line_edit)
    {
        return;
    }

    QString text = line_edit->text();

    auto value = text.toDouble();
    auto ccm = backend_ipl_colorCorrectionMatrix_get();

    if (sender() == m_editCcm00)
    {
        ccm.elementArray[0][0] = value;
    }
    else if (sender() == m_editCcm01)
    {
        ccm.elementArray[0][1] = value;
    }
    else if (sender() == m_editCcm02)
    {
        ccm.elementArray[0][2] = value;
    }
    else if (sender() == m_editCcm10)
    {
        ccm.elementArray[1][0] = value;
    }
    else if (sender() == m_editCcm11)
    {
        ccm.elementArray[1][1] = value;
    }
    else if (sender() == m_editCcm12)
    {
        ccm.elementArray[1][2] = value;
    }
    else if (sender() == m_editCcm20)
    {
        ccm.elementArray[2][0] = value;
    }
    else if (sender() == m_editCcm21)
    {
        ccm.elementArray[2][1] = value;
    }
    else if (sender() == m_editCcm22)
    {
        ccm.elementArray[2][2] = value;
    }

    backend_ipl_colorCorrectionMatrix_set(ccm);
    UpdateColorCorrection();
}

void IplFeaturesWidget::OnButtonCcmDefault()
{
    backend_ipl_colorCorrectionMatrix_setDefault();
    UpdateColorCorrection();
}

void IplFeaturesWidget::OnButtonCcmIdentity()
{
    backend_ipl_colorCorrectionMatrix_setIdentity();
    UpdateColorCorrection();
}

void IplFeaturesWidget::OnCheckBoxMirrorLeftRight(int state)
{
    if (state == Qt::Checked)
    {
        backend_ipl_mirrorLeftRight_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        backend_ipl_mirrorLeftRight_enable(false);
    }

    UpdateTransformations();
}

void IplFeaturesWidget::OnCheckBoxMirrorUpDown(int state)
{
    if (state == Qt::Checked)
    {
        backend_ipl_mirrorUpDown_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        backend_ipl_mirrorUpDown_enable(false);
    }

    UpdateTransformations();
}

void IplFeaturesWidget::OnHotpixelCorrectionEnable(int state)
{
    if (state == Qt::Checked)
    {
        backend_ipl_hotpixelCorrection_enable(true);
        m_labelHotpixelCountValue->setText("");
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (state == Qt::Unchecked)
    {
        backend_ipl_hotpixelCorrection_enable(false);
        m_labelHotpixelCountValue->setText("");
    }

    UpdateHotpixel();
}

void IplFeaturesWidget::OnSpinBoxHotpixelSensitivity(int value)
{
    backend_ipl_hotpixelCorrection_sensitivity_set(value);

    m_labelHotpixelCountValue->setText("");
    if (!m_timer->isActive())
    {
        m_timer->start(500);
    }

    UpdateHotpixel();
}

void IplFeaturesWidget::OnButtonHotpixelResetList()
{
    backend_ipl_hotpixelCorrection_resetList();

    m_labelHotpixelCountValue->setText("");
    if (!m_timer->isActive())
    {
        m_timer->start(500);
    }
}

void IplFeaturesWidget::OnEdgeEnhancementEnable(bool enabled)
{
    backend_ipl_edgeEnhancement_setEnabled(enabled);
}

void IplFeaturesWidget::OnEdgeEnhancementFactorChanged(int value)
{
    m_spinBoxEdgeEnhancementFactor->blockSignals(true);
    m_spinBoxEdgeEnhancementFactor->setValue(value);
    m_spinBoxEdgeEnhancementFactor->blockSignals(false);

    m_sliderEdgeEnhancementFactor->blockSignals(true);
    m_sliderEdgeEnhancementFactor->setValue(value);
    m_sliderEdgeEnhancementFactor->blockSignals(false);

    backend_ipl_edgeEnhancement_factor_set(static_cast<std::uint8_t>(value));
}
