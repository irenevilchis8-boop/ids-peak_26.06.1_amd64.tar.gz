/*!
 * \brief   The DisplayWindow class implements an easy way to display images from a
 *          camera in a Qt widgets window. It can be used for other QT widget
 *          applications as well.
 *
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

#include "displaywindow.h"
#include <utility>

#include <QLabel>
#include <QLayout>
#include <QWidget>
#include <QMutexLocker>


DisplayWindow::DisplayWindow(QPoint pos, int desiredHeight, QSize imageSize, QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    setLayout(m_layout);

    int displayWidth = static_cast<int>(
        static_cast<double>(imageSize.height()) / static_cast<double>(imageSize.height()) * static_cast<double>(desiredHeight));

    setGeometry(QRect{pos, QSize{displayWidth, desiredHeight}});

    // Create a graphics view for the camera image
    m_graphicsView = new QGraphicsView(this);
    m_graphicsView->setStyleSheet("QGraphicsView { border-style: none; background-color: transparent }");
    m_scene = new CustomGraphicsScene(this);
    m_graphicsView->setScene(m_scene);

    m_graphicsView->setInteractive(false);
    m_graphicsView->setFocusPolicy(Qt::NoFocus);

    // Create a label for the capture infos
    m_labelInfos = new QLabel(this);

    // Add the graphics display and the label to the corresponding layout of the display window
    m_layout->addWidget(m_graphicsView);
    m_layout->addWidget(m_labelInfos);
}

void DisplayWindow::UpdateDisplay(QImage image)
{
    if(image.rect() != m_graphicsView->sceneRect())
    {
        m_graphicsView->setSceneRect(image.rect());
        m_graphicsView->fitInView(m_graphicsView->sceneRect(), Qt::KeepAspectRatio);
    }

    m_scene->setImage(std::move(image));
}


void DisplayWindow::UpdateCounters(const FrameStatistics& statistics)
{
    double frameRate_Hz = 0.0;
    if (statistics.frameTime_ms > 0)
    {
        frameRate_Hz = 1000.0 / static_cast<double>(statistics.frameTime_ms);
    }

    m_frameRate = AverageValue(m_frameRate, frameRate_Hz, 3.0);
    m_conversionTime_ms = AverageValue(m_conversionTime_ms, static_cast<double>(statistics.conversionTime_ms), 3.0);

    if (statistics.showCustomNodes)
    {
        m_labelInfos->setText(QString("Framerate: %1, conversion: %2 ms, frames acquired: %3, errors: %4, incomplete: %5, dropped: %6, lost: %7")
            .arg(QString::number(m_frameRate, 'f', 1), QString::number(m_conversionTime_ms, 'f', 1), QString::number(statistics.frameCounter),
                QString::number(statistics.errorCounter), QString::number(statistics.incomplete), QString::number(statistics.dropped), QString::number(statistics.lost)));
    }
    else
    {
        m_labelInfos->setText(QString("Framerate: %1, conversion: %2 ms, frames acquired: %3, errors: %4")
            .arg(QString::number(m_frameRate, 'f', 1), QString::number(m_conversionTime_ms, 'f', 1), QString::number(statistics.frameCounter),
                QString::number(statistics.errorCounter)));
    }
}


double DisplayWindow::AverageValue(double val1, double val2, double deviation)
{
    double ret;

    if (((val1 - val2) > deviation) || ((val2 - val1) > deviation))
    {
        ret = val2;
    }
    else
    {
        ret = (15.0 * val1 + val2) / 16.0;
    }

    return ret;
}


CustomGraphicsScene::CustomGraphicsScene(DisplayWindow* parent)
    : QGraphicsScene(parent)
{

}

void CustomGraphicsScene::setImage(QImage image)
{
    QMutexLocker lock{&m_mutex};
    m_image = std::move(image);
    update();
}


void CustomGraphicsScene::drawBackground(QPainter* painter, const QRectF&)
{
    QMutexLocker lock{&m_mutex};
    painter->drawImage(0, 0, m_image);
}
