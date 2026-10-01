/*!
 * \file    mainwindow.h
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \version 1.0.0
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acquisitionworker.h"
#include "display.h"
#include "iplfeatureswidget.h"

#include "backend.h"


#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>
#include <QSlider>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>

#include <cstdint>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    bool hasError() const;

private:
    QWidget* m_centralWidget{};
    QWidget* m_controlsWidget{};
    QDockWidget* m_dockedControlsWidget{};

    Display* m_display{};
    QLabel* m_labelInfo{};
    QVBoxLayout* m_layout{};

    AcquisitionWorker* m_acquisitionWorker{};
    QThread m_acquisitionThread{};

    QPushButton* m_buttonStartStop{};

    QLabel* m_labelExposureTime{};
    QSlider* m_sliderExposureTime{};
    QLineEdit* m_editExposureTime{};

    QLabel* m_labelGainAnalog{};
    QSlider* m_sliderGainAnalog{};
    QLineEdit* m_editGainAnalog{};

    QLabel* m_labelGainDigital{};
    QSlider* m_sliderGainDigital{};
    QLineEdit* m_editGainDigital{};

    QLabel* m_labelGainCombined{};
    QSlider* m_sliderGainCombined{};
    QLineEdit* m_editGainCombined{};

    QLabel* m_labelGainHost{};
    QSlider* m_sliderGainHost{};
    QLineEdit* m_editGainHost{};

    QLabel* m_labelFrameRate{};
    QSlider* m_sliderFrameRate{};
    QLineEdit* m_editFrameRate{};

    QGroupBox* m_generalGroupBox{};
    QGridLayout* m_generalLayout{};

    IplFeaturesWidget* m_iplFeaturesWidget{};

    peak_camera_handle m_hCam{};

    double m_exposureTime{};
    double m_exposureTimeMin{};
    double m_exposureTimeMax{};
    double m_exposureTimeInc{};

    double m_gain{};
    double m_gainMin{};
    double m_gainMax{};
    double m_gainInc{};

    double m_gainDigital{};
    double m_gainMinDigital{};
    double m_gainMaxDigital{};
    double m_gainIncDigital{};

    double m_gainCombined{};
    double m_gainMinCombined{};
    double m_gainMaxCombined{};
    double m_gainIncCombined{};

    double m_gainHost{};
    double m_gainMinHost{};
    double m_gainMaxHost{};
    double m_gainIncHost{};

    double m_frameRate{};
    double m_frameRateMin{};
    double m_frameRateMax{};
    double m_frameRateInc{};

    bool m_gainAnalogAutoActive{};
    bool m_gainDigitalAutoActive{};
    bool m_gainCombinedAutoActive{};
    bool m_gainHostAutoActive{};
    bool m_exposureAutoActive{};
    bool m_acquisitionRunning{};

    bool m_hasError{};
    bool m_blockErrorMessages{};

    void ComposeMainWindow();
    void CreateControls();
    void UpdateExposureTimeControl();
    void UpdateGainControlAuto();
    void UpdateGainControlAnalog();
    void UpdateGainControlDigital();
    void UpdateGainControlCombined();
    void UpdateGainControlHost();
    void UpdateFrameRateControl();
    void UpdateDisplayBrightnessRoi(QRect rect);
    void UpdateDisplayWhitebalanceRoi(QRect rect);

    void CreateAcquisitionWorkerThread();
    void StartAcquisition();
    void StopAcquisition();

    static void EmitErrorSignal(const char* message, int status, void* errorCallbackContext);

public slots:
    void HandleLibraryError(QString message, int status) const;
    void HandleErrorAndQuit(QString message) const;

    void OnButtonStopStart();
    void OnSliderExposureTime();
    void OnEditExposureTime();
    void OnSliderGain();
    void OnEditGain();
    void OnSliderGainDigital();
    void OnSliderGainCombined();
    void OnSliderGainHost();
    void OnEditGainDigital();
    void OnEditGainCombined();
    void OnEditGainHost();
    void OnSliderFrameRate();
    void OnEditFrameRate();
    void UpdateControls();
    void OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter);
    void OnAboutQtLinkActivated(const QString& link);
    void OnExposureAutoModeChanged(bool active);
    void OnGainAutoModeChanged(bool active);
    void OnGainAnalogModeChanged(bool active);
    void OnGainDigitalModeChanged(bool active);
    void OnGainCombinedModeChanged(bool active);
    void OnGainHostModeChanged(bool active);

signals:
    void libraryError(QString message, int status);
};

#endif // MAINWINDOW_H
