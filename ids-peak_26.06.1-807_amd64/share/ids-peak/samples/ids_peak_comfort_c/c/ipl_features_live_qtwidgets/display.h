/*!
 * \file    display.h
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. It can be used for other QT widget
 *          applications as well.
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

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMutex>
#include <QPainter>
#include <QRect>

#include <cstdint>

class Display;

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomGraphicsScene(Display* parent);
    ~CustomGraphicsScene() override = default;

    void setImage(QImage image);
    void setBrightnessRoiRect(QRect rect);
    void setWhitebalanceRoiRect(QRect rect);

private:
    Display* m_parent{};
    QMutex m_mutex{};
    QImage m_image;
    QRect m_roi_brightness_rect{};
    QRect m_roi_whitebalance_rect{};

    void drawBackground(QPainter* painter, const QRectF& rect) override;
};

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget* parent);
    ~Display() override = default;

    void setBrightnessRoiRect(QRect rect);
    void setWhitebalanceRoiRect(QRect rect);

public slots:
    void OnImageReceived(QImage image);

private:
    CustomGraphicsScene* m_scene{};
    QGraphicsView* m_view;
};

#endif // DISPLAY_H
