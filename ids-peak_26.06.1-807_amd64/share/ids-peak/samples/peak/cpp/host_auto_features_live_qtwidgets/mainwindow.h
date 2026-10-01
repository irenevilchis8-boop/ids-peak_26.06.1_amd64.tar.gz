/*!
 * Copyright (C) 2021 - 2026, IDS Imaging Development Systems GmbH.
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
#include "autofeatures.h"
#include "device.h"
#include "display.h"

#include <peak_afl/peak_afl.hpp>
#include <peak_ipl/peak_ipl.hpp>

#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>

class FloatControl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    std::unique_ptr<Device> m_device;
    std::shared_ptr<AutoFeatures> m_autoFeatures;

    QLabel* m_labelInfo{};
    CustomGraphicsView* m_display{};

    // Controls for ExposureAuto
    QButtonGroup* m_groupExposureAuto{};
    QButtonGroup* m_groupGainAuto{};
    QButtonGroup* m_groupBalanceWhiteAuto{};

    QSpinBox* m_spinBoxSkipFrames{};

    AcquisitionWorker* m_acquisitionWorker{};
    QThread m_acquisitionThread{};

    // Gain / Exposure Controls
    FloatControl* m_controlExposure{};
    FloatControl* m_controlGain{};
    FloatControl* m_controlFrameRate{};

    // Gain limit controls
    FloatControl* m_controlGainMin{};
    FloatControl* m_controlGainMax{};


    // Exposure limit controls
    FloatControl* m_controlExposureLimitMin{};
    FloatControl* m_controlExposureLimitMax{};

    QTimer* m_updateTimer{};

    void OpenDevice();
    void CloseDevice();
    void CreateAutoFeatures();

    void CreateControls();
    QLayout* CreateStatusControls();
    QLayout* CreateAutoControls();
    QLayout* CreateCameraControls();
    void UpdateControls();

    static QFrame* CreateHLine();

private slots:
    void OnCounterChanged(unsigned int frameCounter, unsigned int errorCounter);
    void OnAboutQtLinkActivated(const QString& link);
    void OnRadioExposureAuto(int mode);
    void OnRadioGainAuto(int mode);
    void OnRadioBalanceWhiteAuto(int mode);
    void OnButtonReset();
    void OnSpinBoxSkipFrames(int skipFrames);
    void UpdateValues();

signals:
    void AutoExposureFinished();
    void AutoGainFinished();
    void AutoBalanceWhiteFinished();
};

#endif // MAINWINDOW_H
