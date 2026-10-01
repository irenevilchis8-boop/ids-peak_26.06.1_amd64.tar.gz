/*!
 * \file    mainwindow.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
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

#include "mainwindow.h"

#include "backend.h"

#include "acquisitionworker.h"
#include "display.h"

#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>
#include <QThread>
#include <QWidget>
#include <QFontDatabase>

#include <cinttypes>
#include <cstdint>


#define VERSION "2.0.0"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_centralWidget);
    setCentralWidget(m_centralWidget);

    // Set minimum window size
    setMinimumSize(1280, 1080);

    // connect the error callback from backend to MainWindow
    connect(this, &MainWindow::libraryError, this, &MainWindow::HandleLibraryError);
    backend_errorCallback_connect(this, &MainWindow::EmitErrorSignal);

    // Start function of backend: open library, open camera
    int status = backend_start();
    if (status != 0)
    {
        m_hasError = true;
        m_blockErrorMessages = true;
        backend_exit();
        return;
    }

    backend_acquisition_prepare();

    // Create all user interface controls
    ComposeMainWindow();
    CreateControls();

    char modelName[64];
    backend_camera_modelName(modelName);
    setWindowTitle(modelName);

    // Create and start worker thread that will wait for images from the camera
    CreateAcquisitionWorkerThread();
    StartAcquisition();

    m_blockErrorMessages = false;
    m_exposureAutoActive = false;
    m_hasError = false;
}


MainWindow::~MainWindow()
{
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();
    }

    backend_exit();
}


bool MainWindow::hasError() const
{
    return m_hasError;
}


void MainWindow::ComposeMainWindow()
{
    // Create a display for the camera image
    m_display = new Display(m_centralWidget);

    m_layout->addWidget(m_display);

    auto statusbar = new QStatusBar(this);

    m_labelInfo = new QLabel(this);
    statusbar->addPermanentWidget(m_labelInfo, 2);

    auto m_labelVersion = new QLabel(("ipl_features_live_qtwidgets_c v" VERSION), this);
    statusbar->addPermanentWidget(m_labelVersion);

    auto m_labelAboutQt = new QLabel(R"(<a href="#aboutQt">About Qt</a>)", this);
    connect(m_labelAboutQt, &QLabel::linkActivated, this, &MainWindow::OnAboutQtLinkActivated);
    statusbar->addPermanentWidget(m_labelAboutQt);

    setStatusBar(statusbar);

    show();
}


void MainWindow::CreateControls()
{
    m_dockedControlsWidget = new QDockWidget("Controls", this);
    m_dockedControlsWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_dockedControlsWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_controlsWidget = new QWidget(m_dockedControlsWidget);
    m_dockedControlsWidget->setWidget(m_controlsWidget);

    auto layoutControls = new QGridLayout(m_controlsWidget);
    m_controlsWidget->setLayout(layoutControls);
    layoutControls->setSpacing(24);

    m_buttonStartStop = new QPushButton("Stop acquisition", m_controlsWidget);
    connect(m_buttonStartStop, &QPushButton::clicked, this, &MainWindow::OnButtonStopStart);

    m_labelExposureTime = new QLabel("Exposure time (us)", m_controlsWidget);
    m_sliderExposureTime = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editExposureTime = new QLineEdit(m_controlsWidget);
    m_editExposureTime->setFixedWidth(80);
    connect(m_sliderExposureTime, &QSlider::valueChanged, this, &MainWindow::OnSliderExposureTime);
    connect(m_editExposureTime, &QLineEdit::editingFinished, this, &MainWindow::OnEditExposureTime);

    m_labelGainAnalog = new QLabel("Gain analog", m_controlsWidget);
    m_sliderGainAnalog = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editGainAnalog = new QLineEdit(m_controlsWidget);
    m_editGainAnalog->setFixedWidth(80);
    connect(m_sliderGainAnalog, &QSlider::valueChanged, this, &MainWindow::OnSliderGain);
    connect(m_editGainAnalog, &QLineEdit::editingFinished, this, &MainWindow::OnEditGain);

    m_labelGainDigital = new QLabel("Gain digital", m_controlsWidget);
    m_sliderGainDigital = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editGainDigital = new QLineEdit(m_controlsWidget);
    m_editGainDigital->setFixedWidth(80);
    connect(m_sliderGainDigital, &QSlider::valueChanged, this, &MainWindow::OnSliderGainDigital);
    connect(m_editGainDigital, &QLineEdit::editingFinished, this, &MainWindow::OnEditGainDigital);

    m_labelGainCombined = new QLabel("Gain combined", m_controlsWidget);
    m_sliderGainCombined = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editGainCombined = new QLineEdit(m_controlsWidget);
    m_editGainCombined->setFixedWidth(80);
    connect(m_sliderGainCombined, &QSlider::valueChanged, this, &MainWindow::OnSliderGainCombined);
    connect(m_editGainCombined, &QLineEdit::editingFinished, this, &MainWindow::OnEditGainCombined);

    m_labelGainHost = new QLabel("Gain host", m_controlsWidget);
    m_sliderGainHost = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editGainHost = new QLineEdit(m_controlsWidget);
    m_editGainHost->setFixedWidth(80);
    connect(m_sliderGainHost, &QSlider::valueChanged, this, &MainWindow::OnSliderGainHost);
    connect(m_editGainHost, &QLineEdit::editingFinished, this, &MainWindow::OnEditGainHost);

    m_labelFrameRate = new QLabel("Framerate (fps)", m_controlsWidget);
    m_sliderFrameRate = new QSlider(Qt::Orientation::Horizontal, m_controlsWidget);
    m_editFrameRate = new QLineEdit(m_controlsWidget);
    m_editFrameRate->setFixedWidth(80);
    connect(m_sliderFrameRate, &QSlider::valueChanged, this, &MainWindow::OnSliderFrameRate);
    connect(m_editFrameRate, &QLineEdit::editingFinished, this, &MainWindow::OnEditFrameRate);

    // The group boxes display the controls in separate boxes
    m_generalGroupBox = new QGroupBox("General");
    m_generalLayout = new QGridLayout(m_generalGroupBox);

    // The controls for the IPL features
    m_iplFeaturesWidget = new IplFeaturesWidget(this);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::error, this, &MainWindow::HandleErrorAndQuit);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::exposureAutoModeChanged, this, &MainWindow::OnExposureAutoModeChanged);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::gainAutoModeAutoChanged, this, &MainWindow::OnGainAutoModeChanged);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::gainAutoModeAnalogChanged, this, &MainWindow::OnGainAnalogModeChanged);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::gainDigitalAutoModeChanged, this, &MainWindow::OnGainDigitalModeChanged);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::gainHostAutoModeChanged, this, &MainWindow::OnGainHostModeChanged);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateGainAuto, this, &MainWindow::UpdateGainControlAuto);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateGainAnalog, this, &MainWindow::UpdateGainControlAnalog);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateGainDigital, this, &MainWindow::UpdateGainControlDigital);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateGainCombined, this, &MainWindow::UpdateGainControlCombined);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateGainHost, this, &MainWindow::UpdateGainControlHost);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateExposureTime, this, &MainWindow::UpdateExposureTimeControl);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateExposureTime, this, &MainWindow::UpdateFrameRateControl);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateDisplayBrightnessRoi, this, &MainWindow::UpdateDisplayBrightnessRoi);
    connect(m_iplFeaturesWidget, &IplFeaturesWidget::updateDisplayWhitebalanceRoi, this, &MainWindow::UpdateDisplayWhitebalanceRoi);

    // Add the controls to the layouts
    m_generalLayout->addWidget(m_labelExposureTime, 0, 0);
    m_generalLayout->addWidget(m_sliderExposureTime, 0, 1);
    m_generalLayout->addWidget(m_editExposureTime, 0, 2);

    m_generalLayout->addWidget(m_labelGainAnalog, 1, 0);
    m_generalLayout->addWidget(m_sliderGainAnalog, 1, 1);
    m_generalLayout->addWidget(m_editGainAnalog, 1, 2);

    m_generalLayout->addWidget(m_labelGainDigital, 2, 0);
    m_generalLayout->addWidget(m_sliderGainDigital, 2, 1);
    m_generalLayout->addWidget(m_editGainDigital, 2, 2);

    m_generalLayout->addWidget(m_labelGainCombined, 3, 0);
    m_generalLayout->addWidget(m_sliderGainCombined, 3, 1);
    m_generalLayout->addWidget(m_editGainCombined, 3, 2);

    m_generalLayout->addWidget(m_labelGainHost, 4, 0);
    m_generalLayout->addWidget(m_sliderGainHost, 4, 1);
    m_generalLayout->addWidget(m_editGainHost, 4, 2);

    m_generalLayout->addWidget(m_labelFrameRate, 5, 0);
    m_generalLayout->addWidget(m_sliderFrameRate, 5, 1);
    m_generalLayout->addWidget(m_editFrameRate, 5, 2);

    m_generalLayout->addWidget(m_buttonStartStop, 6, 0, 1, 3);

    layoutControls->addWidget(m_generalGroupBox);
    layoutControls->addWidget(m_iplFeaturesWidget);

    addDockWidget(Qt::LeftDockWidgetArea, m_dockedControlsWidget);

    auto width = m_controlsWidget->minimumSize().width();

    if(width == 0)
    {
        width = 200;
    }
    resizeDocks({ m_dockedControlsWidget }, { width }, Qt::Horizontal);
}

void MainWindow::UpdateExposureTimeControl()
{
    if (backend_exposureTime_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderExposureTime->blockSignals(true);
        m_editExposureTime->blockSignals(true);

        struct range_double range = backend_exposureTime_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read exposure time range.");
        }
        double exposureTime = backend_exposureTime_get();
        if (exposureTime == 0)
        {
            HandleErrorAndQuit("Unable to read exposure time.");
        }

        m_exposureTimeMin = range.min;

        m_exposureTimeInc = range.inc;

        if(backend_ipl_brightness_exposureMode_get() == 0)
        {
            int steps = static_cast<int>((range.max - m_exposureTimeMin) / m_exposureTimeInc);
            m_sliderExposureTime->setRange(0, steps);
        }
        else
        {
            // limit exposure control to 95 %
            auto max = 0.95 * 1000000.0 / backend_frameRate_get();
            int steps = static_cast<int>((max - m_exposureTimeMin) / m_exposureTimeInc);
            m_sliderExposureTime->setRange(0, steps);
        }

        int value = static_cast<int>((exposureTime - m_exposureTimeMin) / m_exposureTimeInc);

        m_sliderExposureTime->setValue(value);

        m_editExposureTime->setText(QString::number(exposureTime, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderExposureTime->blockSignals(false);
        m_editExposureTime->blockSignals(false);
    }

    if (backend_exposureTime_isWriteable() && (!m_exposureAutoActive || !m_acquisitionRunning))
    {
        m_labelExposureTime->setEnabled(true);
        m_sliderExposureTime->setEnabled(true);
        m_editExposureTime->setEnabled(true);
    }
    else
    {
        m_labelExposureTime->setEnabled(false);
        m_sliderExposureTime->setEnabled(false);
        m_editExposureTime->setEnabled(false);
    }
}

void MainWindow::UpdateGainControlAuto()
{
    UpdateGainControlAnalog();
    UpdateGainControlDigital();
    UpdateGainControlCombined();
    UpdateGainControlHost();
}

void MainWindow::UpdateGainControlAnalog()
{
    if (backend_gain_analog_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderGainAnalog->blockSignals(true);
        m_editGainAnalog->blockSignals(true);

        struct range_double range = backend_gain_analog_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read gain range.");
        }
        double gain = backend_gain_analog_get();
        if (gain == 0)
        {
            HandleErrorAndQuit("Unable to read gain.");
        }

        m_gainMin = range.min;

        m_gainInc = range.inc;

        int steps = static_cast<int>((range.max - m_gainMin) / m_gainInc);
        m_sliderGainAnalog->setRange(0, steps);

        int value = static_cast<int>((gain - m_gainMin) / m_gainInc);

        m_sliderGainAnalog->setValue(value);

        m_editGainAnalog->setText(QString::number(gain, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderGainAnalog->blockSignals(false);
        m_editGainAnalog->blockSignals(false);
    }

    if (backend_gain_analog_isWriteable() && (!m_gainAnalogAutoActive || !m_acquisitionRunning))
    {
        m_labelGainAnalog->setEnabled(true);
        m_sliderGainAnalog->setEnabled(true);
        m_editGainAnalog->setEnabled(true);
    }
    else
    {
        m_labelGainAnalog->setEnabled(false);
        m_sliderGainAnalog->setEnabled(false);
        m_editGainAnalog->setEnabled(false);

        const auto supported = backend_gain_analog_isWriteable();
        m_labelGainAnalog->setVisible(supported);
        m_sliderGainAnalog->setVisible(supported);
        m_editGainAnalog->setVisible(supported);
    }
}


void MainWindow::UpdateGainControlDigital()
{
    if (backend_gain_digital_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderGainDigital->blockSignals(true);
        m_editGainDigital->blockSignals(true);

        struct range_double range = backend_gain_digital_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read gain range.");
        }
        double gain = backend_gain_digital_get();
        if (gain == 0)
        {
            HandleErrorAndQuit("Unable to read gain.");
        }

        m_gainMinDigital = range.min;

        m_gainIncDigital = range.inc;

        int steps = static_cast<int>((range.max - m_gainMinDigital) / m_gainIncDigital);
        m_sliderGainDigital->setRange(0, steps);

        int value = static_cast<int>((gain - m_gainMinDigital) / m_gainIncDigital);

        m_sliderGainDigital->setValue(value);

        m_editGainDigital->setText(QString::number(gain, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderGainDigital->blockSignals(false);
        m_editGainDigital->blockSignals(false);
    }

    if (backend_gain_digital_isWriteable() && (!m_gainDigitalAutoActive || !m_acquisitionRunning))
    {
        m_labelGainDigital->setEnabled(true);
        m_sliderGainDigital->setEnabled(true);
        m_editGainDigital->setEnabled(true);
    }
    else
    {
        m_labelGainDigital->setEnabled(false);
        m_sliderGainDigital->setEnabled(false);
        m_editGainDigital->setEnabled(false);

        const auto supported = backend_gain_digital_isWriteable();
        m_labelGainDigital->setVisible(supported);
        m_sliderGainDigital->setVisible(supported);
        m_editGainDigital->setVisible(supported);
    }
}


void MainWindow::UpdateGainControlCombined()
{
    if (backend_gain_combined_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderGainCombined->blockSignals(true);
        m_editGainCombined->blockSignals(true);

        struct range_double range = backend_gain_combined_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read gain combinedrange.");
        }
        double gain = backend_gain_combined_get();
        if (gain == 0)
        {
            HandleErrorAndQuit("Unable to read combined gain.");
        }

        m_gainMinCombined = range.min;

        m_gainIncCombined = range.inc;

        int steps = static_cast<int>((range.max - m_gainMinCombined) / m_gainIncCombined);
        m_sliderGainCombined->setRange(0, steps);

        int value = static_cast<int>((gain - m_gainMinCombined) / m_gainIncCombined);

        m_sliderGainCombined->setValue(value);

        m_editGainCombined->setText(QString::number(gain, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderGainCombined->blockSignals(false);
        m_editGainCombined->blockSignals(false);
    }

    if (backend_gain_combined_isWriteable() && (!m_gainCombinedAutoActive || !m_acquisitionRunning))
    {
        m_labelGainCombined->setEnabled(true);
        m_sliderGainCombined->setEnabled(true);
        m_editGainCombined->setEnabled(true);
    }
    else
    {
        m_labelGainCombined->setEnabled(false);
        m_sliderGainCombined->setEnabled(false);
        m_editGainCombined->setEnabled(false);

        const auto supported = backend_gain_combined_isWriteable();
        m_labelGainCombined->setVisible(supported);
        m_sliderGainCombined->setVisible(supported);
        m_editGainCombined->setVisible(supported);
    }
}

void MainWindow::UpdateGainControlHost()
{
    if (backend_gain_host_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderGainHost->blockSignals(true);
        m_editGainHost->blockSignals(true);

        struct range_double range = backend_ipl_gain_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read gain host range.");
        }
        double gain = backend_ipl_gain_get();
        if (gain == 0)
        {
            HandleErrorAndQuit("Unable to read host gain.");
        }

        m_gainMinHost = range.min;

        m_gainIncHost = range.inc;

        int steps = static_cast<int>((range.max - m_gainMinHost) / m_gainIncHost);
        m_sliderGainHost->setRange(0, steps);

        int value = static_cast<int>((gain - m_gainMinHost) / m_gainIncHost);

        m_sliderGainHost->setValue(value);

        m_editGainHost->setText(QString::number(gain, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderGainHost->blockSignals(false);
        m_editGainHost->blockSignals(false);
    }

    if (backend_gain_host_isWriteable() && (!m_gainHostAutoActive || !m_acquisitionRunning))
    {
        m_labelGainHost->setEnabled(true);
        m_sliderGainHost->setEnabled(true);
        m_editGainHost->setEnabled(true);
    }
    else
    {
        m_labelGainHost->setEnabled(false);
        m_sliderGainHost->setEnabled(false);
        m_editGainHost->setEnabled(false);

        const auto supported = backend_gain_host_isWriteable();
        m_labelGainHost->setVisible(supported);
        m_sliderGainHost->setVisible(supported);
        m_editGainHost->setVisible(supported);
    }
}

void MainWindow::UpdateFrameRateControl()
{
    if (backend_frameRate_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        m_sliderFrameRate->blockSignals(true);
        m_editFrameRate->blockSignals(true);

        struct range_double range = backend_frameRate_range();
        if (range.min == .0 && range.max == .0 && range.inc == .0)
        {
            HandleErrorAndQuit("Unable to read frame rate range.");
        }
        double frameRate = backend_frameRate_get();
        if (frameRate == 0)
        {
            HandleErrorAndQuit("Unable to read frame rate.");
        }

        m_frameRateMin = range.min;

        m_frameRateInc = range.inc;

        int steps = static_cast<int>((range.max - m_frameRateMin) / m_frameRateInc);
        m_sliderFrameRate->setRange(0, steps);

        int value = static_cast<int>((frameRate - m_frameRateMin) / m_frameRateInc);

        m_sliderFrameRate->setValue(value);

        m_editFrameRate->setText(QString::number(frameRate, 'f', 2));

        // Re-establish signals from slider and edit
        m_sliderFrameRate->blockSignals(false);
        m_editFrameRate->blockSignals(false);
    }

    if (backend_frameRate_isWriteable())
    {
        m_labelFrameRate->setEnabled(true);
        m_sliderFrameRate->setEnabled(true);
        m_editFrameRate->setEnabled(true);
    }
    else
    {
        m_labelFrameRate->setEnabled(false);
        m_sliderFrameRate->setEnabled(false);
        m_editFrameRate->setEnabled(false);
    }
}

void MainWindow::UpdateDisplayBrightnessRoi(QRect rect)
{
    m_display->setBrightnessRoiRect(rect);
}

void MainWindow::UpdateDisplayWhitebalanceRoi(QRect rect)
{
    m_display->setWhitebalanceRoiRect(rect);
}

void MainWindow::CreateAcquisitionWorkerThread()
{
    // Create worker thread that waits for new images from the camera
    m_acquisitionWorker = new AcquisitionWorker();
    m_acquisitionWorker->moveToThread(&m_acquisitionThread);

    // Worker must be started, when the acquisition starts
    connect(&m_acquisitionThread, SIGNAL(started()), m_acquisitionWorker, SLOT(Start()), Qt::UniqueConnection);

    // Connect the signal from the worker thread when a new image was received with the display update slot in the
    // Display class
    connect(m_acquisitionWorker, &AcquisitionWorker::imageReceived, m_display, &Display::OnImageReceived);

    // Connect the signal from the worker thread when the counters have changed with the update slot in the MainWindow
    // class
    connect(m_acquisitionWorker, &AcquisitionWorker::counterUpdated, this, &MainWindow::OnCounterUpdated);

    // Connect the signal from the worker thread when the acqusitions was started
    connect(m_acquisitionWorker, &AcquisitionWorker::started, this, &MainWindow::UpdateControls);

    // Connect the signal from the worker thread when the acqusitions was stopped
    connect(m_acquisitionWorker, &AcquisitionWorker::stopped, this, &MainWindow::UpdateControls);

    // Connect error signal of worker thread with slot in the MainWindow class
    connect(m_acquisitionWorker, &AcquisitionWorker::error, this, &MainWindow::HandleErrorAndQuit);
}


void MainWindow::StartAcquisition()
{
    // Start thread execution.
    backend_acquisition_start();

    m_acquisitionThread.start();
    m_acquisitionRunning = true;
}


void MainWindow::StopAcquisition()
{
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();

        backend_acquisition_stop();
    }
    m_acquisitionRunning = false;
}


void MainWindow::OnButtonStopStart()
{
    if ("Stop acquisition" == m_buttonStartStop->text())
    {
        m_buttonStartStop->setText("Start acquisition");
        StopAcquisition();
    }
    else
    {
        m_buttonStartStop->setText("Stop acquisition");
        StartAcquisition();
    }
}


void MainWindow::OnSliderExposureTime()
{
    int value = m_sliderExposureTime->value();

    double exposureTime = m_exposureTimeMin + static_cast<double>(value) * m_exposureTimeInc;

    if (backend_exposureTime_isWriteable())
    {
        backend_exposureTime_set(exposureTime);

        exposureTime = backend_exposureTime_get();

        m_editExposureTime->blockSignals(true);
        m_editExposureTime->setText(QString::number(exposureTime, 'f', 2));
        m_editExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnEditExposureTime()
{
    double exposureTime = m_editExposureTime->text().toDouble();

    if (backend_exposureTime_isWriteable())
    {
        backend_exposureTime_set(exposureTime);

        exposureTime = backend_exposureTime_get();

        int value = static_cast<int>((exposureTime - m_exposureTimeMin) / m_exposureTimeInc);

        m_sliderExposureTime->blockSignals(true);
        m_sliderExposureTime->setValue(value);
        m_sliderExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnSliderGain()
{
    int value = m_sliderGainAnalog->value();

    double gain = m_gainMin + static_cast<double>(value) * m_gainInc;

    if (backend_gain_analog_isWriteable())
    {
        backend_gain_analog_set(gain);

        gain = backend_gain_analog_get();

        m_editGainAnalog->blockSignals(true);
        m_editGainAnalog->setText(QString::number(gain, 'f', 2));
        m_editGainAnalog->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnEditGain()
{
    double gain = m_editGainAnalog->text().toDouble();

    if (backend_gain_analog_isWriteable())
    {
        backend_gain_analog_set(gain);

        gain = backend_gain_analog_get();

        int value = static_cast<int>((gain - m_gainMin) / m_gainInc);

        m_sliderExposureTime->blockSignals(true);
        m_sliderExposureTime->setValue(value);
        m_sliderExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnSliderGainDigital()
{
    int value = m_sliderGainDigital->value();
    double gain = m_gainMinDigital + static_cast<double>(value) * m_gainIncDigital;

    if (backend_gain_digital_isWriteable())
    {
        backend_gain_digital_set(gain);
        gain = backend_gain_digital_get();

        m_editGainDigital->blockSignals(true);
        m_editGainDigital->setText(QString::number(gain, 'f', 2));
        m_editGainDigital->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnEditGainDigital()
{
    double gain = m_editGainDigital->text().toDouble();

    if (backend_gain_digital_isWriteable())
    {
        backend_gain_digital_set(gain);

        gain = backend_gain_digital_get();

        int value = static_cast<int>((gain - m_gainMinDigital) / m_gainIncDigital);

        m_sliderExposureTime->blockSignals(true);
        m_sliderExposureTime->setValue(value);
        m_sliderExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnSliderGainCombined()
{
    int value = m_sliderGainCombined->value();
    double gain = m_gainMinCombined + static_cast<double>(value) * m_gainIncCombined;

    if (backend_gain_combined_isWriteable())
    {
        backend_gain_combined_set(gain);
        gain = backend_gain_combined_get();

        m_editGainCombined->blockSignals(true);
        m_editGainCombined->setText(QString::number(gain, 'f', 2));
        m_editGainCombined->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnEditGainCombined()
{
    double gain = m_editGainCombined->text().toDouble();

    if (backend_gain_combined_isWriteable())
    {
        backend_gain_combined_set(gain);

        gain = backend_gain_combined_get();

        int value = static_cast<int>((gain - m_gainMinCombined) / m_gainIncCombined);

        m_sliderGainCombined->blockSignals(true);
        m_sliderGainCombined->setValue(value);
        m_sliderGainCombined->blockSignals(false);
    }
    UpdateFrameRateControl();
}

void MainWindow::OnSliderGainHost()
{
    int value = m_sliderGainHost->value();
    double gain = m_gainMinHost + static_cast<double>(value) * m_gainIncHost;

    if (backend_gain_host_isWriteable())
    {
        backend_ipl_gain_set(gain);
        gain = backend_ipl_gain_get();

        m_editGainHost->blockSignals(true);
        m_editGainHost->setText(QString::number(gain, 'f', 2));
        m_editGainHost->blockSignals(false);
    }
    UpdateFrameRateControl();
}


void MainWindow::OnEditGainHost()
{
    double gain = m_editGainHost->text().toDouble();

    if (backend_gain_host_isWriteable())
    {
        backend_ipl_gain_set(gain);

        gain = backend_ipl_gain_get();

        int value = static_cast<int>((gain - m_gainMinHost) / m_gainIncHost);

        m_sliderGainHost->blockSignals(true);
        m_sliderGainHost->setValue(value);
        m_sliderGainHost->blockSignals(false);
    }
    UpdateFrameRateControl();
}



void MainWindow::OnSliderFrameRate()
{
    int value = m_sliderFrameRate->value();

    double frameRate = m_frameRateMin + static_cast<double>(value) * m_frameRateInc;

    if (backend_frameRate_isWriteable())
    {
        backend_frameRate_set(frameRate);

        frameRate = backend_frameRate_get();

        m_editFrameRate->blockSignals(true);
        m_editFrameRate->setText(QString::number(frameRate, 'f', 2));
        m_editFrameRate->blockSignals(false);
    }
}


void MainWindow::OnEditFrameRate()
{
    double frameRate = m_editFrameRate->text().toDouble();

    if (backend_frameRate_isWriteable())
    {
        backend_frameRate_set(frameRate);

        frameRate = backend_frameRate_get();

        int value = static_cast<int>((frameRate - m_frameRateMin) / m_frameRateInc);

        m_sliderFrameRate->blockSignals(true);
        m_sliderFrameRate->setValue(value);
        m_sliderFrameRate->blockSignals(false);
    }
}


void MainWindow::UpdateControls()
{
    UpdateExposureTimeControl();
    UpdateGainControlAnalog();
    UpdateGainControlDigital();
    UpdateGainControlCombined();
    UpdateGainControlHost();
    UpdateFrameRateControl();
}


void MainWindow::OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter)
{
    auto frameInfo = backend_frameInfo_get();
    auto processingTime = frameInfo->processingTime_ms;
    auto frameID = frameInfo->frameID;

    auto lastAverage = backend_ipl_brightness_averageLast_get();

    QString strText;
    strText.sprintf("Acquired: %4d, errors: %4d, Frame ID: %4" PRIu64 ", Processing Time: %03dms, last average: %d", frameCounter,
        errorCounter, frameID, processingTime, lastAverage);
    m_labelInfo->setText(strText);
    m_labelInfo->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
}


void MainWindow::OnAboutQtLinkActivated(const QString& link)
{
    if (link == "#aboutQt")
    {
        QMessageBox::aboutQt(this, "About Qt");
    }
}


void MainWindow::OnExposureAutoModeChanged(bool active)
{
    m_exposureAutoActive = active;
    UpdateExposureTimeControl();
    m_sliderExposureTime->setEnabled(!active);
    m_editExposureTime->setEnabled(!active);
}

void MainWindow::OnGainAutoModeChanged(bool active)
{
    if (backend_gain_analog_isWriteable())
    {
        OnGainAnalogModeChanged(active);    
    }
    else if (backend_gain_digital_isWriteable())
    {
        OnGainDigitalModeChanged(active);
    }
    else if (backend_gain_combined_isWriteable())
    {
        OnGainCombinedModeChanged(active);
    }
    else if (backend_gain_host_isWriteable())
    {
        OnGainHostModeChanged(active);
    }
}

void MainWindow::OnGainAnalogModeChanged(bool active)
{
    m_gainAnalogAutoActive = active;
    UpdateGainControlAnalog();
    m_sliderGainAnalog->setEnabled(!active);
    m_editGainAnalog->setEnabled(!active);
}

void MainWindow::OnGainDigitalModeChanged(bool active)
{
    m_gainDigitalAutoActive = active;
    UpdateGainControlDigital();
    m_sliderGainDigital->setEnabled(!active);
    m_editGainDigital->setEnabled(!active);
}

void MainWindow::OnGainCombinedModeChanged(bool active)
{
    m_gainCombinedAutoActive = active;
    UpdateGainControlCombined();
    m_sliderGainCombined->setEnabled(!active);
    m_editGainCombined->setEnabled(!active);
}

void MainWindow::OnGainHostModeChanged(bool active)
{
    m_gainHostAutoActive = active;
    UpdateGainControlHost();
    m_sliderGainHost->setEnabled(!active);
    m_editGainHost->setEnabled(!active);
}

void MainWindow::EmitErrorSignal(const char* message, int status, void* errorCallbackContext)
{
    emit static_cast<MainWindow*>(errorCallbackContext)->libraryError(QString::fromStdString(message), status);
};


void MainWindow::HandleLibraryError(QString message, int) const
{
    // block all error messages due to a critical message
    if (m_blockErrorMessages)
    {
        return;
    }

    message.prepend("Error: ");

    QMessageBox::warning(nullptr, "Error", message, QMessageBox::Ok);
}


void MainWindow::HandleErrorAndQuit(QString message) const
{
    // block all error messages due to a critical message
    if (m_blockErrorMessages)
    {
        return;
    }

    message += "\n(Error!)";
    message += "\nExiting application";

    QMessageBox::critical(nullptr, "Error", message, QMessageBox::Ok);
    qApp->quit();
}
