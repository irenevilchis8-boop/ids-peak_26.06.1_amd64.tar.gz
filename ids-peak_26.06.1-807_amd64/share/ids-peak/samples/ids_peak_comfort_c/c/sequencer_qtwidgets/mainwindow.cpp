/*!
 * \file    mainwindow.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \version 1.0.0
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

#include "mainwindow.h"

#include "acquisitionworker.h"
#include "display.h"

#include <QApplication>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QThread>
#include <QWidget>
#include <QScrollBar>

#include <cstdint>


#define VERSION "1.0.0"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    Check(peak_Library_Init(), "peak_Library_Init() failed");
    Check(peak_CameraList_Update(nullptr), "peak_CameraList_Update() failed");
    if (!Check(peak_Camera_OpenFirstAvailable(&m_hCam), "peak_Camera_OpenFirstAvailable() failed"))
    {
        QMessageBox::critical(this, "Error", "No camera available");
        exit(0);
    }

    if (PEAK_TRUE != Sequencer_IsSupported(m_hCam))
    {
        QMessageBox::critical(this, "Error", "The sequencer feature is not supported by this camera");
        exit(0);
    }

    CheckColorGainsSupported();
    CheckMasterGainType();

    m_centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_centralWidget);
    setCentralWidget(m_centralWidget);

    m_layout->addLayout(CreateCameraInfo());
    m_layout->addLayout(CreateDisplays());
    m_layout->addLayout(CreateSizeControls());
    m_layout->addSpacing(20);
    m_layout->addLayout(CreateOffsetControls());
    m_layout->addLayout(CreateBrightnessControls());
    m_layout->addLayout(CreateColorGainControls());
    m_layout->addLayout(CreateStatusControl());
    m_layout->addLayout(CreateButtonControls());
    m_layout->addSpacing(10);
    m_layout->addLayout(CreateInfoControls());

    EnableControls(false);
    UpdateLabelSizes();

    InitSequencerSettings();

    UpdateSize();

    setMinimumSize(1000, 600);

    CreateAcquisitionWorkerThread();
    StartAcquisition();
}

MainWindow::~MainWindow()
{
    if (peak_Acquisition_IsStarted(m_hCam))
    {
        StopAcquisition();
    }

    Check(Sequencer_Enable(m_hCam, false), "peak_Sequencer_Enable() failed");
    Check(peak_Camera_ResetToDefaultSettings(m_hCam), "peak_Camera_ResetToDefaultSettings() failed");
    Check(peak_Camera_Close(m_hCam), "peak_Camera_Close() failed");

    peak_Library_Exit();
}

bool MainWindow::Check(peak_status status, const QString& errorMsg)
{
    if (PEAK_STATUS_SUCCESS == status)
    {
        return true;
    }
    else
    {
        if (m_labelStatus)
        {
            QTextCursor cursor(m_labelStatus->textCursor());
            QTextCharFormat format;

            cursor.setCharFormat(format);
            cursor.insertText("Info: " + errorMsg + "\n");

            m_labelStatus->verticalScrollBar()->setValue(m_labelStatus->verticalScrollBar()->maximum());
        }

        return false;
    }
}

void MainWindow::CheckColorGainsSupported()
{
    m_colorGainsSupported = (PEAK_ACCESS_NOT_SUPPORTED != peak_Gain_GetAccessStatus(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_RED));
}

void MainWindow::CheckMasterGainType()
{
    if (PEAK_ACCESS_NOT_SUPPORTED == peak_Gain_GetAccessStatus(m_hCam, PEAK_GAIN_TYPE_ANALOG, PEAK_GAIN_CHANNEL_MASTER))
    {
        m_masterGainType = PEAK_GAIN_TYPE_DIGITAL;
    }
}

QHBoxLayout* MainWindow::CreateCameraInfo()
{
    auto layout = new QHBoxLayout();

    m_labelCameraInfo = new QLabel(this);
    peak_camera_id camID = peak_Camera_ID_FromHandle(m_hCam);

    peak_camera_descriptor camDesc;
    if (Check(peak_Camera_GetDescriptor(camID, &camDesc), "peak_Camera_GetDescriptor() failed"))
    {
        m_labelCameraInfo->setText("Camera " + QString::fromStdString(camDesc.modelName) + " (" + QString::fromStdString(camDesc.serialNumber) + ")");
    }

    layout->addWidget(m_labelCameraInfo);

    return layout;
}

QHBoxLayout* MainWindow::CreateDisplays()
{
    auto layout = new QHBoxLayout();

    auto col = palette().color(QWidget::backgroundRole());

    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        m_display[i] = new Display(i, m_centralWidget);
        m_display[i]->SetColorBackground(col);
        layout->addWidget(m_display[i]);
    }

    return layout;
}

QHBoxLayout* MainWindow::CreateSizeControls()
{
    auto layout = new QHBoxLayout();

    m_sliderWidth = new CustomSlider("Width (applied to whole sequence)");
    m_sliderWidth->EnableInteger(true);
    layout->addWidget(m_sliderWidth);
    connect(m_sliderWidth, &CustomSlider::ValueChanged, this, &MainWindow::OnSliderSize);

    layout->addSpacing(10);

    m_sliderHeight = new CustomSlider("Height (applied to whole sequence)");
    m_sliderHeight->EnableInteger(true);
    layout->addWidget(m_sliderHeight);
    connect(m_sliderHeight, &CustomSlider::ValueChanged, this, &MainWindow::OnSliderSize);

    return layout;
}

QHBoxLayout* MainWindow::CreateOffsetControls()
{
    auto layout = new QHBoxLayout();

    m_sliderOffsetX = new CustomSlider("Offset X");
    m_sliderOffsetX->EnableInteger(true);
    layout->addWidget(m_sliderOffsetX);
    connect(m_sliderOffsetX, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    layout->addSpacing(10);

    m_sliderOffsetY = new CustomSlider("Offset Y");
    m_sliderOffsetY->EnableInteger(true);
    layout->addWidget(m_sliderOffsetY);
    connect(m_sliderOffsetY, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    return layout;
}

QHBoxLayout* MainWindow::CreateBrightnessControls()
{
    auto layout = new QHBoxLayout();

    m_sliderExposureTime = new CustomSlider("Exposure time");
    layout->addWidget(m_sliderExposureTime);
    connect(m_sliderExposureTime, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    layout->addSpacing(10);

    m_sliderGainMaster = new CustomSlider("Gain master");
    layout->addWidget(m_sliderGainMaster);
    connect(m_sliderGainMaster, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    return layout;
}

QHBoxLayout* MainWindow::CreateColorGainControls()
{
    auto layout = new QHBoxLayout();

    m_sliderGainRed = new CustomSlider("Gain red");
    layout->addWidget(m_sliderGainRed);
    connect(m_sliderGainRed, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    m_sliderGainGreen = new CustomSlider("Gain green");
    layout->addWidget(m_sliderGainGreen);
    connect(m_sliderGainGreen, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    m_sliderGainBlue = new CustomSlider("Gain blue");
    layout->addWidget(m_sliderGainBlue);
    connect(m_sliderGainBlue, &CustomSlider::ValueChanged, this, &MainWindow::OnSlider);

    return layout;
}

QHBoxLayout* MainWindow::CreateStatusControl()
{
    auto layout = new QHBoxLayout();

    m_labelStatus = new QTextEdit();
    m_labelStatus->setFixedHeight(120);
    m_labelStatus->setReadOnly(true);
    m_labelStatus->setStyleSheet("QTextEdit { background: white; border: 1px solid #ADADAD }");
    layout->addWidget(m_labelStatus);

    return layout;
}

QHBoxLayout* MainWindow::CreateButtonControls()
{
    auto layout = new QHBoxLayout();

    m_buttonStartStopConfiguration = new QPushButton("Start configuration");
    m_buttonStartStopConfiguration->adjustSize();
    layout->addWidget(m_buttonStartStopConfiguration);
    connect(m_buttonStartStopConfiguration, &QPushButton::clicked, this, &MainWindow::OnButtonStartStopConfiguration);

    m_buttonTriggerSequence = new QPushButton("Trigger sequence");
    m_buttonTriggerSequence->adjustSize();
    layout->addWidget(m_buttonTriggerSequence);
    connect(m_buttonTriggerSequence, &QPushButton::clicked, this, &MainWindow::OnButtonTriggerSequence);

    m_buttonResetToDefault = new QPushButton("Reset camera to default");
    m_buttonResetToDefault->adjustSize();
    layout->addWidget(m_buttonResetToDefault);
    connect(m_buttonResetToDefault, &QPushButton::clicked, this, &MainWindow::OnButtonResetToDefault);

    m_buttonClearStatus = new QPushButton("Clear status");
    connect(m_buttonClearStatus, &QPushButton::clicked, this, &MainWindow::OnButtonClearStatus, Qt::UniqueConnection);
    layout->addWidget(m_buttonClearStatus);

    return layout;
}

QHBoxLayout* MainWindow::CreateInfoControls()
{
    auto layout = new QHBoxLayout();

    m_labelInfo = new QLabel(this);
    layout->addWidget(m_labelInfo);
    layout->addSpacing(20);
    layout->addStretch();

    auto labelVersion = new QLabel(("sequencer_qtwidgets_c v" VERSION), this);
    layout->addWidget(labelVersion);

    auto labelAboutQt = new QLabel(R"(<a href="#aboutQt">About Qt</a>)", this);
    connect(labelAboutQt, &QLabel::linkActivated, this, &MainWindow::OnAboutQtLinkActivated);
    layout->addWidget(labelAboutQt);

    return layout;
}

void MainWindow::InitSequencerSettings()
{
    Check(peak_Camera_ResetToDefaultSettings(m_hCam), "peak_Camera_ResetToDefaultSettings() failed");
    Check(Trigger_SoftwareBurst_Configure(m_hCam, NUMBER_OF_DISPLAYS), "peak_Trigger_SoftwareBurst_Configure() failed");

    Check(Sequencer_EnableConfiguration(m_hCam, PEAK_TRUE), "peak_Sequencer_Configuration_Enable() failed");

    for (int i = 0; i < NUMBER_OF_DISPLAYS - 1; i++)
    {
        Check(SequencerSet_Select(m_hCam, i), "peak_Sequencer_Set_Select() failed");
        Check(SequencerSet_SetNext(m_hCam, i + 1), "peak_Sequencer_Set_SelectNext() failed");
        Check(SequencerSet_SetTriggerSource(m_hCam, SEQUENCER_TRIGGERSOURCE_EXPOSURE_START), "peak_Sequencer_SetTriggerSourceExposureStart() failed");
    }

    Check(SequencerSet_Select(m_hCam, NUMBER_OF_DISPLAYS - 1), "peak_Sequencer_Set_Select() failed");
    Check(SequencerSet_SetNext(m_hCam, 0), "peak_Sequencer_Set_SelectNext() failed");
    Check(SequencerSet_SetTriggerSource(m_hCam, SEQUENCER_TRIGGERSOURCE_EXPOSURE_START), "peak_Sequencer_SetTriggerSourceExposureStart() failed");

    UpdateSequencerSettings();

    EnableSequencerConfiguration(false);
}

void MainWindow::UpdateSequencerSettings()
{
    UpdateExposureTime();
    UpdateGains();
    UpdatePos();
}

void MainWindow::RestoreSequencerSettings()
{
    Check(SequencerSet_Select(m_hCam, m_selected), "peak_Sequencer_Set_Select() failed");
    Check(SequencerSet_LoadSettings(m_hCam), "peak_Sequencer_LoadSettings() failed");

    UpdateSequencerSettings();
}

void MainWindow::EnableSequencerConfiguration(bool enable)
{
    if (enable)
    {
        Check(Sequencer_Enable(m_hCam, false), "peak_Sequencer_Enable() failed");
        Check(Sequencer_EnableConfiguration(m_hCam, true), "peak_Sequencer_Configuration_Enable() failed");
        SelectDisplay(m_selected);
    }
    else
    {
        Check(Sequencer_EnableConfiguration(m_hCam, false), "peak_Sequencer_Configuration_Enable() failed");
        Check(Sequencer_Enable(m_hCam, true), "peak_Sequencer_Enable() failed");
        SelectDisplay(-1);
    }
}

void MainWindow::UpdateLabelSizes()
{
    std::initializer_list<int> list { m_sliderOffsetX->GetLabelWidth(), m_sliderExposureTime->GetLabelWidth(), m_sliderGainRed->GetLabelWidth() };
    auto maximum = std::max(list) + 10;
    m_sliderOffsetX->SetLabelWidth(maximum);
    m_sliderExposureTime->SetLabelWidth(maximum);
    m_sliderGainRed->SetLabelWidth(maximum);
    maximum = std::max(m_sliderOffsetY->GetLabelWidth(), m_sliderGainMaster->GetLabelWidth()) + 10;
    m_sliderOffsetY->SetLabelWidth(maximum);
    m_sliderGainMaster->SetLabelWidth(maximum);
}

void MainWindow::CreateAcquisitionWorkerThread()
{
    m_acquisitionWorker = new AcquisitionWorker();
    m_acquisitionWorker->m_hCam = m_hCam;
    m_acquisitionWorker->moveToThread(&m_acquisitionThread);

    connect(&m_acquisitionThread, &QThread::started, m_acquisitionWorker, &AcquisitionWorker::Start, Qt::UniqueConnection);
    connect(m_acquisitionWorker, &AcquisitionWorker::Started, this, &MainWindow::OnAcquisitionStarted, Qt::UniqueConnection);

    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        connect(m_acquisitionWorker, &AcquisitionWorker::ImageReceived, m_display[i], &Display::OnImageReceived, Qt::UniqueConnection);
        connect(m_display[i], &Display::Signal_Selected, this, &MainWindow::OnDisplaySelected, Qt::UniqueConnection);
    }

    connect(m_acquisitionWorker, &AcquisitionWorker::CounterUpdated, this, &MainWindow::OnCounterUpdated, Qt::UniqueConnection);
    connect(m_acquisitionWorker, &AcquisitionWorker::SequenceFinished, this, &MainWindow::OnSequenceFinished, Qt::UniqueConnection);
}

void MainWindow::StartAcquisition()
{
    if (m_acquisitionThread.isRunning())
    {
        return;
    }

    if (PEAK_STATUS_SUCCESS == peak_Acquisition_Start(m_hCam, PEAK_INFINITE))
    {
        m_acquisitionThread.start();
    }
}

void MainWindow::StopAcquisition()
{
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        peak_Acquisition_Stop(m_hCam);
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();
    }
}

void MainWindow::UpdateSize()
{
    peak_size min;
    peak_size max;
    peak_size inc;

    if (Check(peak_ROI_Size_GetRange(m_hCam, &min, &max, &inc), "peak_ROI_Size_GetRange() failed"))
    {
        peak_size val;

        m_sliderWidth->SetRange(static_cast<double>(min.width), static_cast<double>(max.width), static_cast<double>(std::max(static_cast<int>(inc.width), 4)));
        m_sliderHeight->SetRange(static_cast<double>(min.height), static_cast<double>(max.height), static_cast<double>(inc.height));

        if (Check(peak_ROI_Size_Get(m_hCam, &val), "peak_ROI_Size_Get() failed"))
        {
            m_sliderWidth->SetValue(static_cast<double>(val.width));
            m_sliderHeight->SetValue(static_cast<double>(val.height));
        }
    }
}

void MainWindow::UpdatePos()
{
    peak_position min;
    peak_position max;
    peak_position inc;

    if (Check(peak_ROI_Offset_GetRange(m_hCam, &min, &max, &inc), "peak_ROI_Offset_GetRange() failed"))
    {
        peak_position val;

        m_sliderOffsetX->SetRange(static_cast<double>(min.x), static_cast<double>(max.x), static_cast<double>(static_cast<int>(inc.x)));
        m_sliderOffsetY->SetRange(static_cast<double>(min.y), static_cast<double>(max.y), static_cast<double>(inc.y));

        if (Check(peak_ROI_Offset_Get(m_hCam, &val), "peak_ROI_Offset_Get() failed"))
        {
            m_sliderOffsetX->SetValue(static_cast<double>(val.x));
            m_sliderOffsetY->SetValue(static_cast<double>(val.y));
        }
    }
}

void MainWindow::UpdateExposureTime()
{
    double min = 0;
    double max = 0;
    double inc = 0;
    double value = 0;

    if (Check(peak_ExposureTime_GetRange(m_hCam, &min, &max, &inc), "peak_ExposureTime_GetRange() failed"))
    {
        if (Check(peak_ExposureTime_Get(m_hCam, &value), "peak_ExposureTime_Get() failed"))
        {
            m_sliderExposureTime->SetRange(min, max, inc);
            m_sliderExposureTime->SetValue(value);
        }
    }
}

void MainWindow::UpdateGains()
{
    double min = 0;
    double max = 0;
    double inc = 0;
    double gain = 0;

    if (Check(peak_Gain_GetRange(m_hCam, m_masterGainType, PEAK_GAIN_CHANNEL_MASTER, &min, &max, &inc), "peak_Gain_GetRange() failed"))
    {
        if (Check(peak_Gain_Get(m_hCam, m_masterGainType, PEAK_GAIN_CHANNEL_MASTER, &gain), "peak_Gain_Get() failed"))
        {
            m_sliderGainMaster->SetRange(min, max, inc);
            m_sliderGainMaster->SetValue(gain);
        }
    }

    if (!m_colorGainsSupported)
    {
        return;
    }

    if (Check(peak_Gain_GetRange(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_RED, &min, &max, &inc), "peak_Gain_GetRange() failed"))
    {
        if (Check(peak_Gain_Get(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_RED, &gain), "peak_Gain_Get() failed"))
        {
            m_sliderGainRed->SetRange(min, max, inc);
            m_sliderGainRed->SetValue(gain);
        }
    }

    if (Check(peak_Gain_GetRange(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_GREEN, &min, &max, &inc), "peak_Gain_GetRange() failed"))
    {
        if (Check(peak_Gain_Get(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_GREEN, &gain), "peak_Gain_Get() failed"))
        {
            m_sliderGainGreen->SetRange(min, max, inc);
            m_sliderGainGreen->SetValue(gain);
        }
    }

    if (Check(peak_Gain_GetRange(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_BLUE, &min, &max, &inc), "peak_Gain_GetRange() failed"))
    {
        if (Check(peak_Gain_Get(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_BLUE, &gain), "peak_Gain_Get() failed"))
        {
            m_sliderGainBlue->SetRange(min, max, inc);
            m_sliderGainBlue->SetValue(gain);
        }
    }
}

void MainWindow::SelectDisplay(int number)
{
    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        m_display[i]->setStyleSheet("QGraphicsView { border: 1px solid grey }");
    }

    if (number > -1)
    {
        m_display[number]->setStyleSheet("QGraphicsView { border: 2px solid red }");
    }
}

void MainWindow::EnableControls(bool enable)
{
    m_buttonTriggerSequence->setEnabled(!enable);
    m_buttonResetToDefault->setEnabled(!enable);

    m_sliderWidth->setEnabled(enable);
    m_sliderHeight->setEnabled(enable);
    m_sliderOffsetX->setEnabled(enable);
    m_sliderOffsetY->setEnabled(enable);
    m_sliderExposureTime->setEnabled(enable);
    m_sliderGainMaster->setEnabled(enable);
    m_sliderGainRed->setEnabled(enable && m_colorGainsSupported);
    m_sliderGainGreen->setEnabled(enable && m_colorGainsSupported);
    m_sliderGainBlue->setEnabled(enable && m_colorGainsSupported);
}

void MainWindow::OnAcquisitionStarted()
{
    // Trigger one sequence after the program start
    static bool once = true;
    if (once)
    {
        once = false;
        OnButtonTriggerSequence();
    }
}

void MainWindow::OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter)
{
    QString strText;
    strText.sprintf("Acquired: %d, errors: %d", frameCounter, errorCounter);
    m_labelInfo->setText(strText);
}

void MainWindow::OnAboutQtLinkActivated(const QString& link)
{
    if (link == "#aboutQt")
    {
        QMessageBox::aboutQt(this, "About Qt");
    }
}

void MainWindow::OnSliderSize()
{
    Check(Sequencer_EnableConfiguration(m_hCam, false), "peak_Sequencer_Configuration_Enable() failed");

    peak_size val;
    val.width = m_sliderWidth->GetValue();
    val.height = m_sliderHeight->GetValue();

    Check(peak_ROI_Size_Set(m_hCam, val), "peak_ROI_Size_Set() failed");
    UpdateSize();

    Check(Sequencer_EnableConfiguration(m_hCam, true), "peak_Sequencer_Configuration_Enable() failed");

    RestoreSequencerSettings();
}

void MainWindow::OnSlider(double)
{
    Check(SequencerSet_Select(m_hCam, m_selected), "peak_Sequencer_Set_Select() failed");

    Check(peak_ExposureTime_Set(m_hCam, m_sliderExposureTime->GetValue()), "peak_ExposureTime_Set() failed");
    Check(peak_Gain_Set(m_hCam, m_masterGainType, PEAK_GAIN_CHANNEL_MASTER, m_sliderGainMaster->GetValue()), "peak_Gain_Set() failed");

    if (m_colorGainsSupported)
    {
        Check(peak_Gain_Set(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_RED, m_sliderGainRed->GetValue()), "peak_Gain_Set() failed");
        Check(peak_Gain_Set(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_GREEN, m_sliderGainGreen->GetValue()), "peak_Gain_Set() failed");
        Check(peak_Gain_Set(m_hCam, PEAK_GAIN_TYPE_DIGITAL, PEAK_GAIN_CHANNEL_BLUE, m_sliderGainBlue->GetValue()), "peak_Gain_Set() failed");
    }

    peak_position pos;
    pos.x = static_cast<uint32_t>(m_sliderOffsetX->GetValue());
    pos.y = static_cast<uint32_t>(m_sliderOffsetY->GetValue());
    Check(peak_ROI_Offset_Set(m_hCam, pos), "peak_ROI_Offset_Set() failed");

    Check(SequencerSet_SaveSettings(m_hCam), "peak_Sequencer_SaveSettings() failed");

    UpdateSequencerSettings();
}

void MainWindow::OnDisplaySelected()
{
    if (!m_sliderExposureTime->isEnabled())
    {
        return;
    }

    m_selected = 0;

    QObject* obj = sender();

    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        if (obj == m_display[i])
        {
            m_selected = i;
            break;
        }
    }

    SelectDisplay(m_selected);

    RestoreSequencerSettings();
}

void MainWindow::OnButtonStartStopConfiguration()
{
    if (m_sliderExposureTime->isEnabled())
    {
        m_buttonStartStopConfiguration->setText("Start configuration");
        EnableControls(false);

        EnableSequencerConfiguration(false);
        StartAcquisition();
    }
    else
    {
        m_buttonStartStopConfiguration->setText("Stop configuration");
        EnableControls(true);

        StopAcquisition();
        EnableSequencerConfiguration(true);
    }
}

void MainWindow::OnButtonTriggerSequence()
{
    if (Check(Trigger_SoftwareBurst_Execute(m_hCam), "peak_Trigger_SoftwareBurst_Execute() failed"))
    {
        m_buttonStartStopConfiguration->setEnabled(false);
        m_buttonTriggerSequence->setEnabled(false);
        m_buttonResetToDefault->setEnabled(false);
    }
}

void MainWindow::OnButtonResetToDefault()
{
    StopAcquisition();
    InitSequencerSettings();
    StartAcquisition();
}

void MainWindow::OnSequenceFinished()
{
    m_buttonStartStopConfiguration->setEnabled(true);
    m_buttonTriggerSequence->setEnabled(true);
    m_buttonResetToDefault->setEnabled(true);
}

void MainWindow::OnButtonClearStatus()
{
    m_labelStatus->clear();
}
