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

#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QRect>
#include <QWidget>
#include <QMutex>

#include <cstdint>

#include "framestatistics.hpp"

class DisplayWindow;


class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomGraphicsScene(DisplayWindow* pParent=nullptr);
    ~CustomGraphicsScene() override = default;

    void setImage(QImage image);

private:
    QImage m_image{};
    QMutex m_mutex{};

    void drawBackground(QPainter* painter, const QRectF& rect) override;
};


class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    DisplayWindow(QPoint pos, int desiredHeight, QSize imageSize, QWidget* parent=nullptr);
    ~DisplayWindow() override = default;

public slots:
    void UpdateDisplay(QImage image);
    void UpdateCounters(const FrameStatistics& statistics);

private:
    static double AverageValue(double val1, double val2, double deviation);

    QLabel* m_labelInfos{};
    QVBoxLayout* m_layout{};

    QGraphicsView* m_graphicsView{};
    CustomGraphicsScene* m_scene{};

    double m_frameRate{};
    double m_conversionTime_ms{};
};

#endif // DISPLAY_WINDOW_H
