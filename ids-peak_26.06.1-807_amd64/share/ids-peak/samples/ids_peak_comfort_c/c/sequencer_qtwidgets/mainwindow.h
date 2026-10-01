/*!
 * \file    mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acquisitionworker.h"
#include "display.h"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QSlider>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QTimer>

#include <cstdint>

#include "additional_functions.h"
#include "customslider.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:

    QVBoxLayout* m_layout{};

    QWidget* m_centralWidget{};
    Display* m_display[NUMBER_OF_DISPLAYS]{};
    int m_selected{0};
    bool m_colorGainsSupported{};
    peak_gain_type m_masterGainType{ PEAK_GAIN_TYPE_ANALOG };

    QLabel* m_labelCameraInfo{};

    CustomSlider* m_sliderWidth{};
    CustomSlider* m_sliderHeight{};
    CustomSlider* m_sliderOffsetX{};
    CustomSlider* m_sliderOffsetY{};

    CustomSlider* m_sliderExposureTime{};
    CustomSlider* m_sliderGainMaster{};
    CustomSlider* m_sliderGainRed{};
    CustomSlider* m_sliderGainGreen{};
    CustomSlider* m_sliderGainBlue{};

    QTextEdit* m_labelStatus{};

    QPushButton* m_buttonStartStopConfiguration{};
    QPushButton* m_buttonTriggerSequence{};
    QPushButton* m_buttonResetToDefault{};
    QPushButton* m_buttonClearStatus{};

    QLabel* m_labelInfo{};

    AcquisitionWorker* m_acquisitionWorker{};
    QThread m_acquisitionThread{};

    peak_camera_handle m_hCam{};

    bool Check(peak_status status, const QString& errorMsg);

    void CheckColorGainsSupported();
    void CheckMasterGainType();

    void InitSequencerSettings();
    void UpdateSequencerSettings();
    void RestoreSequencerSettings();
    void EnableSequencerConfiguration(bool enable);

    QHBoxLayout* CreateCameraInfo();
    QHBoxLayout* CreateDisplays();
    QHBoxLayout* CreateSizeControls();
    QHBoxLayout* CreateOffsetControls();
    QHBoxLayout* CreateBrightnessControls();
    QHBoxLayout* CreateColorGainControls();
    QHBoxLayout* CreateStatusControl();
    QHBoxLayout* CreateButtonControls();
    QHBoxLayout* CreateInfoControls();

    void UpdateLabelSizes();

    void CreateAcquisitionWorkerThread();
    void StartAcquisition();
    void StopAcquisition();

    void UpdateSize();
    void UpdatePos();
    void UpdateExposureTime();
    void UpdateGains();
    void SelectDisplay(int number);
    void EnableControls(bool enable);

public slots:

    void OnAcquisitionStarted();
    void OnSliderSize();
    void OnSlider(double value);
    void OnDisplaySelected();
    void OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter);
    void OnSequenceFinished();
    void OnAboutQtLinkActivated(const QString& link);
    void OnButtonStartStopConfiguration();
    void OnButtonTriggerSequence();
    void OnButtonResetToDefault();
    void OnButtonClearStatus();
};

#endif // MAINWINDOW_H
