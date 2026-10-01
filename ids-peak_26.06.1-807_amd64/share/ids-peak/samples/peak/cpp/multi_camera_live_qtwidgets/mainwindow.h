/*!
 * Copyright (C) 2020 - 2026, IDS Imaging Development Systems GmbH.
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
#include "displaywindow.h"

#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak/peak.hpp>

#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>

#include <cstdint>


// The members of this structure are important for the use of the camera
struct DeviceContext
{
    std::shared_ptr<peak::core::Device> device{};
    std::shared_ptr<peak::core::DataStream> dataStream{};
    std::shared_ptr<peak::core::NodeMap> nodemapRemoteDevice{};
    peak::common::PixelFormat pixelFormat{};
    std::unique_ptr<DisplayWindow> displayWindow{};
    QSize imageSize{};
    AcquisitionWorker* acquisitionWorker{};
    QThread acquisitionThread{};
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    void OnAboutQt(const QString& link);

private:
    bool OpenDevices();
    void CloseDevices();
    void CreateStatusBar();

    void closeEvent(QCloseEvent* event) override;

    std::vector<std::unique_ptr<DeviceContext>> m_vecDevices{};

    QWidget* m_centralWidget{};
    QVBoxLayout* m_layout{};
    QWidget* m_statusBar{};
    QHBoxLayout* m_statusBarLayout{};
    QLabel* m_statusBarLabelVersion{};
    QLabel* m_statusBarLabelAboutQt{};

    static constexpr int32_t m_max_number_of_devices{3};
    static constexpr int64_t m_maximum_throughputlimit{125000000};
};

#endif // MAINWINDOW_H
