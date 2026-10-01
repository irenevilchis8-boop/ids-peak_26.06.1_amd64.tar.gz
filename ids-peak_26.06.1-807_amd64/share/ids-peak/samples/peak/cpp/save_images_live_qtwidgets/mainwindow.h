/*!
 * Copyright (C) 2019 - 2026, IDS Imaging Development Systems GmbH.
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

#include <peak_ipl/peak_ipl.hpp>

#include <peak/peak.hpp>

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QThread>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <cstdint>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    std::shared_ptr<peak::core::Device> m_device;
    std::shared_ptr<peak::core::DataStream> m_dataStream;
    std::shared_ptr<peak::core::NodeMap> m_nodemapRemoteDevice;

    CustomGraphicsView* m_display{};
    QLabel* m_labelInfo{};
    QLabel* m_labelVersion{};
    QPushButton* m_buttonSave{};
    QLabel* m_labelAboutQt{};

    QVBoxLayout* m_layout{};
    QHBoxLayout* m_controls{};

    AcquisitionWorker* m_acquisitionWorker{};
    QThread m_acquisitionThread;

    std::mutex m_writeMutex;

    void DestroyAll();

    bool OpenDevice();
    void CloseDevice();

    std::string selectSaveFileWithDialog();

public slots:
    void SaveImage();
    void onCounterChanged(unsigned int frameCounter, unsigned int errorCounter);
    void onAboutQtLinkActivated(const QString& link);
};

#endif // MAINWINDOW_H
