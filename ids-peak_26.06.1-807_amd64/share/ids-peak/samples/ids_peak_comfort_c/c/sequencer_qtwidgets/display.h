/*!
 * \file    display.h
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. The display is adapted to show only
 *          images with an explicit number.
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

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsScene>
#include <QGraphicsView>
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

    void SetImage(QImage image);
    void SetColorBackground(const QColor& col);

private:

    Display* m_parent;
    QImage m_image;
    QColor m_colorBackground;

    void drawBackground(QPainter* painter, const QRectF& rect) override;
};


class Display : public QGraphicsView
{
    Q_OBJECT

public:

    explicit Display(int number, QWidget* parent);
    ~Display() override = default;

    void SetColorBackground(const QColor& col);

public slots:

    void OnImageReceived(int numDisplay, QImage image);

private:

    int m_number;
    CustomGraphicsScene* m_scene;

    void mousePressEvent(QMouseEvent *event) override;

signals:

    void Signal_Selected();
};

#endif // DISPLAY_H
